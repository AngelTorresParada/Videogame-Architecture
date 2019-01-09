#include "MovePlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

#define PLAYER_WIDTH 30.0f

MovePlayerComponent::MovePlayerComponent(GameObject *_player, float _speed) {
	player = _player;
	speed = _speed;
}

MovePlayerComponent::~MovePlayerComponent() {
}

void MovePlayerComponent::Run() {
}


void MovePlayerComponent::ProcessMessage(Message *_msg) {
	MoveLeftMessage *mlm = dynamic_cast<MoveLeftMessage *>(_msg);
	if (mlm) {
		float x = 0;
		float y = 0;
		player->getTransform()->getPosition(&x, &y);
		if (!(x - speed < PLAYER_WIDTH / 2))
			player->getTransform()->setPosition(x - speed, y);
	}
	else {
		MoveRightMessage *mrm = dynamic_cast<MoveRightMessage *>(_msg);
		if (mrm) {
			float x = 0;
			float y = 0;
			player->getTransform()->getPosition(&x, &y);
			if (!(x + speed > SCR_WIDTH - PLAYER_WIDTH / 2))
				player->getTransform()->setPosition(x + speed, y);
			
		}
		else {
			BulletShotMessage *bulletShot = dynamic_cast<BulletShotMessage *>(_msg);
			if (bulletShot && bulletShot->owner == Bullet::ENEMY) {
				checkCollision(bulletShot->x, bulletShot->y);
			}
		}
	}
}


float MovePlayerComponent::getSpeed() {
	return speed;
}

void MovePlayerComponent::setSpeed(float _speed) {
	speed = _speed;
}


void MovePlayerComponent::checkCollision(float _x, float _y) {
	float x, y;
	player->getTransform()->getPosition(&x, &y);
	float distance = sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
	if (distance < PLAYER_WIDTH / 2 + 10) {
		EntityHitMessage *msg = new EntityHitMessage(player);
		SendMessage(msg);
	}
}

void MovePlayerComponent::SendMessage(Message *_msg) {
	player->RecieveMessage(_msg);
}
