#pragma once
#include "ApplicationMode.h"
#include "ApplicationModeMenu.h"
#include "ApplicationModeGame.h"
#include "ApplicationModePause.h"
#include "ApplicationModeGameOver.h"
#include "ApplicationModeOptions.h"
#include "ApplicationModeLevels.h"

class AudioSource;

class ApplicationManager {

	

	public:
		void playMusic(AudioSource *);
		void stopMusic(AudioSource *);

		ApplicationModeGame::Difficulty level;
		ApplicationMode::IdApplicationMode reservedMode;

		ApplicationManager(ApplicationMode *);
		~ApplicationManager();

		ApplicationMode *activeMode;
		ApplicationMode::IdApplicationMode desiredMode;

		ApplicationMode::IdApplicationMode ManageMode(ApplicationMode::IdApplicationMode);
		ApplicationMode::IdApplicationMode ManageMode(ApplicationMode::IdApplicationMode, int);

		void Run();
		void ProcessInput();
		void Render();

		
};