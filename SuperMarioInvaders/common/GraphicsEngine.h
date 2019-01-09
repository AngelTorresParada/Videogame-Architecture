#pragma once

#include <vector>
#include "Sprite.h"

class Game;


class Text {
	public:
		float x;
		float y;
		const char *text;
};


class GraphicsEngine {
	std::vector<Sprite *> sprites;
	std::vector<Text *> texts;

	public:
		GraphicsEngine(Game *);
		~GraphicsEngine();
		void Render();
		void AddSprite(Sprite *);
		void RemoveSprite(const Sprite *);

		void AddText(Text *);
		void RemoveText(Text *);
		void RenderText(float, float, const char *);
};