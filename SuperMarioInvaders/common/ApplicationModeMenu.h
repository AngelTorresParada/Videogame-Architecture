#pragma once

#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"

#include "ApplicationMode.h"

#include <string>


class ApplicationModeMenu : public ApplicationMode {
	IdApplicationMode id;
	bool change;
	int selectedOption = 0;

	bool upPressed;
	bool downPressed;
	bool spacePressed;

	void setTexts(const char *);
	std::string playText;
	std::string optionsText;
	std::string quitText;

	public:
		ApplicationModeMenu();
		~ApplicationModeMenu();

		virtual void Run();
		virtual void ProcessInput();
		virtual void Render();
		virtual IdApplicationMode GetIdApplicationMode();

		GLuint texBlock;
};
