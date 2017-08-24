#include <zion.h>

void    checkKeys(Zion::Window& win, Zion::Camera& camera)
{
	if (win.isKeyPressed(GLFW_KEY_A))
		camera.moveLeft(0.002f);
	if (win.isKeyPressed(GLFW_KEY_D))
		camera.moveRight(0.002f);
	if (win.isKeyPressed(GLFW_KEY_W))
		camera.moveIn(0.002f);
	if (win.isKeyPressed(GLFW_KEY_S))
		camera.moveOut(0.002f);
}

int     main(int ac, char **av)
{
	Zion::Window    win;
	Zion::Shader    shader;
	Zion::Renderer  renderer;
	Zion::Camera    camera =  Zion::Camera(glm::vec3(0, 0, 1));
	Zion::Gltf      model;

	win.initWindow("Test",  960, 540);
	shader.initShader("shaders/basic.vert", "shaders/basic.frag");

	glm::mat4   proj_mat = glm::perspective(45.0f, 1.0f * (960 / 540), 0.1f, 1000.0f);
	shader.setUniformMat4((GLchar *)"proj_matrix", proj_mat);

	Zion::SquareSprite square(shader, 0.0, 0.0, 0.5, 0.5);
	square.addBaseColor({0.0, 1.0, 0.0, 1.0});
	//renderer.addToRender(&square, glm::translate(glm::mat4(), glm::vec3(0, 0, -1)));

	Zion::CubeSprite cube(shader, 0, 0, -2, 2.5, 2.5, 2.5);
	cube.addTextureFromFile("textures/floor.png");
	//renderer.addToRender(&cube, glm::translate(glm::mat4(), glm::vec3(-2, 0, 0)));

	model.loadFromFile(shader, "models/bomberman.gltf");
	//model.loadFromFile(shader, "models/box.glb");
	renderer.addToRender(&model, glm::translate(glm::mat4(), glm::vec3(0, 0, -2)));

	while (!win.shouldClose() && !win.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		win.clearWindow(0.0f, 0.0f, 0.0f, 1.0f);
		checkKeys(win, camera);
		shader.setUniformMat4((GLchar *)"view_matrix", camera.getViewMatrix());
		renderer.render();
		win.updateWindow();
	}
	return 0;
}