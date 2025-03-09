#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameContext.h" 
#include "GameEngine.h" 
#include <iostream>

Player::Player(int x, int y, GameContext* context) : GameObject(x, y, 10, 'P', context), score(0), lastDirection(3) {}

void Player::teleport(GameContext* context) {
	const auto& teleports = context->getTeleports();
	if (teleports.empty()) return;

	std::pair<int, int> currentPosition = std::make_pair(x, y);
	
	std::pair<int, int> newPosition;
	do {
		int randomIndex = std::rand() % teleports.size();
		newPosition = teleports[randomIndex];
	} while (newPosition == currentPosition && teleports.size() > 1);  //чтобы два раза подряд не телепортироваться в одну точку

	x = newPosition.first;
	y = newPosition.second;
}

void Player::act(GameObject& context) {
	if (_kbhit()) {  //клавиша нажата?
		char key = _getch();  //ждём нажатия кнопки и возвращаем её код
		int newX = x, newY = y;
		switch (key) {
		case 'w': newY--; lastDirection = 0; break;
		case 's': newY++; lastDirection = 1; break;
		case 'a': newX--; lastDirection = 2; break;
		case 'd': newX++; lastDirection = 3; break;
		case 'e': 			
			getContext()->addObject(new Bullet(x, y, lastDirection, getContext()));
			break;
		default: return;
		}

		GameContext* gameContext = this->getContext(); 
		if (gameContext && !gameContext->isWall(newX, newY)) {
			x = newX;
			y = newY;

			if (gameContext->getMapCell(x, y) == '.') {
				gameContext->setMapCell(x, y, ' ');  
				increaseScore(1);  
			}

			if (gameContext->getMapCell(x, y) == 'o') {
				teleport(gameContext);
			}
		}
	}
}

void Player::collision(GameObject& other) {
	if (dynamic_cast<Enemy*>(&other)) {
		setHealth(getHealth() - 1); 
		GameEngine::renderMessage(*getContext(), "You were hit! Health remaining: " + std::to_string(getHealth()), 0);
	}
}

void Player::increaseScore(int points) { score += points; }
int Player::getScore() const { return score; }