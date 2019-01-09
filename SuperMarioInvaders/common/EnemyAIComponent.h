#pragma once

#include "Component.h"
#include "Message.h"

class GameObject;


class EnemyAIComponent : public Component {
	float speed;
	int direction;
	GameObject *enemy;

public:
	EnemyAIComponent(GameObject *, float);
	~EnemyAIComponent();

	virtual void Run();
	virtual void ProcessMessage(Message *);
	virtual void SendMessage(Message *);

	float getSpeed();
	void setSpeed(float);

	int getDirection();
	void setDirection(int);

	void checkCollision(float, float);
	void checkLimit();
	void checkFloor();


};