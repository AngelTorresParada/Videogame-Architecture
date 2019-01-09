#pragma once
#include "GameObject.h"
#include "TransformComponent.h"

class Player : public GameObject {

	public:
		Player(Game *, float, float);
		virtual ~Player();
		virtual void Run();
		virtual Sprite *getSprite();
		virtual TransformComponent *getTransform();
		virtual void RecieveMessage(Message *);

	private:
		virtual void ProcessMessage(Message *);
		Sprite *sprite;
		TransformComponent *transform;

};