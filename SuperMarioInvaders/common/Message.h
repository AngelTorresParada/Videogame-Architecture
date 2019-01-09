#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Message {
	public:
		virtual ~Message();
};


class MoveLeftMessage : public Message {
	public:
		virtual ~MoveLeftMessage();
};


class MoveRightMessage : public Message {
	public:
		virtual ~MoveRightMessage();
};


class DestroyBulletMessage : public Message {
	public:
		virtual ~DestroyBulletMessage();
};


class DestroyEnemyBulletMessage : public Message {
	public:
		virtual ~DestroyEnemyBulletMessage();
};


class CreateBulletMessage : public Message {
	public: 
		virtual ~CreateBulletMessage();
		Bullet::Owner owner;
};


class EntityHitMessage : public Message {
	public:
		EntityHitMessage(GameObject *);
		virtual ~EntityHitMessage();

		GameObject *hitEntity;
};


class ChangeDirectionMessage : public Message {
	public:
		virtual ~ChangeDirectionMessage();
};


class PartnerKilledMessage : public Message {
	public: 
		virtual ~PartnerKilledMessage();
};


class BulletShotMessage : public Message {
	public:
		virtual ~BulletShotMessage();
		float x, y;
		Bullet::Owner owner;

};


class InvokeDirectionChangeMessage : public Message {
	public:
		virtual ~InvokeDirectionChangeMessage();
};


class DestroyBossMessage : public Message {
	public:
		virtual ~DestroyBossMessage();
};


class GameOverMessage : public Message {
	public:
		virtual ~GameOverMessage();
};