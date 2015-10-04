#include "game/game.h"
#include "console_gfx/screen.h"

int main()
{
	console::screen scr;
        conway::game gam(scr.width(), scr.height());
        gam.run();
        return 0;
}
