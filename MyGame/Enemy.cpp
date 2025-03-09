#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "GameEngine.h"

Enemy::Enemy(int x, int y, GameContext* context) : GameObject(x, y, 1, 'E', context), spawnX(x), spawnY(y){}

void Enemy::act(GameObject& context) {
    if (!isAlive()) {
        respawn();
        return;
    }

    GameContext* gameContext = this->getContext();
    if (!gameContext) return;

    int playerX = context.getX();
    int playerY = context.getY();

    int direction = rand() % 4;
    int newX = x, newY = y;

    if (abs(playerX - x) + abs(playerY - y) <= 5) {
        bool moveX = (rand() % 2 == 0);  //по x или y
        if (moveX) {
            if (playerX > x) newX++;
            else if (playerX < x) newX--;

            if (newX >= 0 && newX < gameContext->getWidth() &&
                !gameContext->isWall(newX, y) && gameContext->isCageFree(newX, y)) {
                x = newX;
            }
        }
        else {
            if (playerY > y) newY++;
            else if (playerY < y) newY--;

            if (newY >= 0 && newY < gameContext->getHeight() &&
                !gameContext->isWall(x, newY) && gameContext->isCageFree(x, newY)) {
                y = newY;
            }
        }
    }
    else {  //если игрок далеко, то случайно
        switch (direction) {
        case 0: newY--; break;
        case 1: newY++; break;
        case 2: newX--; break;
        case 3: newX++; break;
        }
    }

    if (newX >= 0 && newX < gameContext->getWidth() &&
        newY >= 0 && newY < gameContext->getHeight()) {
        if (!gameContext->isWall(newX, newY) && gameContext->isCageFree(newX, newY)) {
            x = newX;
            y = newY;
        }
    }
}

void Enemy::collision(GameObject& other) {
    if (dynamic_cast<Bullet*>(&other)) {
        setHealth(0);
    }
}

void Enemy::respawn() {
    x = spawnX;
    y = spawnY;
    setHealth(1); 
}