#pragma once

#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "Sprite.h"


#define NUM_ENEMIES_X 10
#define NUM_ENEMIES_Y 5
#define MAX_BOSS_FREQUENCE 200
#define BOSS_Y 420

class TransformComponent;
class Game;
class Component;
class Message;

class GameObject {
	public:
		virtual ~GameObject();
		virtual void Run() = 0;
		virtual Sprite *getSprite() = 0;
		virtual void RecieveMessage(Message *) = 0;
		virtual TransformComponent *getTransform() = 0;

		std::vector<Component *> components;

	protected:
		virtual void ProcessMessage(Message *) = 0;
		Game *game;
};


