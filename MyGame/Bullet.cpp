#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "GameContext.h"

Bullet::Bullet(int x, int y, int direction, GameContext* context)
    : GameObject(x, y, 1, '*', context), direction(direction) {
}

void Bullet::collision(GameObject& other) {}

void Bullet::act(GameObject& context) {
    switch (direction) {
    case 0: y--; break;
    case 1: y++; break; 
    case 2: x--; break;
    case 3: x++; break;
    }

    if (x < 0 || x >= getContext()->getWidth() || y < 0 || y >= getContext()->getHeight()) {
        setHealth(0); 
        return;
    }

    for (auto obj : getContext()->getObjects()) {
        if (obj->getX() == x && obj->getY() == y && obj != this) {            
            obj->collision(*this); 
            if (!obj->isAlive()) {
                setHealth(0); 
            }
            break;
        }
    }
}