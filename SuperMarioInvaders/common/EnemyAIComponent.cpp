#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Bullet.h"

#define INCREMENTALSPEED 0.1f

EnemyAIComponent::EnemyAIComponent(GameObject *_enemy, float _speed) {
	enemy = _enemy;
	speed = _speed;
	direction = 1;
}


EnemyAIComponent::~EnemyAIComponent() {
}


void EnemyAIComponent::Run() {
	float x, y;
	enemy->getTransform()->getPosition(&x, &y);
	enemy->getTransform()->setPosition(x + speed * direction, y);
	checkLimit();
	checkFloor();
}


void EnemyAIComponent::ProcessMessage(Message *_msg) {
	if (dynamic_cast<ChangeDirectionMessage *>(_msg)) {
		direction *= -1;
		float x, y;
		enemy->getTransform()->getPosition(&x, &y);
		enemy->getTransform()->setPosition(x, y - 5);
	}
	else {
		if (dynamic_cast<PartnerKilledMessage *>(_msg)) {
			speed += INCREMENTALSPEED;
			if (speed > 8) speed = 8;
		}
		else {
			BulletShotMessage *bulletShot = dynamic_cast<BulletShotMessage *>(_msg);
			if (bulletShot) {
				if(bulletShot->owner == Bullet::PLAYER)
					checkCollision(bulletShot->x, bulletShot->y);
			}
		}
	}
}


void EnemyAIComponent::SendMessage(Message *_msg) {
	enemy->RecieveMessage(_msg);
}


float EnemyAIComponent::getSpeed() {
	return speed;
}


void EnemyAIComponent::setSpeed(float _speed) {
	speed = _speed;
}


int EnemyAIComponent::getDirection() {
	return direction;
}


void EnemyAIComponent::setDirection(int _direction) {
	direction = _direction;
}


void EnemyAIComponent::checkCollision(float _x, float _y) {
	float x, y;
	enemy->getTransform()->getPosition(&x, &y);
	float distance = sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
	if (distance < ENEMY_WIDTH/2 + 10) {
		EntityHitMessage *msg = new EntityHitMessage(enemy);
		SendMessage(msg);
	}
}


void EnemyAIComponent::checkLimit() {
	float x, y;
	enemy->getTransform()->getPosition(&x, &y);
	if ((x > SCR_WIDTH - 50 && direction > 0) || (x < 50 && direction < 0)) {
		InvokeDirectionChangeMessage *msg = new InvokeDirectionChangeMessage;
		SendMessage(msg);
	}
}

void EnemyAIComponent::checkFloor() {
	float x, y;
	enemy->getTransform()->getPosition(&x, &y);

	if (y <= 45) {
		GameOverMessage *msg = new GameOverMessage;
		SendMessage(msg);
	}
}


