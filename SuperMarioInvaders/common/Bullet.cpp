#include "Bullet.h"
#include "TransformComponent.h"
#include "Game.h"

#define BULLET_WIDTH 20.0f

Bullet::Bullet(Game *_game, float _x, float _y, Owner _owner) {
	game = _game;
	owner = _owner;

	GLuint texture = CORE_LoadPNG("../data/fireball.png", false);
	transform = new TransformComponent(this, _x, _y);
	float *x = new float;
	float *y = new float;
	transform->getPosition(x, y);

	components = std::vector<Component *>();
	components.push_back(transform);

	sprite = new Sprite(texture, *x, *y, BULLET_WIDTH, BULLET_WIDTH);
}

Bullet::~Bullet() {
	while (!components.empty())
		components.pop_back();
	delete sprite;
}


void Bullet::Run() {
	float x, y;
	transform->getPosition(&x, &y);
	if (owner == PLAYER) transform->setPosition(x, y + BULLET_SPEED);
	else transform->setPosition(x, y - BULLET_SPEED);
	transform->getPosition(&x, &y);
	BulletShotMessage *bulletShot = new BulletShotMessage;
	bulletShot->x = x;
	bulletShot->y = y;
	bulletShot->owner = owner;
	SendMessage(bulletShot);

	transform->getPosition(&x, &y);
	sprite->x = x;
	sprite->y = y;

	if (y + BULLET_SPEED > SCR_HEIGHT && owner == PLAYER) {
		DestroyBulletMessage *msg = new DestroyBulletMessage;
		SendMessage(msg);
	}
	else if (y < 30 && owner == ENEMY) {
		DestroyEnemyBulletMessage *msg = new DestroyEnemyBulletMessage;
		SendMessage(msg);
	}

}


Sprite * Bullet::getSprite() {
	return sprite;
}


TransformComponent * Bullet::getTransform() {
	return transform;
}


void Bullet::RecieveMessage(Message *_msg) {
}


Bullet::Owner Bullet::getOwner() {
	return owner;
}


void Bullet::ProcessMessage(Message *_msg) {
}


void Bullet::SendMessage(Message *_msg) {
	game->RecieveMessage(_msg);
}
