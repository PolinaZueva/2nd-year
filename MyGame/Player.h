#pragma once

#include "GameObject.h"
#include <conio.h>

class Player : public GameObject {
private:
	int score;  
	int lastDirection;

public:
	Player(int x, int y, GameContext* context);
	void teleport(GameContext* context);
	void act(GameObject& context) override;
	void collision(GameObject& other) override;
	void increaseScore(int points);
	int getScore() const;
};