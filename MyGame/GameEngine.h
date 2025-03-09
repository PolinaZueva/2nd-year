#pragma once
#include <windows.h> 
#include "GameObject.h"
#include "GameContext.h"

//управляет игровым процессом
class GameEngine {
private:
    GameContext& context;

public:
    GameEngine(GameContext& context) : context(context) {}
    void run();
    static void ClearScreen();
    static void renderMessage(const GameContext& context, const std::string& message, int line = 0);
    void showMenu();
    void gameOver();
    void gameWin();
};
