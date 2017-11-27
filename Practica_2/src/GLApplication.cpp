/*
* GLApplication.cpp
*
*  Created on: 07/08/2016
*      Author: rey
*/

#include "Headers/GLApplication.h"

Sphere sphere1(1.5, 20, 5, MODEL_MODE::VERTEX_LIGHT_COLOR);
Sphere sphere2(1.5, 20, 5, MODEL_MODE::VERTEX_LIGHT_TEXTURE);

Texture texture1(GL_TEXTURE_2D, "Textures/mercury.png");
Shader shader, shader2, shader3;

GLuint VBO, VAO, EBO;
struct VertexTexture {//cubo-luna
	glm::vec3 m_Pos;
	glm::vec2 m_TexCoord;
};
struct VertexColorTexture {//cubo-mlticolor
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
};

GLApplication::GLApplication() :
windowManager(nullptr), camera(nullptr) {
}

GLApplication::~GLApplication() {
	destroy();
}

void GLApplication::GLMain() {
	initialize();
	applicationLoop();
}

void GLApplication::initialize() {
	if (!windowManager
		|| !windowManager->initialize(800, 700, "Practica_2", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);// COLOR DE ESCENARIO
	glEnable(GL_DEPTH_TEST);
	shader.initialize("Shaders/ShaderColor.vs", "Shaders/ShaderColor.fs");
	sphere1.init();//esfera 1- esfera color verde
	sphere1.load();

	sphere2.init();//esfera 2- esfera texturizada con la luna
    sphere2.load();
	texture1.load();
	
	shader2.initialize("Shaders/basic.vs", "Shaders/basic.fs");
	shader3.initialize("Shaders/lightingSpecularMap.vs", "Shaders/lightingSpecularMap.fs");
	// Set up vertex data (and buffer(s)) and attribute pointers
	VertexTexture vertices[8] = {
		{ glm::vec3(0.25f, 0.25f, 0.25f),  glm::vec2{ 1.0f, 1.0f } }, // 0
		{ glm::vec3(0.25f, -0.25f, 0.25f), glm::vec2{ 1.0f, 0.0f } }, // 1
		{ glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec2{ 0.0f, 0.0f } }, // 2
		{ glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec2{ 0.0f, 1.0f } }, // 3

		{ glm::vec3(0.25f, 0.25f, -0.25f), glm::vec2{ 1.0f, 1.0f } }, // 4
		{ glm::vec3(0.25f, -0.25f, -0.25f), glm::vec2{ 1.0f, 0.0f } }, // 5
		{ glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec2{ 0.0f, 0.0f } }, // 6
		{ glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec2{ 0.0f, 1.0f } }, // 7
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, 1, 2, 3,  //Cara Frontal
		3, 2, 7, 2, 6, 7, //Cara Derecha
		4, 5, 7, 5, 6, 7, // Cara Trasera
		4, 5, 0, 5, 1, 0, //Cara Izquierda
		4, 0, 7, 0, 3, 7, // Cara Superior
		5, 1, 6, 1, 2, 6 //Cara Inferior
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*) sizeof(vertices[0].m_Pos));
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set up vertex data (and buffer(s)) and attribute pointers
	VertexColorTexture vertices2[8] = {
		{ glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f)}, // 0
		{ glm::vec3(0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 1.0f, 0.0f)}, // 1
		{ glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 0.0f, 1.0f)}, // 2
		{ glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 1.0f, 0.0f)}, // 3

		{ glm::vec3(0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f)}, // 4
		{ glm::vec3(0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 1.0f, 0.0f)}, // 5
		{ glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 0.0f, 1.0f)}, // 6
		{ glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 1.0f, 0.0f)}, // 7
	};
	GLuint indices2[] = {  // Note that we start from 0!
		0, 1, 3, 1, 2, 3,  //Cara Frontal
		3, 2, 7, 2, 6, 7, //Cara Derecha
		4, 5, 7, 5, 6, 7, // Cara Trasera
		4, 5, 0, 5, 1, 0, //Cara Izquierda
		4, 0, 7, 0, 3, 7, // Cara Superior
		5, 1, 6, 1, 2, 6 //Cara Inferior
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices2[0]), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices2[0]), (GLvoid*) sizeof(vertices2[0].m_Pos));
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	
}

void GLApplication::applicationLoop() {
	bool processInput = true;
	double lastTime = TimeManager::Instance().GetTime();
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		shader.turnOn();
		// Transformation matrices
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection;
		/*PERSPECTIVA*/
		projection = glm::perspective(5.0f,//FOV
			(GLfloat)WindowManager::screenWidth
			/ (GLfloat)WindowManager::screenHeight, 0.1f, 100.0f);
	    /*ORTHO*/
		//projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);// izq, der, inf, sup, p.sercano, p.legano
		// Get the uniform locations
		GLint modelLoc = shader.getUniformLocation("model");
		GLint viewLoc = shader.getUniformLocation("view");
		GLint projLoc = shader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// Draw the loaded model 1
		glm::mat4 model1;
		model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, -6.0f));
		model1 = glm::scale(model1, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		sphere1.render();//Renderizado esfera 1

		glm::mat4 model4; //Cubo 2- muticolor
		model4 = glm::translate(model4, glm::vec3(-6.0f, 0.0f, -6.0f));
		model4 = glm::scale(model4, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model4));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		shader.turnOff();

		shader3.turnOn();
		// Get the uniform locations
		 modelLoc = shader3.getUniformLocation("model");
		 viewLoc = shader3.getUniformLocation("view");
		 projLoc = shader3.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// Draw the loaded model 2
		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(3.0f, 0.0f, -6.0f));
		model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		texture1.bind(GL_TEXTURE0);
		sphere2.render();//Renderizado esfera 2
		
		glm::mat4 model3;//Cubo 1- Texturizado
		model3 = glm::translate(model3, glm::vec3(-3.0f, 0.0f, -6.0f));
		model3 = glm::scale(model3, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		shader3.turnOff();
		
		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}

	shader.destroy();
	shader2.destroy();
	shader3.destroy();

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
}
