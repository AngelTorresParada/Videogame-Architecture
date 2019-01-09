
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"
#include "GraphicsEngine.h"
#include "Options.h"
#include "globals.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "Block.h"

#define BLOCK_W 30.0f


void Game::SendMessage(Message *_msg) {
	DestroyBulletMessage *destroyBullet = dynamic_cast<DestroyBulletMessage *>(_msg);
	if (destroyBullet) {
		for (auto e = entities.begin(); e != entities.end();) {
			Bullet *b = dynamic_cast<Bullet *>(*e);
			if (b && b->getOwner() == Bullet::PLAYER) {
				removeSprite(*e);
				e = entities.erase(e);
				playerShot = false;
			}
			else {
				++e;
			}
		}
	}
	else {
		CreateBulletMessage *createBullet = dynamic_cast<CreateBulletMessage *>(_msg);
		if (createBullet && !playerShot) {
			float x, y;
			player->getTransform()->getPosition(&x, &y);
			Bullet *b = new Bullet(this, x, y + 30, createBullet->owner);
			entities.push_back(b);
			addNewSprite(b);
			playerShot = true;
		}
		else {
			EntityHitMessage *entityHit = dynamic_cast<EntityHitMessage *>(_msg);
			if (entityHit) {
				for (auto e = entities.begin(); e != entities.end(); ++e) {
					if ((*e) == entityHit->hitEntity) {
						if (dynamic_cast<Enemy *>(*e) || dynamic_cast<Boss *>(*e)) {
							if (dynamic_cast<Boss *>(*e)) {
								cyclesToBoss = BOSS_CYCLE;
								score += 50;
							}
							else {
								numEnemies--;
								score += 10;
							}
							removeSprite(*e);
							entities.erase(e);
							PartnerKilledMessage *msg1 = new PartnerKilledMessage;
							SendMessage(msg1);
							DestroyBulletMessage *msg2 = new DestroyBulletMessage;
							SendMessage(msg2);
							break;
						}
						else
							if (dynamic_cast<Player *>(*e)) {
								removeSprite(*e);
								entities.erase(e);
								DestroyEnemyBulletMessage *msg = new DestroyEnemyBulletMessage;
								SendMessage(msg);
								isGameOver = true;
								break;
							}
							else {
								removeSprite(*e);
								entities.erase(e);
								DestroyEnemyBulletMessage *msg = new DestroyEnemyBulletMessage;
								SendMessage(msg);
								break;
							}
					}
				}
			}
			else {
				if (dynamic_cast<InvokeDirectionChangeMessage *>(_msg)) {
					ChangeDirectionMessage *msg = new ChangeDirectionMessage;
					SendMessage(msg);
				}
				else {
					if (dynamic_cast<DestroyBossMessage *>(_msg)) {
						for (auto e = entities.begin(); e != entities.end(); ++e) {
							if (dynamic_cast<Boss *>(*e)) {
								cyclesToBoss = BOSS_CYCLE;
								removeSprite(*e);
								entities.erase(e);
								break;
							}
						}
					}
					else {
						DestroyEnemyBulletMessage *destroyBullet = dynamic_cast<DestroyEnemyBulletMessage *>(_msg);
						if (destroyBullet) {
							for (auto e = entities.begin(); e != entities.end();) {
								Bullet *b = dynamic_cast<Bullet *>(*e);
								if (b && b->getOwner() == Bullet::ENEMY) {
									removeSprite(*e);
									e = entities.erase(e);
								}
								else {
									++e;
								}
							}
						}
						else {
							if (dynamic_cast<GameOverMessage *>(_msg)) {
								isGameOver = true;
							}
							else {
								for (int i = 0; i < entities.size(); ++i) {
									entities[i]->RecieveMessage(_msg);
								}
							}
						}
					}
				}
			}
		}
	}
	
}


void Game::addBlocks() {
	int maxValue = (SCR_WIDTH - 75) / static_cast<int>(BLOCK_WIDTH);
	for (int i = 0; i < maxValue; i++) {
		if (i % 6 != 4 && i % 6 != 5 && i % 6 != 0) {
			Block *b = new Block(this, i * BLOCK_WIDTH + 75, 120);
			entities.push_back(b);
		}
	}
}


void Game::addEnemies(const char *_filename, ApplicationModeGame::Difficulty _difficulty) {
	char *diff = new char[7];
	switch (_difficulty) {
		case ApplicationModeGame::Difficulty::EASY:
			diff = "easy";
			break;
		case ApplicationModeGame::Difficulty::NORMAL:
			diff = "normal";
			break;
		case ApplicationModeGame::Difficulty::HARD:
			diff = "hard";
			break;
	}

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);
	if (result) {
		pugi::xml_node difficulty = doc.child(diff);
		for (pugi::xml_node node = difficulty.child("enemymap").child("enemy"); node; node = node.next_sibling("enemy")) {
			float x = node.attribute("x").as_float();
			float y = node.attribute("y").as_float();
			Enemy *e = new Enemy(this, x, y);
			e->setSpeed(difficulty.child("speed").attribute("speed").as_float() * reEnemies);
			entities.push_back(e);
			addNewSprite(e);
			numEnemies++;
		}
	}
}


void Game::setTexts(const char *_filename) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);
	if (result) {
		pugi::xml_node menu;
		switch (g_options->language) {
		case 0:
			menu = doc.child("english").child("game");
			break;
		case 1:
			menu = doc.child("spanish").child("game");
			break;
		}
		scrText = menu.child("score").attribute("text").as_string();
		easyText = menu.child("easy").attribute("text").as_string();
		normalText = menu.child("normal").attribute("text").as_string();
		hardText = menu.child("hard").attribute("text").as_string();
	}
}


Game::Game(ApplicationModeGame::Difficulty _difficulty) {

	player = new Player(this, SCR_WIDTH / 2, PLAYER_Y);

	setTexts("../data/Texts.tmx");

	level = _difficulty;

	entities.push_back(player);

	addBlocks();

	scoreString = scrText;
	scoreString.append(std::to_string(score));
	scoreText = new Text;
	scoreText->x = 50;
	scoreText->y = 550;
	scoreText->text = scoreString.c_str();

	switch (_difficulty) {
		case ApplicationModeGame::Difficulty::EASY:
			levelString = easyText;
			break;
		case ApplicationModeGame::Difficulty::NORMAL:
			levelString = normalText;
			break;
		case ApplicationModeGame::Difficulty::HARD:
			levelString = hardText;
			break;
	}

	levelText = new Text;
	levelText->x = 550;
	levelText->y = 550;
	levelText->text = levelString.c_str();

	GLuint texBlock = CORE_LoadPNG("../data/blockBkg.png", true);
	for (int i = 0; i <= SCR_WIDTH / BLOCK_W; i++) {
		Sprite *s = new Sprite(texBlock, BLOCK_W * i + BLOCK_W/2, BLOCK_W/2, BLOCK_W, BLOCK_W);
		worldSprites.push_back(s);
	}

	isGameOver = false;
}


Game::~Game() {
	while (!entities.empty()) {
		entities.pop_back();
	}

	delete scoreText;
	delete levelText;
}


void Game::Run() {

	if (!isGameOver) {
		cyclesToBoss--;
		cyclesToShot--;

		if (cyclesToBoss == 0) {
			Boss *boss = new Boss(this, SCR_WIDTH + 50, 450);
			entities.push_back(boss);
			addNewSprite(boss);
		}

		if (cyclesToShot == 0) {

			for (auto e : entities) {
				if (dynamic_cast<Enemy *>(e)) {
					int value = rand() % numEnemies;
					if (value <= 3) {
						float x, y;
						e->getTransform()->getPosition(&x, &y);
						Bullet *bullet = new Bullet(this, x, y - 30, Bullet::ENEMY);
						entities.push_back(bullet);
						addNewSprite(bullet);
						cyclesToShot = SHOT_CYCLE;
						break;
					}
				}
			}

		}

		for (int i = 0; i < entities.size(); i++) {
			entities[i]->Run();
		}

		scoreString = scrText;
		scoreString.append(std::to_string(score));

		if (numEnemies == 0) {
			reEnemies++;
			addEnemies("../data/Enemies.tmx", level);
		}
	}
}

void Game::RecieveMessage(Message *_msg) {
	SendMessage(_msg);
}

void Game::setGraphicsEngine(GraphicsEngine *_engine) {
	engine = _engine;
	engine->AddText(scoreText);
	engine->AddText(levelText);
}

void Game::addNewSprite(GameObject *_entity) {
	engine->AddSprite(_entity->getSprite());
}

void Game::removeSprite(GameObject *_entity) {
	engine->RemoveSprite(_entity->getSprite());
}


