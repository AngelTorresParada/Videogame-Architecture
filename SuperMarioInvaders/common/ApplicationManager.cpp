#include "ApplicationManager.h"
#include "AudioSource.h"

void ApplicationManager::playMusic(AudioSource *_source) {
	_source->play();
}


void ApplicationManager::stopMusic(AudioSource *_source) {
	_source->stop();
}


ApplicationManager::ApplicationManager(ApplicationMode *_activeMode = nullptr) {
	activeMode = _activeMode;
}

ApplicationMode::IdApplicationMode ApplicationManager::ManageMode(ApplicationMode::IdApplicationMode _desiredId) {
	if (activeMode && activeMode->GetIdApplicationMode() != _desiredId) {
		delete activeMode;
		activeMode = nullptr;
	}

	if (!activeMode) {
		switch (_desiredId) {
			case ApplicationMode::AM_MENU:
				activeMode = new ApplicationModeMenu();
				break;
			case ApplicationMode::AM_GAME:
				activeMode = new ApplicationModeGame();
				break;
			case ApplicationMode::AM_PAUSE:
				activeMode = new ApplicationModePause();
				break;
			case ApplicationMode::AM_GAMEOVER:
				activeMode = new ApplicationModeGameOver();
				dynamic_cast<ApplicationModeGameOver *>(activeMode)->level = level;
				break;
			case ApplicationMode::AM_OPTIONS:
				activeMode = new ApplicationModeOptions();
				break;
			case ApplicationMode::AM_LEVELS:
				activeMode = new ApplicationModeLevels();
				break;
			default:
				activeMode = nullptr;
				return ApplicationMode::AM_NULL;
		}
	}

	return activeMode->GetIdApplicationMode();
}

ApplicationMode::IdApplicationMode ApplicationManager::ManageMode(ApplicationMode::IdApplicationMode _desiredId, int _level) {
	if (activeMode && activeMode->GetIdApplicationMode() != _desiredId) {
		delete activeMode;
		activeMode = nullptr;
	}
	activeMode = new ApplicationModeGame(_level);
	return activeMode->GetIdApplicationMode();
}

void ApplicationManager::Run() {
	if (activeMode)
		activeMode->Run();
}


void ApplicationManager::ProcessInput() {
	if (activeMode)
		activeMode->ProcessInput();
}


void ApplicationManager::Render() {
	if (activeMode)
		activeMode->Render();
}