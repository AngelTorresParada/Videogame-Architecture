#include "InputManager.h"

InputManager::InputManager(Game *_game) {
	game = _game;
}


InputManager::~InputManager(){
}


void InputManager::SendMessage(Message *_msg) {
	game->RecieveMessage(_msg);
}
