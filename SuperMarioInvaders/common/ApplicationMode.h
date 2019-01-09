#pragma once

class ApplicationMode {
	public:
		enum IdApplicationMode {
			AM_NULL,
			AM_MENU,
			AM_GAME,
			AM_PAUSE,
			AM_OPTIONS,
			AM_GAMEOVER,
			AM_LEVELS
		};

		virtual void Run() = 0;
		virtual void ProcessInput() = 0;
		virtual void Render() = 0;
		virtual IdApplicationMode GetIdApplicationMode() = 0;
};
