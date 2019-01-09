#include "Options.h"

void Options::setLanguage() {
	language++;
	if (language > 1)
		language = 0;
	else if (language < 0)
		language = 1;
}
