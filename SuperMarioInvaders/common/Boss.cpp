#include "Boss.h"
#include "Game.h"
#include "BossMovementComponent.h"

Boss::Boss(Game *_game, float _x, float _y) {
	game = _game;

	GLuint texture = CORE_LoadPNG("../data/Bowser.png", false);
	transform = new TransformComponent(this, _x, _y);
	float *x = new float;
	float *y = new float;
	transform->getPosition(x, y);
	BossMovementComponent *ai = new BossMovementComponent(this, 2);

	components = std::vector<Component *>();
	components.push_back(transform);
	components.push_back(ai);

	sprite = new Sprite(texture, *x, *y, ENEMY_WIDTH, ENEMY_WIDTH);
}

Boss::~Boss() {
	while (!components.empty())
		components.pop_back();
	delete sprite;
}

void Boss::Run() {
	for (auto c : components) {
		c->Run();
	}

	float x, y;
	transform->getPosition(&x, &y);
	sprite->x = x;
	sprite->y = y;
}


Sprite * Boss::getSprite() {
	return sprite;
}


TransformComponent * Boss::getTransform() {
	return transform;
}


void Boss::RecieveMessage(Message *_msg) {
	ProcessMessage(_msg);
}


void Boss::ProcessMessage(Message *_msg) {
	if (dynamic_cast<DestroyBossMessage *>(_msg) || dynamic_cast<EntityHitMessage *>(_msg))
		game->RecieveMessage(_msg);
	else {
		for (auto c : components) {
			c->ProcessMessage(_msg);
		}
	}
}
