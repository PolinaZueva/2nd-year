#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
private:
    int direction;

public:
    Bullet(int x, int y, int direction, GameContext* context);
    void act(GameObject& context) override;
    void collision(GameObject& other) override;
};