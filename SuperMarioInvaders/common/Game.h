#pragma once
#include "ApplicationModeGame.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "GameObject.h"
#include "Message.h"
#include <string>


#define PLAYER_Y 45
#define ENEMIES_X 50
#define ENEMIES_Y 240
#define BOSS_Y 420

#define NUM_ENEMIES_X 10
#define NUM_ENEMIES_Y 5

#define BOSS_CYCLE 500
#define SHOT_CYCLE 200

class GraphicsEngine;


class Game{
	//Enemies *enemies;

	std::vector<GameObject *> entities;
	std::vector<Sprite *> worldSprites;
	bool playerShot = false;
	GameObject *player;
	GraphicsEngine *engine;
	int cyclesToBoss = BOSS_CYCLE;
	int cyclesToShot = SHOT_CYCLE;

	int numEnemies = 0;
	int reEnemies = 1;

	Text *scoreText;
	std::string scoreString;
	int score = 0;

	Text *levelText;
	std::string levelString;

	void addEnemies(const char *, ApplicationModeGame::Difficulty);
	void SendMessage(Message *);

	void addBlocks();

	std::string scrText;
	std::string easyText;
	std::string normalText;
	std::string hardText;


	public:
		void setTexts(const char *);

		ApplicationModeGame::Difficulty level;

		Game(ApplicationModeGame::Difficulty);
		~Game();

		std::vector<GameObject *>getEntities() { return entities; }
		std::vector<Sprite *>getWorldSprites() { return worldSprites; }

		void Run();

		void RecieveMessage(Message *);

		void setGraphicsEngine(GraphicsEngine *);
		void addNewSprite(GameObject *);
		void removeSprite(GameObject *);

		bool isGameOver;

};