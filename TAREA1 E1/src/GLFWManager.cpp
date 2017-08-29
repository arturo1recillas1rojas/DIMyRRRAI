/*
 * GLFWManager.cpp
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */
#include <GL/glew.h>
#include "Headers/GLFWManager.h"

int WindowManager::screenWidth = 800;
int WindowManager::screenHeight = 700;

GLFWManager::GLFWManager() :
		window(nullptr) {
}

GLFWManager::~GLFWManager() {
	destroy();
}

bool GLFWManager::initialize(int width, int height, std::string strTitle,
		bool bFullScreen) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	this->screenWidth = width;
	this->screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
				glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
				nullptr);

	if (window == nullptr) {
		std::cerr
				<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
				<< std::endl;
		destroy();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		return false;
	}

	return true;
}

bool GLFWManager::processInput(bool continueApplication = true) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
			|| glfwWindowShouldClose(window) != 0) {
		return false;
	}
	//Color Rojo oscuro al press => R
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS
		|| glfwWindowShouldClose(window) != 0) {
		glClearColor(0.4, 0.0, 0.0, 0.0);
	}//Color Verde oscuro al press => G
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS
		|| glfwWindowShouldClose(window) != 0) {
		glClearColor(0.0, 0.4, 0.0, 0.0);
	}//Color Azul oscuro al press => B
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS
		|| glfwWindowShouldClose(window) != 0) {
		glClearColor(0.0, 0.0, 0.4, 0.0);
	}//Color Violeta oscuro al press => V
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS
		|| glfwWindowShouldClose(window) != 0) {
		glClearColor(0.3, 0.0, 0.5, 0.0);
	}//Color Amarillo oscuro al press => Y
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS
		|| glfwWindowShouldClose(window) != 0) {
		glClearColor(1.0, 0.7, 0.0, 0.0);
	}

	glfwPollEvents();

	return continueApplication;
}

void GLFWManager::swapTheBuffers() {
	glfwSwapBuffers(window);
}

void GLFWManager::destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void GLFWManager::reshapeCallback(GLFWwindow* Window, int widthRes,
		int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}
