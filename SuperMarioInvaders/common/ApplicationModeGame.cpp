#pragma once

#include "globals.h"
#include "ApplicationMode.h"
#include "ApplicationModeGame.h"
#include "ApplicationManager.h"
#include "InputManager.h"
#include "Game.h"


void ApplicationModeGame::SetGameOver() {
	if (g_game->isGameOver) {
		g_manager->level = g_game->level;
		delete g_game;
		g_game = nullptr;
		g_manager->ManageMode(AM_GAMEOVER);
	}
}


ApplicationModeGame::ApplicationModeGame() {
	id = AM_GAME;
	if (!g_game) {
		g_game = new Game(EASY);
	}
	engine = new GraphicsEngine(g_game);
	inputManager = new InputManager(g_game);

	spacePressed = true;
}


ApplicationModeGame::ApplicationModeGame(int _level) {
	id = AM_GAME;
	
	if (!g_game) {
		switch (_level) {
			case 0:
				g_game = new Game(EASY);
				break;
			case 1:
				g_game = new Game(NORMAL);
				break;
			case 2:
				g_game = new Game(HARD);
				break;
			default:
				g_game = new Game(EASY);
		}
		
	}
	engine = new GraphicsEngine(g_game);
	inputManager = new InputManager(g_game);

	spacePressed = true;
}


ApplicationModeGame::~ApplicationModeGame() {
	delete g_game;
	delete engine;
	delete inputManager;
}


void ApplicationModeGame::Run() {
	SetGameOver();
	if (g_game)
		g_game->Run();

}


void ApplicationModeGame::ProcessInput() {
	Message *msg;
	if (SYS_KeyPressed(SYS_KEY_LEFT)) {
		msg = new MoveLeftMessage;
	}
	else {
		if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
			msg = new MoveRightMessage;
		}
		else {
			if (SYS_KeyPressed(SYS_KEY_UP)) {
				CreateBulletMessage *createBullet = new CreateBulletMessage;
				createBullet->owner = Bullet::PLAYER;
				msg = createBullet;
			}
			else {
				if (SYS_KeyPressed(SYS_KEY_SPACE) && !spacePressed) {
					g_manager->ManageMode(AM_PAUSE);
				}
				else if (!SYS_KeyPressed(SYS_KEY_SPACE)) {
					spacePressed = false;
				}
				msg = nullptr;
				return;
			}
		}
	}
	inputManager->SendMessage(msg);
}


void ApplicationModeGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	engine->Render();
	SYS_Show();
	SYS_Pump();
	SYS_Sleep(25);
}


ApplicationMode::IdApplicationMode ApplicationModeGame::GetIdApplicationMode() {
	return id;
}
