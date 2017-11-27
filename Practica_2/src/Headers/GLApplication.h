/*
 * GLApplication.h
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */

#ifndef GLAPPLICATION_H_
#define GLAPPLICATION_H_

#include <stdlib.h>

#include <GL/glew.h>

#include "WindowManager.h"
#include "Sphere.h"
#include "Shader.h"
#include "CameraFPS.h"
#include "CameraOrbital.h"
#include "TimeManager.h"
#include "Texture.h"

class GLApplication {
public:

	GLApplication();
	~GLApplication();

	void GLMain();
	void initialize();
	void applicationLoop();
	void destroy();

	void setWindowManager(WindowManager * windowManager) {
		this->windowManager = windowManager;
	}

	WindowManager * getWindowManager() {
		return windowManager;
	}
	
	//CameraFPS* getCamera() {
	CameraOrbital* getCamera() {
		return camera;
	}

	//void setCamera(CameraFPS* camera) {
	void setCamera(CameraOrbital* camera) {
		this->camera = camera;
	}
	glm::quat transform;
protected:
	WindowManager * windowManager;
	//CameraFPS * camera;
	CameraOrbital * camera;
	Shader shader;

};

#endif /* GLAPPLICATION_H_ */
