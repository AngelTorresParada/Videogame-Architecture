#include "Message.h"

Message::~Message() {
}


MoveLeftMessage::~MoveLeftMessage() {
}


MoveRightMessage::~MoveRightMessage() {
}


DestroyBulletMessage::~DestroyBulletMessage() {
}

CreateBulletMessage::~CreateBulletMessage() {
}

EntityHitMessage::EntityHitMessage(GameObject *_entity) {
	hitEntity = _entity;
}

EntityHitMessage::~EntityHitMessage() {
}


ChangeDirectionMessage::~ChangeDirectionMessage() {
}


PartnerKilledMessage::~PartnerKilledMessage() {
}


BulletShotMessage::~BulletShotMessage() {
}

InvokeDirectionChangeMessage::~InvokeDirectionChangeMessage() {
}

DestroyBossMessage::~DestroyBossMessage() {
}

DestroyEnemyBulletMessage::~DestroyEnemyBulletMessage() {
}

GameOverMessage::~GameOverMessage() {
}
