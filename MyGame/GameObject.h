#pragma once

class GameContext;

class GameObject {
protected:
	int x, y;
	int health;
	char representation;
	GameContext* context;
	int score;

public:
	GameObject(int x, int y, int health, char repr, GameContext* context);
	virtual ~GameObject() = default;
	virtual void act(GameObject& context) = 0;  //поведение игрока
	virtual void collision(GameObject& other) = 0;

	int getScore() const;  
	void setScore(int newScore);  

	int getX() const;
	int getY() const;
	int getHealth() const;
	char getRepresentation() const;

	void setPosition(int newX, int newY);
	void setHealth(int health);
	bool isAlive() const;

	GameContext* getContext() const;
};	