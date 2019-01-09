#pragma once
#include "Component.h"
#include "Message.h"

class GameObject;


class MovePlayerComponent : public Component {
	GameObject *player;
	float speed;

	public:
		MovePlayerComponent(GameObject *, float);
		~MovePlayerComponent();

		virtual void Run();
		virtual void ProcessMessage(Message *);

		float getSpeed();
		void setSpeed(float);

		void checkCollision(float, float);
		void SendMessage(Message *);


};