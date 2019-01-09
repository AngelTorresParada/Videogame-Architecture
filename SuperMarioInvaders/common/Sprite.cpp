#include "Sprite.h"

Sprite::Sprite(GLuint _texture, float _x, float _y, float _width, float _height) {
	texture = _texture;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
}


Sprite::~Sprite() {
}


void Sprite::Render() {
	CORE_RenderCenteredSprite(vmake(x, y), vmake(width, height), texture);
}
