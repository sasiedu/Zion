#include <zion.h>

void    checkKeys(Zion::Window& win, Zion::Camera& camera)
{
	if (win.isKeyPressed(GLFW_KEY_A))
		camera.moveLeft(2.5f);
	if (win.isKeyPressed(GLFW_KEY_D))
		camera.moveRight(2.5f);
	if (win.isKeyPressed(GLFW_KEY_W))
		camera.moveForward(2.5f);
	if (win.isKeyPressed(GLFW_KEY_S))
		camera.moveBackward(2.5f);
}

int     main(int ac, char **av)
{
	Zion::Window    win;
	Zion::Shader    shader;
	Zion::Renderer  renderer;
	Zion::Camera    camera =  Zion::Camera(glm::vec3(0, 0, 3));
	Zion::Gltf      model;
	glm::mat4       trans;

	win.initWindow("Test",  1280, 760);
	shader.initShader("shaders/basic.vert", "shaders/basic.frag");

	glm::mat4   proj_mat = glm::perspective(glm::radians(70.0f), (float)1280 / (float)960, 0.1f, 100.0f);
	shader.setUniformMat4((GLchar *)"proj_matrix", proj_mat);

	Zion::SquareSprite square(shader, 0.0, 0.0, 0.5, 0.5);
	square.addBaseColor({0.0, 1.0, 0.0, 1.0});
	//renderer.addToRender(&square, glm::translate(glm::mat4(), glm::vec3(0, 0, -1)));

	Zion::CubeSprite cube(shader, 0, 0, 0, 2.5, 2.5, 2.5);
	cube.addTextureFromFile("textures/floor.png");
	//renderer.addToRender(&cube, glm::translate(glm::mat4(), glm::vec3(0, 0, -3)));

	Zion::Material material;
	//material.texure.loadTextureFromPath("models/OnileDiffuseColor.png");
	model.loadFromFile(shader, "models/enemy1.gltf");
	//model.addMaterial(0, material);
	renderer.addToRender(&model, glm::translate(trans, glm::vec3(0, 0, -5)));
	renderer.addToRender(&model, glm::translate(trans, glm::vec3(5, 0, -5)));
	renderer.addToRender(&model, glm::translate(trans, glm::vec3(-5, 0, -5)));


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