#include "globals.h"
#include "ApplicationModeMenu.h"
#include "ApplicationManager.h"
#include "GameObject.h"
#include "ApplicationModePause.h"
#include "Options.h"
#include "pugixml.hpp"
#include "pugiconfig.hpp"

#define PLAYER_Y 67.5
#define ENEMIES_X 50
#define ENEMIES_Y 240


void ApplicationModeMenu::setTexts(const char *_filename) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);
	if (result) {
		pugi::xml_node menu;
		switch (g_options->language) {
			case 0:
				menu = doc.child("english").child("menu");
				break;
			case 1:
				menu = doc.child("spanish").child("menu");
				break;
		}
		playText = menu.child("game").attribute("text").as_string();
		optionsText = menu.child("options").attribute("text").as_string();
		quitText = menu.child("quit").attribute("text").as_string();
	}
}

ApplicationModeMenu::ApplicationModeMenu() {
	id = AM_MENU;

	setTexts("../data/Texts.tmx");

	texBlock = CORE_LoadPNG("../data/blockBkg.png", true);

	

	change = false;

	FONT_Init();

}

ApplicationModeMenu::~ApplicationModeMenu() {
}


void ApplicationModeMenu::Run() {
	if (change) {
		switch (selectedOption) {
		case 0:
			g_manager->ManageMode(ApplicationMode::AM_LEVELS);
			break;
		case 1:
			g_manager->reservedMode = id;
			g_manager->ManageMode(ApplicationMode::AM_OPTIONS);
			break;
		case 2:
			g_manager->ManageMode(ApplicationMode::AM_NULL);
			break;
		}
	}
}


void ApplicationModeMenu::ProcessInput() {
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


void ApplicationModeMenu::Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i <= SCR_WIDTH / 50 + 1; ++i) {
		CORE_RenderCenteredSprite(vmake(i * 50.f + 25.f, 25.f), vmake(50, 50), texBlock);
	}

	GLuint title = CORE_LoadPNG("../data/SuperMarioInvaders.png", true);
	CORE_RenderCenteredSprite(vmake(SCR_WIDTH /2, 450), vmake(600, 150), title);

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

	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 250), playText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 200), optionsText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 150), quitText.c_str());

	SYS_Show();
	SYS_Pump();
	SYS_Sleep(25);
}


ApplicationMode::IdApplicationMode ApplicationModeMenu::GetIdApplicationMode() {
	return id;
}
