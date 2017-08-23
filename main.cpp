#include <zion.h>

int     main(int ac, char **av)
{
	Zion::Window    win;
	Zion::Shader    shader;

	win.initWindow("Test",  960, 540);
	shader.initShader("shaders/basic.vert", "shaders/basic.frag");

	Zion::SquareSprite square(shader, 0.5, 0.5, 0.5, 0.5);

	while (!win.shouldClose() && !win.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		win.clearWindow(0.0f, 0.0f, 0.0f, 1.0f);
		square.render(glm::mat4());
		win.updateWindow();
	}
	return 0;
}