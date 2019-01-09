#pragma once

#include "GameObject.h"
#include "TransformComponent.h"

#define ENEMY_WIDTH 50.0f
#define BOSS_SPEED 3.0f

class Boss : public GameObject {

public:
	Boss(Game *, float, float);
	~Boss();
	virtual void Run();
	virtual Sprite *getSprite();
	virtual TransformComponent *getTransform();
	virtual void RecieveMessage(Message *);

private:
	virtual void ProcessMessage(Message *);
	Sprite *sprite;
	TransformComponent *transform;

};