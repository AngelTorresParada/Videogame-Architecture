#include "ApplicationModeLevels.h"
#include "ApplicationManager.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "Options.h"
#include "globals.h"

void ApplicationModeLevels::setTexts(const char *_filename) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);
	if (result) {
		pugi::xml_node menu;
		switch (g_options->language) {
		case 0:
			menu = doc.child("english").child("levels");
			break;
		case 1:
			menu = doc.child("spanish").child("levels");
			break;
		}
		titleText = menu.child("title").attribute("text").as_string();
		easyText = menu.child("easy").attribute("text").as_string();
		normalText = menu.child("normal").attribute("text").as_string();
		hardText = menu.child("hard").attribute("text").as_string();
		returnText = menu.child("return").attribute("text").as_string();
	}
}

ApplicationModeLevels::ApplicationModeLevels() {
	setTexts("../data/Texts.tmx");

	id = AM_PAUSE;
	texBlock = CORE_LoadPNG("../data/blockBkg.png", true);

	change = false;
	FONT_Init();

	upPressed = false;
	downPressed = false;
	spacePressed = true;
}


ApplicationModeLevels::~ApplicationModeLevels() {
}


void ApplicationModeLevels::Run() {
	int level = 0;
	if (change) {
		switch (selectedOption) {
		case 0:
			level = 0;
			break;
		case 1:
			level = 1;
			break;
		case 2:
			level = 2;
			break;
		case 3:
			g_manager->ManageMode(ApplicationMode::AM_MENU);
			return;
		}
		g_manager->ManageMode(ApplicationMode::AM_GAME, level);
	}
}

void ApplicationModeLevels::ProcessInput() {
	if (SYS_KeyPressed(SYS_KEY_UP) && !upPressed) {
		upPressed = true;
		selectedOption--;
		if (selectedOption < 0) selectedOption = 3;
	}
	else if (!SYS_KeyPressed(SYS_KEY_UP)) upPressed = false;

	if (SYS_KeyPressed(SYS_KEY_DOWN) && !downPressed) {
		downPressed = true;
		selectedOption++;
		if (selectedOption > 3) selectedOption = 0;
	}
	else if (!SYS_KeyPressed(SYS_KEY_DOWN)) downPressed = false;

	if (SYS_KeyPressed(SYS_KEY_SPACE) && !spacePressed) {
		change = true;
	}
	else if (!SYS_KeyPressed(SYS_KEY_SPACE)) spacePressed = false;
}

void ApplicationModeLevels::Render() {
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
	case 3:
		CORE_RenderCenteredSprite(vmake(SCR_WIDTH / 2 - 125, 110), vmake(20, 20), texBlock);
		break;
	}

	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 400), titleText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 250), easyText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 200), normalText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 150), hardText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 100), returnText.c_str());


	SYS_Show();
	SYS_Pump();
	SYS_Sleep(25);
}

ApplicationMode::IdApplicationMode ApplicationModeLevels::GetIdApplicationMode() {
	return id;
}
