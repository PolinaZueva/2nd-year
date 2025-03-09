#include "GameContext.h"
#include "GameEngine.h"
#include "Player.h"
#include "Enemy.h"

int main() {
    srand(time(NULL));

    GameContext context;  //создаем контекст игры
    context.initializeMap();  

    Player* player = new Player(1, 1, &context);  
    context.setPlayer(player);
    context.addObject(player);

    context.addObject(new Enemy(17, 1, &context));   
    context.addObject(new Enemy(26, 9, &context));  
    context.addObject(new Enemy(3, 17, &context));  

    GameEngine engine(context);  //создаем игровой движок
    engine.showMenu();
    engine.run();  //основной цикл

    return 0;
}
