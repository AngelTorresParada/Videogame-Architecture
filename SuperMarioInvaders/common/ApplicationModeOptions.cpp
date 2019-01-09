#include "ApplicationModeOptions.h"
#include "ApplicationManager.h"
#include "Game.h"
#include "Options.h"
#include "globals.h"
#include "pugixml.hpp"
#include "pugiconfig.hpp"

void ApplicationModeOptions::setTexts(const char *_filename) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);
	if (result) {
		pugi::xml_node menu;
		switch (g_options->language) {
		case 0:
			menu = doc.child("english").child("options");
			break;
		case 1:
			menu = doc.child("spanish").child("options");
			break;
		}
		titleText = menu.child("title").attribute("text").as_string();
		musicText = menu.child("music").attribute("text").as_string();
		onText = menu.child("m_on").attribute("text").as_string();
		offText = menu.child("m_off").attribute("text").as_string();
		languageText = menu.child("language").attribute("text").as_string();
		englishText = menu.child("l_eng").attribute("text").as_string();
		spanishText = menu.child("l_spa").attribute("text").as_string();
		returnText = menu.child("return").attribute("text").as_string();
	}
}


ApplicationModeOptions::ApplicationModeOptions() {
	setTexts("../data/Texts.tmx");
	id = AM_OPTIONS;
	texBlock = CORE_LoadPNG("../data/blockBkg.png", true);

	change = false;
	FONT_Init();

	upPressed = false;
	downPressed = false;
	spacePressed = true;
}


ApplicationModeOptions::~ApplicationModeOptions() {
}


void ApplicationModeOptions::Run() {
	if (change) {
		switch (selectedOption) {
		case 0:
			g_options->language = g_options->language == 0 ? 1 : 0;
			if (g_game)
				g_game->setTexts("../data/Texts.tmx");
			setTexts("../data/Texts.tmx");
			change = false;
			break;
		case 1:
			g_options->isMusicOn = g_options->isMusicOn ? false : true;
			g_options->isMusicOn ? g_manager->playMusic(g_source) : g_manager->stopMusic(g_source);
			change = false;
			break;
		case 2:
			switch (g_manager->reservedMode) {
				case ApplicationMode::AM_PAUSE:
					g_manager->ManageMode(ApplicationMode::AM_PAUSE);
					break;
				case ApplicationMode::AM_MENU:
					delete g_game;
					g_game = nullptr;
					g_manager->ManageMode(ApplicationMode::AM_MENU);
					break;
			}
			break;
		}
	}
}


void ApplicationModeOptions::ProcessInput() {
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
		spacePressed = true;
		change = true;
	}
	else if (!SYS_KeyPressed(SYS_KEY_SPACE)) {
		spacePressed = false;
		change = false;
	}
}


void ApplicationModeOptions::Render() {
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

	std::string ling = languageText;
	switch (g_options->language) {
		case 0:
			ling.append(englishText);
			break;
		case 1:
			ling.append(spanishText);
			break;
	}

	std::string sound = musicText;
	sound.append(g_options->isMusicOn ? onText : offText);

	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 400), titleText.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 250), ling.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 200), sound.c_str());
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 75, 150), returnText.c_str());

	SYS_Show();
	SYS_Pump();
	SYS_Sleep(25);
}


ApplicationMode::IdApplicationMode ApplicationModeOptions::GetIdApplicationMode() {
	return id;
}
