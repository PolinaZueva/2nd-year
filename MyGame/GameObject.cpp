#include "GameObject.h"

GameObject::GameObject(int x, int y, int health, char representation, GameContext* context) :
	x(x), y(y), health(health), representation(representation), context(context), score(0) {
}

int GameObject::getX() const { return x; }
int GameObject::getY() const { return y; }
int GameObject::getHealth() const { return health; }
char GameObject::getRepresentation() const { return representation; }

void GameObject::setPosition(int newX, int newY) {
	x = newX;
	y = newY;
}

void GameObject::setHealth(int health) { this->health = health; }
bool GameObject::isAlive() const { return health > 0; }

GameContext* GameObject::getContext() const { return context; }

int GameObject::getScore() const { return score; }
void GameObject::setScore(int newScore) { score = newScore; }
