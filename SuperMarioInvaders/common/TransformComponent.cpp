#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject *_entity, float _x, float _y) {
	parent = _entity;
	x = _x;
	y = _y;
}


void TransformComponent::Run() {
}


void TransformComponent::getPosition(float *_x, float *_y) {
	*_x = x;
	*_y = y;
}


void TransformComponent::setPosition(float _x, float _y) {
	x = _x;
	y = _y;
}

void TransformComponent::ProcessMessage(Message *) {
}
