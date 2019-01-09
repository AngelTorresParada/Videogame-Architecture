#pragma once
#include "ApplicationMode.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "globals.h"

class ApplicationModePause : public ApplicationMode {

	IdApplicationMode id;

	bool change;
	int selectedOption = 0; 

	bool upPressed;
	bool downPressed;
	bool spacePressed;

	void setTexts(const char *);
	std::string titleText;
	std::string resumeText;
	std::string optionsText;
	std::string quitText;

public:
	ApplicationModePause();
	~ApplicationModePause();

	virtual void Run();
	virtual void ProcessInput();
	virtual void Render();
	virtual IdApplicationMode GetIdApplicationMode();

	GLuint texBlock;
};