#include "Block.h"
#include "Game.h"

Block::Block(Game *_game, float _x, float _y) {
	game = _game;

	GLuint texture = CORE_LoadPNG("../data/blockBkg.png", false);
	transform = new TransformComponent(this, _x, _y);
	float *x = new float;
	float *y = new float;
	transform->getPosition(x, y);

	components = std::vector<Component *>();
	components.push_back(transform);

	sprite = new Sprite(texture, *x, *y, BLOCK_WIDTH, BLOCK_WIDTH);
}

Block::~Block() {
	delete sprite;
	while (!components.empty())
		components.pop_back();
}

void Block::Run() {
	for (auto c : components) {
		c->Run();
	}
}

Sprite * Block::getSprite() {
	return sprite;
}

TransformComponent * Block::getTransform() {
	return transform;
}

void Block::RecieveMessage(Message *_msg) {
	ProcessMessage(_msg);
}

void Block::ProcessMessage(Message *_msg) {
	BulletShotMessage *bulletShot = dynamic_cast<BulletShotMessage *>(_msg);
	if (bulletShot)
		checkCollisions(bulletShot->x, bulletShot->y);
	else {
		EntityHitMessage *entityHit = dynamic_cast<EntityHitMessage *>(_msg);
		if (entityHit) {
			game->RecieveMessage(_msg);
		}
	}
}

void Block::checkCollisions(float _x, float _y) {
	float x, y;
	getTransform()->getPosition(&x, &y);
	float distance = sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
	if (distance < BLOCK_WIDTH / 2 + 10) {
		EntityHitMessage *msg = new EntityHitMessage(this);
		ProcessMessage(msg);
	}
}

