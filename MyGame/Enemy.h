#pragma once

#include "GameObject.h"
#include <conio.h>

class Enemy : public GameObject {
private:
	int spawnX, spawnY;

public:
	Enemy(int x, int y, GameContext* context);
	void act(GameObject& context) override;
	void collision(GameObject& other) override;
	void respawn(); 
};