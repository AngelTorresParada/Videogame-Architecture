#pragma once
#include "Component.h"
#include "Message.h"
#include "GameObject.h"


class BossMovementComponent : public Component {
	GameObject *boss;
	float speed;

public:
	BossMovementComponent(GameObject *, float);
	~BossMovementComponent();

	virtual void Run();
	virtual void ProcessMessage(Message *);
	void SendMessage(Message *);

	float getSpeed();
	void setSpeed(float);

	void checkCollision(float, float);


};