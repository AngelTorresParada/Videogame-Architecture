#include "Player.h"
#include "MovePlayerComponent.h"
#include "Game.h"

#define PLAYER_WIDTH 30.0f

Player::Player(Game *_game, float _x, float _y) {
	game = _game;

	GLuint texture = CORE_LoadPNG("../data/fireMario.png", false);
	transform = new TransformComponent(this, _x, _y);
	float *x = new float;
	float *y = new float;
	transform->getPosition(x, y);

	MovePlayerComponent *m = new MovePlayerComponent(this, 5);

	components = std::vector<Component *>();
	components.push_back(transform);
	components.push_back(m);

	sprite = new Sprite(texture, *x, *y, PLAYER_WIDTH, PLAYER_WIDTH);
}


Player::~Player() {
	while (!components.empty())
		components.pop_back();
	delete sprite;
}


void Player::Run() {
	for (auto c : components) {
		c->Run();
	}
	float x, y;
	transform->getPosition(&x, &y);
	sprite->x = x;
	sprite->y = y;
}


Sprite *Player::getSprite() {
	return sprite;
}


TransformComponent * Player::getTransform() {
	return transform;
}

void Player::RecieveMessage(Message *_msg) {
	ProcessMessage(_msg);
}

void Player::ProcessMessage(Message *_msg) {
	if (dynamic_cast<MoveLeftMessage *>(_msg) || dynamic_cast<MoveRightMessage *>(_msg) || dynamic_cast<BulletShotMessage *>(_msg)) {
		for (auto c : components) {
			c->ProcessMessage(_msg);
		}
	}
	else {
		if (dynamic_cast<EntityHitMessage *>(_msg)) {
			game->RecieveMessage(_msg);
		}
	}
}
