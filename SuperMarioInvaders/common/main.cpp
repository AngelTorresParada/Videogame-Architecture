#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "../SuperMarioInvaders/lib/alc.h"
#include "../SuperMarioInvaders/lib/al.h"
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioListener.h"


#include "Game.h"
#include "ApplicationManager.h"
#include "ApplicationMode.h"
#include "Options.h"
#include "globals.h"

#include <string>



Game *g_game = nullptr;
ApplicationManager *g_manager = nullptr;
Options *g_options;
AudioSource *g_source;



int Main(void) {

	g_manager = new ApplicationManager(nullptr);
	g_game = nullptr;
	g_options = new Options;
	g_options->isMusicOn = true;
	g_options->language = 0;


	ApplicationMode::IdApplicationMode mode = ApplicationMode::AM_MENU;

	// Set up rendering
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
	glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ALCdevice *device = alcOpenDevice(nullptr);
	ALCcontext *context = alcCreateContext(device, nullptr);

	alcMakeContextCurrent(context);

	AudioBuffer *buffer = AudioBuffer::load("../data/music.wav");
	g_source = new AudioSource(buffer);

	g_manager->playMusic(g_source);
	g_source->setLooping(true);

	while (!SYS_GottaQuit()) {
		g_manager->ManageMode(mode);
		g_manager->ProcessInput();
		g_manager->Run();
		g_manager->Render();
		if (!g_manager->activeMode)
			break;
		else
			mode = g_manager->activeMode->GetIdApplicationMode();
	}


	return 0;
}
