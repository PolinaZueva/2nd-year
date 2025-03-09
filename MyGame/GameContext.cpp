#include "GameObject.h"
#include "GameContext.h"
#include "GameEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <iostream>
#include <fstream>

GameContext::GameContext() : width(0), height(0), player(nullptr), winCount(0), loseCount(0) {}

GameContext::GameContext(int width, int height) : width(width), height(height), player(nullptr), winCount(0), loseCount(0) {
	map.resize(height, std::string(width, ' '));
}

GameContext::~GameContext() {
	for (auto object : objects) {
		delete object;
	}
}

int GameContext::getWidth() const { return width; }
int GameContext::getHeight() const { return height; }

void GameContext::setPlayer(GameObject* player) { this->player = player; }
GameObject* GameContext::getPlayer() const { return player; }
void GameContext::addObject(GameObject* object) { return objects.push_back(object); }
const std::vector<GameObject*>& GameContext::getObjects() const { return objects; }

void GameContext::initializeMap() {
	map = {
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"A...............................A",
	"A.AAAAA.AAAAA.AAAAA.AAAAAoAAAAA.A",
	"A.A   A.A   A.A   A.A   A.A   A.A",
	"A.AAAA.AAAAA.AAAAA.AAAAA.AAAAAA.A",
	"A...............................A",
	"A.AAAAAoAAAAA.AAAAA.AAAAA.AAAAA.A",
	"A.A   A.A   A.A   A.A   A.A   A.A",
	"A.AAAA.AAAAA.AAAAA.AAAAA.AAAAAA.A",
	"A...............................A",
	"A.AA AA.AAAAA.AAAAA.AAAAAoAA AA.A",
	"A.A . A.A   A.A   A.A   A.A . A.A",
	"A.AA A.AAAAA.AAAAA.AAAAA.AAA AA.A",
	"A...............................A",
	"A.AAAAAoAAAAA.AAAAA.AAAAA.AAAAA.A",
	"A.A   A.A   A.A   A.A   A.A   A.A",
	"A.AAAA.AAAAA.AAAAA.AAAAA.AAAAAA.A",
	"A...............................A",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	};

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 'o') {
				teleports.push_back({ x, y });
			}
		}
	}

	width = map[0].size();
	height = map.size();
}

void GameContext::initializeBuffer() {
	buffer = map;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole != INVALID_HANDLE_VALUE) {
		COORD newSize = { static_cast<SHORT>(buffer[0].size()), static_cast<SHORT>(buffer.size()) };
		SetConsoleScreenBufferSize(hConsole, newSize);
	}
}

void GameContext::renderToBuffer() {
	buffer = map;
	for (auto object : objects) {
		if (object->isAlive()) {
			buffer[object->getY()][object->getX()] = object->getRepresentation();
		}
	}
}

void GameContext::render() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to get console handle.\n";
		return;
	}

	COORD bufferSize = { static_cast<SHORT>(buffer[0].size()), static_cast<SHORT>(buffer.size()) };
	COORD bufferCoord = { 0, 0 };
	SMALL_RECT writeRegion = { 0, 0, static_cast<SHORT>(buffer[0].size() - 1), static_cast<SHORT>(buffer.size() - 1) };

	std::vector<CHAR_INFO> charBuffer(bufferSize.X * bufferSize.Y);

	for (size_t y = 0; y < buffer.size(); ++y) {
		const std::string& line = buffer[y];
		for (size_t x = 0; x < line.size(); ++x) {
			CHAR_INFO& charInfo = charBuffer[y * bufferSize.X + x];
			charInfo.Char.AsciiChar = line[x];
			if (line[x] == 'A') {
				charInfo.Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
			}
			else if (line[x] == '.') {
				charInfo.Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			}
			else if (line[x] == 'E') {
				charInfo.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
			}
			else if (line[x] == 'o') {
				charInfo.Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
			}
			else {
				charInfo.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			}
		}
	}

	if (!WriteConsoleOutput(hConsole, charBuffer.data(), bufferSize, bufferCoord, &writeRegion)) {
		std::cerr << "Failed to write console output.\n";
	}
}

void GameContext::setPlayerName(const std::string& name) { playerName = name; }
std::string GameContext::getPlayerName() const { return playerName; }

void GameContext::saveLeaderboard() {
	std::ofstream file("leaderboard.txt");
	for (const auto& entry : leaderboard) {
		file << entry.first << " " << entry.second << "\n";
	}
}

void GameContext::loadLeaderboard() {
	std::ifstream file("leaderboard.txt");
	if (!file.is_open()) {
		std::cerr << "Failed to open leaderboard file.\n";
		return;
	}

	std::string name;
	int score;
	while (file >> name >> score) {
		leaderboard[name] = score;
	}
}

void GameContext::addToLeaderboard(const std::string& name, int score) {
	leaderboard[name] = score;
	saveLeaderboard();
}

void GameContext::showLeaderboard() {
	GameEngine::ClearScreen();

	std::cout << "Leaderboard:\n";
	for (const auto& entry : leaderboard) {
		std::cout << entry.first << ": " << entry.second << "\n";
	}
	std::cout << "Press any key to continue...\n";
	_getch();
}

void GameContext::incrementWinCount() { winCount++; }  
void GameContext::incrementLoseCount() { loseCount++; }  
int GameContext::getWinCount() const { return winCount; } 
int GameContext::getLoseCount() const { return loseCount; } 

bool GameContext::isWall(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height) return true;
	return map[y][x] == 'A';
}

bool GameContext::isCageFree(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height) return false; 
	return map[y][x] == ' ' || map[y][x] == '.'; 
}

void GameContext::removeDotAt(int x, int y) {
	if (map[y][x] == '.') {
		map[y][x] = ' '; 
	}
}

void GameContext::setMapCell(int x, int y, char value) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		map[y][x] = value;
	}
}

char GameContext::getMapCell(int x, int y) const {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return map[y][x];
	}
	return ' ';
}

bool GameContext::isGameWon() const {
	for (const auto& line : map) {
		if (line.find('.') != std::string::npos) {
			return false;
		}
	}
	return true;
}

const std::vector<std::pair<int, int>>& GameContext::getTeleports() const { return teleports; }

void GameContext::reset() {
	for (auto it = objects.begin(); it != objects.end(); ) {
		if (dynamic_cast<Bullet*>(*it)) { 
			delete* it;
			it = objects.erase(it);
		}
		else {
			++it;
		}
	}

	if (player) {
		player->setHealth(10);  
		player->setScore(0);   
		player->setPosition(1, 1);  
	}

	for (auto obj : objects) {
		if (dynamic_cast<Enemy*>(obj)) {
			dynamic_cast<Enemy*>(obj)->respawn();
		}
	}

	initializeMap();
}






