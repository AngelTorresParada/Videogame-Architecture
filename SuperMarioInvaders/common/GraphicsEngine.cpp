#include "GraphicsEngine.h"
#include "Game.h"

GraphicsEngine::GraphicsEngine(Game *_game) {
	FONT_Init();

	_game->setGraphicsEngine(this);

	for (auto s : _game->getWorldSprites()) {
		sprites.push_back(s);
	}

	std::vector<GameObject *> entities = _game->getEntities();
	for (auto entity = entities.begin(); entity != entities.end(); ++entity) {
		sprites.push_back((*entity)->getSprite());
	}
	
}

GraphicsEngine::~GraphicsEngine() {
	while (!sprites.empty()) {
		sprites.pop_back();
	}
}


void GraphicsEngine::Render() {

	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->Render();
	}

	for (auto t = texts.begin(); t != texts.end(); ++t) {
		RenderText((*t)->x, (*t)->y, (*t)->text);
	}

}


void GraphicsEngine::AddSprite(Sprite *_sprite) {
	sprites.push_back(_sprite);
}


void GraphicsEngine::RemoveSprite(const Sprite *_sprite) {
	for (auto s = sprites.begin(); s != sprites.end(); ++s) {
		if ((*s) == _sprite) {
			sprites.erase(s);
			break;
		}
	}
	
}


void GraphicsEngine::AddText(Text *_text) {
	texts.push_back(_text);
}

void GraphicsEngine::RemoveText(Text *_text) {
	for (auto t = texts.begin(); t != texts.end(); ++t) {
		if ((*t) == _text) {
			texts.erase(t);
			break;
		}
	}
}


void GraphicsEngine::RenderText(float _x, float _y, const char *_text) {
	FONT_DrawString(vmake(_x, _y), _text);
}
