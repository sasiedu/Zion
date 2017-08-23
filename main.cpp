#include <zion.h>

int     main(int ac, char **av)
{
	Zion::Window    win;
	Zion::Shader    shader;

	win.initWindow("Test",  960, 540);
	shader.initShader("shaders/basic.vert", "shaders/basic.frag");

	glm::mat4   proj_mat = glm::perspective(90.0f, 1.0f * (960 / 540), 0.1f, 1000.0f);

	shader.setUniformMat4((GLchar *)"proj_matrix", proj_mat);

	Zion::SquareSprite square(shader, 0.0, 0.0, 0.5, 0.5);
	square.addBaseColor({0.0, 1.0, 0.0, 1.0});
	Zion::CubeSprite cube(shader, 0, 0.0, 0, 0.3, 0.3, 0.3);
	//cube.addBaseColor({0.0, 0.0, 1.0, 1.0});
	cube.addTextureFromFile("textures/floor.png");
	//Zion::SquareSprite square1(shader, -0.5, 0.5, 0.5, 0.5);
	//square1.addTextureFromFile("textures/floor.png");

	glm::mat4 rot = glm::rotate(glm::mat4(), 45.0f, glm::vec3(0, 1, 0));
	glm::mat4 trans = glm::translate(glm::mat4(), glm::vec3(0, 0, -0.6));
	glm::mat4 mat = trans * rot;

	while (!win.shouldClose() && !win.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		win.clearWindow(0.0f, 0.0f, 0.0f, 1.0f);
		square.render(glm::translate(glm::mat4(), glm::vec3(0, 0, -1)));
		cube.render(mat);
		//square1.render(glm::mat4());
		win.updateWindow();
	}
	return 0;
}