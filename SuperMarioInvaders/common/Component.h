#pragma once
#include "Message.h"

class Component {
	public:
		virtual void Run() = 0;
		virtual void ProcessMessage(Message *) = 0;
};