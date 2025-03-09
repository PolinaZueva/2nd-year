#include "GameEngine.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>


void GameEngine::ClearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //дескриптор
    COORD homeCoords = { 0, 0 };
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;  //размеры

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;  //общее колво точек для очистки экрана
        FillConsoleOutputCharacter(hConsole, ' ', cells, homeCoords, &written);  //заполняем пробелами
        SetConsoleCursorPosition(hConsole, homeCoords);
    }
}

void GameEngine::renderMessage(const GameContext& context, const std::string& message, int line) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD messageCoords = { 0, static_cast<SHORT>(context.getHeight() + 1 + line) };
    SetConsoleCursorPosition(hConsole, messageCoords);  //устанавливаем курсор

    DWORD written;
    std::string clearLine(context.getWidth(), ' ');
    WriteConsole(hConsole, clearLine.c_str(), clearLine.size(), &written, nullptr);

    SetConsoleCursorPosition(hConsole, messageCoords);
    std::cout << "Message: " << message;
}


void GameEngine::gameWin() {
    context.incrementWinCount();
    context.addToLeaderboard(context.getPlayerName(), context.getWinCount());  
    ClearScreen();
    std::cout << "You win! All dots collected.\n";
    std::cout << "Total wins: " << context.getWinCount() << "\n";  
    std::cout << "Total losses: " << context.getLoseCount() << "\n";  
    while (true) {
        std::cout << "1. Play again\n";
        std::cout << "2. Exit\n";
        std::cout << "Choose an option: ";

        char choice = _getch();
        switch (choice) {
        case '1':
            ClearScreen(); 
            context.reset();  
            run();          
            return;
        case '2':
            exit(0);  
        default:
            std::cout << "Invalid option. Try again.\n";
            break;
        }
    }
}

void GameEngine::gameOver() {
    context.addToLeaderboard(context.getPlayerName(), context.getWinCount());
    context.incrementLoseCount();
    ClearScreen();  
    std::cout << "Game Over! You were caught by an enemy.\n";
    std::cout << "Total wins: " << context.getWinCount() << "\n";  
    std::cout << "Total losses: " << context.getLoseCount() << "\n";  
    while (true) {
        std::cout << "1. Play again\n";
        std::cout << "2. Exit\n";
        std::cout << "Choose an option: ";

        char choice = _getch();
        switch (choice) {
        case '1':
            context.reset();  
            run();            
        case '2':
            exit(0); 
        default:
            std::cout << "Invalid option. Try again.\n";
            break;
        }
    }
}

void GameEngine::showMenu() {
    context.loadLeaderboard();
    while (true) {
        ClearScreen();
        std::cout << "Menu:\n";
        std::cout << "1. Play\n";
        std::cout << "2. Rules of the game\n";
        std::cout << "3. Leaderboard\n";
        std::cout << "4. Exit\n"; 
        std::cout << "Choose an item: ";

        char choice = _getch();
        switch (choice) {
        case '1': {
            std::string name;
            std::cout << "Enter your name: ";
            std::cin >> name;
            context.setPlayerName(name);
            return;
        }
        case '2':
            ClearScreen();
            std::cout << "Правила игры:\n";
            std::cout << "- Управляйте персонажем (P) с помощью клавиш W, A, S, D.\n";
            std::cout << "- Вы можете стрелять персонажем (P) во врагов (E) с помощью клавиши E.\n";
            std::cout << "- Собирайте точки (.) для увеличения счета.\n";
            std::cout << "- Избегайте врагов (E). У вас 10 жизней.\n";
            std::cout << "- На карте есть несколько телепортов, они могут помочь вам быстрее перемещаться по карте.\n";
            std::cout << "Нажмите любую клавишу для возврата в меню...\n";
            _getch();
            break;
        case '3':
            context.showLeaderboard();
            break;
        case '4':
            exit(0);
        default:
            break;
        }
    }
}

void GameEngine::run() {
    ClearScreen();
    int frameCount = 0;
    while (true) {
        Player* player = dynamic_cast<Player*>(context.getPlayer());
        if (player) {
            player->act(*player);

            if (frameCount % 10 == 0) {
                for (auto obj : context.getObjects()) {                    
                        obj->act(*player);
                }
            }

            int x = player->getX();
            int y = player->getY();
            if (context.getMapCell(x, y) == '.') {
                context.setMapCell(x, y, ' '); 
            }

            if (context.isGameWon()) {
                gameWin();
                return;
            }

            for (auto obj : context.getObjects()) {
                if (obj != player && obj->getX() == player->getX() && obj->getY() == player->getY()) {
                    player->collision(*obj); 
                    obj->collision(*player); 
                }
            }

            if (!player->isAlive()) {
                gameOver();
                return;
            }

            context.renderToBuffer();  
            context.render();          

            frameCount++;
            Sleep(15);
        }
    }
}