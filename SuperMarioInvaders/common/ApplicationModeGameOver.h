#pragma once
#include "ApplicationMode.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "globals.h"
#include "ApplicationModeGame.h"

class ApplicationModeGameOver : public ApplicationMode {

	IdApplicationMode id;

	bool change;
	int selectedOption = 0;

	bool upPressed;
	bool downPressed;
	bool spacePressed;

	int waitForIntro;

	void setTexts(const char *);
	std::string titleText;
	std::string newText;
	std::string quitText;

	

public:
	ApplicationModeGame::Difficulty level;

	ApplicationModeGameOver();
	~ApplicationModeGameOver();

	virtual void Run();
	virtual void ProcessInput();
	virtual void Render();
	virtual IdApplicationMode GetIdApplicationMode();

	GLuint texBlock;
};