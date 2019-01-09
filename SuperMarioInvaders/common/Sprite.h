#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"

class Sprite {
	public:

		GLuint texture;
		float x;
		float y;
		float height;
		float width;

		Sprite(GLuint, float, float, float, float);
		~Sprite();

		void Render();
};