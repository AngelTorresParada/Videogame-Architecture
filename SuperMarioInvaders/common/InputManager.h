#pragma once
#include "Game.h"
#include "Message.h"


class InputManager {
	Game *game;
	public:
		InputManager(Game *);
		~InputManager();

		void SendMessage(Message *);


};