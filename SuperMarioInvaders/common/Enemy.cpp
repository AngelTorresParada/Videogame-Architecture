#include "Enemy.h"
#include "Game.h"
#include "EnemyAIComponent.h"

Enemy::Enemy(Game *_game, float _x, float _y) {
	game = _game;

	GLuint texture = CORE_LoadPNG("../data/Koopa.png", false);
	transform = new TransformComponent(this, _x, _y);
	float *x = new float;
	float *y = new float;
	transform->getPosition(x, y);
	EnemyAIComponent *ai = new EnemyAIComponent(this, 1);

	components = std::vector<Component *>();
	components.push_back(transform);
	components.push_back(ai);

	sprite = new Sprite(texture, *x, *y, ENEMY_WIDTH, ENEMY_WIDTH);
}

Enemy::~Enemy() {
	while (! components.empty())
		components.pop_back();
	delete sprite;
}

void Enemy::Run() {
	for (auto c : components) {
		c->Run();
	}

	float x, y;
	transform->getPosition(&x, &y);
	sprite->x = x;
	sprite->y = y;
}

Sprite * Enemy::getSprite() {
	return sprite;
}

TransformComponent * Enemy::getTransform() {
	return transform;
}

void Enemy::RecieveMessage(Message *_msg) {
	ProcessMessage(_msg);
}

void Enemy::setSpeed(float _speed) {
	for (auto c : components) {
		EnemyAIComponent *ai = dynamic_cast<EnemyAIComponent *>(c);
		if (ai) {
			ai->setSpeed(_speed);
		}
	}
}

void Enemy::ProcessMessage(Message *_msg) {
	if (dynamic_cast<EntityHitMessage *>(_msg) || dynamic_cast<InvokeDirectionChangeMessage *>(_msg) || dynamic_cast<GameOverMessage *>(_msg))
		game->RecieveMessage(_msg);
	else {
		for (auto c : components) {
			c->ProcessMessage(_msg);
		}
	}
	
}
