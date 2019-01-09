#pragma once
#include "Component.h"
#include "GameObject.h"

class TransformComponent : public Component {

	public:
		TransformComponent(GameObject *, float, float);

		virtual void Run();
		virtual void ProcessMessage(Message *);

		void getPosition(float *, float *);
		void setPosition(float, float);

	private:
		float x;
		float y;
		GameObject *parent;
};