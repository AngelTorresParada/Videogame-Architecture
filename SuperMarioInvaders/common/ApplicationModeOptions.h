#pragma once

#include "ApplicationMode.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "globals.h"

class ApplicationModeOptions : public ApplicationMode {

	IdApplicationMode id;

	bool change;
	int selectedOption = 0;

	bool upPressed;
	bool downPressed;
	bool spacePressed;

	void setTexts(const char *);
	std::string titleText;
	std::string musicText;
	std::string onText;
	std::string offText;
	std::string languageText;
	std::string englishText;
	std::string spanishText;
	std::string returnText;

public:
	ApplicationModeOptions();
	~ApplicationModeOptions();

	virtual void Run();
	virtual void ProcessInput();
	virtual void Render();
	virtual IdApplicationMode GetIdApplicationMode();

	GLuint texBlock;
};