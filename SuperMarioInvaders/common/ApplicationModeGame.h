#pragma once
#include "ApplicationMode.h"
#include "GraphicsEngine.h"
#include <vector>

class InputManager;

class ApplicationModeGame : public ApplicationMode {

	IdApplicationMode id;
	GraphicsEngine *engine;
	InputManager *inputManager;

	bool spacePressed;

	void SetGameOver();

	public:
		ApplicationModeGame();
		ApplicationModeGame(int);
		~ApplicationModeGame();

		virtual void Run();
		virtual void ProcessInput();
		virtual void Render();
		virtual IdApplicationMode GetIdApplicationMode();

		enum Difficulty {
			EASY,
			NORMAL,
			HARD,
		};
};