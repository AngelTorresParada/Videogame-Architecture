#include "ApplicationModePause.h"
#include "ApplicationManager.h"
#include "Options.h"
#include "globals.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"

void ApplicationModePause::setTexts(const char *_filename) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);
	if (result) {
		pugi::xml_node menu;
		switch (g_options->language) {
		case 0:
			menu = doc.child("english").child("pause");
			break;
		case 1:
			menu = doc.child("spanish").child("pause");
			break;
		}
		titleText = menu.child("title").attribute("text").as_string();
		resumeText = menu.child("resume").attribute("text").as_string();
		optionsText = menu.child("options").attribute("text").as_string();
		quitText = menu.child("quit").attribute("text").as_string();
	}
}


ApplicationModePause::ApplicationModePause() {
	setTexts("../data/Texts.tmx");
	id = AM_PAUSE;
	texBlock = CORE_LoadPNG("../data/blockBkg.png", true);

	change = false;
	FONT_Init();

	upPressed = false;
	downPressed = false;
	spacePressed = true;
}


ApplicationModePause::~ApplicationModePause() {
}


void ApplicationModePause::Run() {
	if (change) {
		switch (selectedOption) {
		case 0:
			g_manager->ManageMode(ApplicationMode::AM_GAME);
			break;
		case 1:
			g_manager->reservedMode = id;
			g_manager->ManageMode(ApplicationMode::AM_OPTIONS);
			break;
		case 2:
			delete g_game;
			g_game = nullptr;
			g_manager->ManageMode(ApplicationMode::AM_MENU);
			break;
		}
	}
}


void ApplicationModePause::ProcessInput() {
	if (SYS_KeyPressed(SYS_KEY_UP) && !upPressed) {
		upPressed = true;
		selectedOption--;
		if (selectedOption < 0) selectedOption = 2;
	}
	else if (!SYS_KeyPressed(SYS_KEY_UP)) upPressed = false;

	if (SYS_KeyPressed(SYS_KEY_DOWN) && !downPressed) {
		downPressed = true;
		selectedOption++;
		if (selectedOption > 2) selectedOption = 0;
	}
	else if (!SYS_KeyPressed(SYS_KEY_DOWN)) downPressed = false;

	if (SYS_KeyPressed(SYS_KEY_SPACE) && !spacePressed) {
		change = true;
	}
	else if (!SYS_KeyPressed(SYS_KEY_SPACE)) spacePressed = false;
}


void ApplicationModePause::Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i <= SCR_WIDTH / 50 + 1; ++i) {
		CORE_RenderCenteredSprite(vmake(i * 50.f + 25.f, 25.f), vmake(50, 50), texBlock);
	}

	switch (selectedOption) {
	case 0:
		CORE_RenderCenteredSprite(vmake(SCR_WIDTH / 2 - 125, 260), vmake(20, 20), texBlock);
		break;
	case 1:
		CORE_RenderCenteredSprite(vmake(SCR_WIDTH / 2 - 125, 210), vmake(20, 20), texBlock);
		break;
	case 2:
		CORE_RenderCenteredSprite(vmake(SCR_WIDTH / 2 - 125, 160), vmake(20, 20), texBlock);
		break;
	}

	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 400), titleText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 250), resumeText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 200), optionsText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 150), quitText.c_str());

	SYS_Show();
	SYS_Pump();
	SYS_Sleep(25);
}

ApplicationMode::IdApplicationMode ApplicationModePause::GetIdApplicationMode() {
	return id;
}
