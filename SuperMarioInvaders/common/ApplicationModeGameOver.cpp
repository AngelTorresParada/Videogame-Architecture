#include "ApplicationModeGameOver.h"
#include "ApplicationManager.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "Options.h"
#include "globals.h"

void ApplicationModeGameOver::setTexts(const char *_filename) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);
	if (result) {
		pugi::xml_node menu;
		switch (g_options->language) {
		case 0:
			menu = doc.child("english").child("gameover");
			break;
		case 1:
			menu = doc.child("spanish").child("gameover");
			break;
		}
		titleText = menu.child("title").attribute("text").as_string();
		newText = menu.child("new").attribute("text").as_string();
		quitText = menu.child("quit").attribute("text").as_string();
	}
}

ApplicationModeGameOver::ApplicationModeGameOver() {
	id = AM_GAMEOVER;
	setTexts("../data/Texts.tmx");
	texBlock = CORE_LoadPNG("../data/blockBkg.png", true);

	change = false;
	FONT_Init();

	upPressed = false;
	downPressed = false;
	spacePressed = true;
}


ApplicationModeGameOver::~ApplicationModeGameOver() {
}


void ApplicationModeGameOver::Run() {
	if (change) {
		switch (selectedOption) {
		case 0:
			g_manager->ManageMode(ApplicationMode::AM_GAME, level);
			break;
		case 1:
			g_manager->ManageMode(ApplicationMode::AM_MENU);
			break;
		}
	}
}

void ApplicationModeGameOver::ProcessInput() {
	if (SYS_KeyPressed(SYS_KEY_UP) && !upPressed) {
		upPressed = true;
		selectedOption--;
		if (selectedOption < 0) selectedOption = 1;
	}
	else if (!SYS_KeyPressed(SYS_KEY_UP)) upPressed = false;

	if (SYS_KeyPressed(SYS_KEY_DOWN) && !downPressed) {
		downPressed = true;
		selectedOption++;
		if (selectedOption > 1) selectedOption = 0;
	}
	else if (!SYS_KeyPressed(SYS_KEY_DOWN)) downPressed = false;

	if (SYS_KeyPressed(SYS_KEY_SPACE) && !spacePressed) {
		change = true;
	}
	else if (!SYS_KeyPressed(SYS_KEY_SPACE)) spacePressed = false;
}

void ApplicationModeGameOver::Render() {
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

	}

	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 400), titleText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 250), newText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 200), quitText.c_str());

	SYS_Show();
	SYS_Pump();
	SYS_Sleep(25);
}

ApplicationMode::IdApplicationMode ApplicationModeGameOver::GetIdApplicationMode() {
	return id;
}
