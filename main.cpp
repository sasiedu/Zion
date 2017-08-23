#include <zion.h>

int     main(int ac, char **av)
{
	Zion::Window    win;

	win.initWindow("Test",  960, 540);
	while (!win.shouldClose() && !win.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		win.clearWindow(0.0f, 0.0f, 0.0f, 1.0f);
		win.updateWindow();
	}
	return 0;
}