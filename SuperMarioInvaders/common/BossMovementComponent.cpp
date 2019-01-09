#include "BossMovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Boss.h"
#include "Message.h"
#include "Bullet.h"


BossMovementComponent::BossMovementComponent(GameObject *_boss, float _speed) {
	boss = _boss;
	speed = _speed;
}


BossMovementComponent::~BossMovementComponent() {
}


void BossMovementComponent::Run() {
	float x, y;
	boss->getTransform()->getPosition(&x, &y);
	boss->getTransform()->setPosition(x - speed, y);
	boss->getTransform()->getPosition(&x, &y);
	if (x < -ENEMY_WIDTH/2) {
		DestroyBossMessage *msg = new DestroyBossMessage;
		SendMessage(msg);
	}
}


void BossMovementComponent::ProcessMessage(Message *_msg) {
	BulletShotMessage *bulletShot = dynamic_cast<BulletShotMessage *>(_msg);
	if (bulletShot && bulletShot->owner == Bullet::PLAYER) {
		checkCollision(bulletShot->x, bulletShot->y);
	}
}


void BossMovementComponent::SendMessage(Message *_msg) {
	boss->RecieveMessage(_msg);
}


float BossMovementComponent::getSpeed() {
	return speed;
}


void BossMovementComponent::setSpeed(float _speed) {
	speed = _speed;
}


void BossMovementComponent::checkCollision(float _x, float _y) {
	float x, y;
	boss->getTransform()->getPosition(&x, &y);
	float distance = sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
	if (distance < ENEMY_WIDTH / 2 + 20) {
		EntityHitMessage *msg = new EntityHitMessage(boss);
		SendMessage(msg);
	}
}
