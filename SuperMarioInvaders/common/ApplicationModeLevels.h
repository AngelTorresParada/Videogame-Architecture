#pragma once
#include "ApplicationMode.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "globals.h"

class ApplicationModeLevels : public ApplicationMode {

	IdApplicationMode id;

	bool change;
	int selectedOption = 0;

	bool upPressed;
	bool downPressed;
	bool spacePressed;

	void setTexts(const char *);
	std::string titleText;
	std::string easyText;
	std::string normalText;
	std::string hardText;
	std::string returnText;

public:
	ApplicationModeLevels();
	~ApplicationModeLevels();

	virtual void Run();
	virtual void ProcessInput();
	virtual void Render();
	virtual IdApplicationMode GetIdApplicationMode();

	GLuint texBlock;
};