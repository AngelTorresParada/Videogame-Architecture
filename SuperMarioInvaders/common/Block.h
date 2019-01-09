#pragma once

#include "GameObject.h"
#include "TransformComponent.h"

#define BLOCK_WIDTH 30.0f

class Block : public GameObject {

public:
	Block(Game *, float, float);
	virtual ~Block();
	virtual void Run();
	virtual Sprite *getSprite();
	virtual TransformComponent *getTransform();
	virtual void RecieveMessage(Message *);

private:
	virtual void ProcessMessage(Message *);
	Sprite *sprite;
	TransformComponent *transform;

	void checkCollisions(float, float);

};