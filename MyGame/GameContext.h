#pragma once

#include "GameObject.h"
#include <windows.h> 
#include <vector>
#include <iostream>
#include <string>
#include <map>

class GameObject;

class GameContext {
private:
    int width, height;
    std::vector<std::string> map;
    std::vector<GameObject*> objects;
    GameObject* player;
    std::vector<std::string> buffer;  //временный
    int winCount;
    int loseCount;
    std::string playerName;
    std::map<std::string, int> leaderboard;
    std::vector<std::pair<int, int>> teleports;    

public:
    GameContext();
    GameContext(int width, int height);
    ~GameContext();

    int getWidth() const;
    int getHeight() const;

    //управление объектами
    void setPlayer(GameObject* player);
    GameObject* getPlayer() const;
    void addObject(GameObject* object);
    const std::vector<GameObject*>& getObjects() const;       

    //управление состоянием
    void initializeMap();
    void initializeBuffer();

    //рендеринг
    void renderToBuffer();
    void render() const;

    //управление игровыми данными
    void setPlayerName(const std::string& name);
    std::string getPlayerName() const;
    void saveLeaderboard();
    void loadLeaderboard();
    void addToLeaderboard(const std::string& name, int score);
    void showLeaderboard();    
    void incrementWinCount();
    void incrementLoseCount();
    int getWinCount() const;
    int getLoseCount() const;
        
    bool isWall(int x, int y) const;
    bool isCageFree(int x, int y) const;
    void removeDotAt(int x, int y);
    void setMapCell(int x, int y, char value);
    char getMapCell(int x, int y) const;
    bool isGameWon() const;
    const std::vector<std::pair<int, int>>& getTeleports() const;

    //сброс игры
    void reset();
};