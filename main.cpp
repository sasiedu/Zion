#include <zion.h>

void    checkKeys(Zion::Window& win, Zion::Camera& camera)
{
	if (win.isKeyPressed(GLFW_KEY_A))
		camera.moveLeft(2.5f);
	if (win.isKeyPressed(GLFW_KEY_D))
		camera.moveRight(2.5f);
	if (win.isKeyPressed(GLFW_KEY_W))
		camera.moveIn(2.5f);
	if (win.isKeyPressed(GLFW_KEY_S))
		camera.moveOut(2.5f);
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

	glm::mat4   proj_mat = glm::perspective(glm::radians(70.0f), 960.0f / 540.0f, 0.1f, 1000.0f);
	shader.setUniformMat4((GLchar *)"proj_matrix", proj_mat);

	Zion::SquareSprite square(shader, 0.0, 0.0, 0.5, 0.5);
	square.addBaseColor({0.0, 1.0, 0.0, 1.0});
	//renderer.addToRender(&square, glm::translate(glm::mat4(), glm::vec3(0, 0, -1)));

	Zion::CubeSprite cube(shader, 0, 0, 0, 2.5, 2.5, 2.5);
	cube.addTextureFromFile("textures/floor.png");
	renderer.addToRender(&cube, glm::translate(glm::mat4(), glm::vec3(0, 0, -3)));

	model.loadFromFile(shader, "models/bomberman.gltf");
	renderer.addToRender(&model, glm::translate(glm::mat4(), glm::vec3(0, 0, -3)));
	renderer.addToRender(&model, glm::translate(glm::mat4(), glm::vec3(5, 0, -3)));
	renderer.addToRender(&model, glm::translate(glm::mat4(), glm::vec3(-5, 0, -3)));


	Zion::Renderable::startTime = (float)glfwGetTime();
	Zion::Renderable::runTime = Zion::Renderable::startTime;
	while (!win.shouldClose() && !win.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		auto currentTime = (float)glfwGetTime();
		Zion::Renderable::deltaTime = currentTime - Zion::Renderable::runTime;
		Zion::Renderable::runTime = currentTime;

		win.clearWindow(0.0f, 0.0f, 0.0f, 1.0f);
		checkKeys(win, camera);
		shader.setUniformMat4((GLchar *)"view_matrix", camera.getViewMatrix());
		renderer.render();
		win.updateWindow();
	}
	return 0;
}