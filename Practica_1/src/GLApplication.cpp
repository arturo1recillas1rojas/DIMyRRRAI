/*
* GLApplication.cpp
*
*  Created on: 07/08/2016
*      Author: rey
*/

#include "Headers/GLApplication.h"

GLuint VBO, VAO, VBO2, VAO2, EBO;
Shader shader, shader2;

Texture * texture1;

struct VertexColorTexture {
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
	glm::vec2 m_TexCoord;
};

GLApplication::GLApplication() :
windowManager(nullptr) {
}

GLApplication::~GLApplication() {
	destroy();
}

void GLApplication::GLMain() {
	initialize();
	applicationLoop();
}

/* 1  -  Crear un programa que dibuje dos triangulos consecutivos, esto se logra agregando mas vertices a
         nuestro bffer(VBO), sin utilizar idices.
   5  -  Desde el shader ajustar el triangulo para que se dibuje invertido.
   6  -  Pasar al shader una variable uniform para que exista un oset en el eje x.*/
/*
void GLApplication::initialize() {
if (!windowManager
|| !windowManager->initialize(800, 700, "Practica 1", false)) {
this->destroy();
exit(-1);
}
glEnable(GL_DEPTH_TEST);

glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

shader.initialize("Shaders/basic.vs", "Shaders/basic.fs");
// Set up vertex data (and buffer(s)) and attribute pointers
GLfloat Vertices[] = {
//Triangulo superior
// Positions          // Colors - rojo
-0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Left
0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Right
0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // Top
//Triangulo inferior
// Positions          // Colors - azul
-0.8f, -0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Left
0.8f, -0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Right
0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f   // Top
};

glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
// Position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);
// Color attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
glEnableVertexAttribArray(1);
glBindVertexArray(0); // Unbind VAO
}

void GLApplication::applicationLoop() {
bool processInput = true;
while (processInput) {
processInput = windowManager->processInput(true);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

shader.turnOn();
glBindVertexArray(VAO);
//ej 6
GLint id = shader.getUniformLocation("offset");
glUniform1f(id, 0.5); //aumento en x
shader.getUniformLocation("offset");
//
glDrawArrays(GL_TRIANGLES, 0, 6);// This is for primitive GL_TRIANGLE
glBindVertexArray(0);
shader.turnOff();

windowManager->swapTheBuffers();
}
}

void GLApplication::destroy() {
if (windowManager) {
delete windowManager;
windowManager = nullptr;
}

shader.destroy();

glDisableVertexAttribArray(0);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &VBO);
glBindVertexArray(0);
glDeleteVertexArrays(1, &VAO);
}
*/

/* 2  -  Crear un programa que dibuje dos triangulos usando dos diferentes VBOs y VAOs para los datos.
   3  -  Crear un programa que dibuje dos triangulos con dos shaders diferentes, un shader que dibuje un
         triangulo de color rojo y otro de color verde.*/
/*
void GLApplication::initialize() {
if (!windowManager
|| !windowManager->initialize(800, 700, "Practica 1", false)) {
this->destroy();
exit(-1);
}
glEnable(GL_DEPTH_TEST);

glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

shader.initialize("Shaders/basic.vs", "Shaders/basic.fs");
// Set up vertex data (and buffer(s)) and attribute pointers
GLfloat Vertices[] = {
//Triangulo superior
// Positions          // Colors - Verde
-0.8f, -0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Left
0.8f, -0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Right
0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f   // Top
};
shader2.initialize("Shaders/basic.vs", "Shaders/basic.fs");
GLfloat Vertices2[] = {
//Triangulo inferior
// Positions          // Colors - rojo
-0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Left
0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom Right
0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // Top
};
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
// Position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);
// Color attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
glEnableVertexAttribArray(1);
glBindVertexArray(0); // Unbind VAO

glGenVertexArrays(1, &VAO2);
glGenBuffers(1, &VBO2);
glBindVertexArray(VAO2);
glBindBuffer(GL_ARRAY_BUFFER, VBO2);
glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
// Position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);
// Color attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
glEnableVertexAttribArray(1);
glBindVertexArray(0); // Unbind VAO
}

void GLApplication::applicationLoop() {
bool processInput = true;
while (processInput) {
processInput = windowManager->processInput(true);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

shader.turnOn();
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 6);// This is for primitive GL_TRIANGLE
glBindVertexArray(0);
shader.turnOff();

shader2.turnOn();
glBindVertexArray(VAO2);
glDrawArrays(GL_TRIANGLES, 0, 6);// This is for primitive GL_TRIANGLE
glBindVertexArray(0);
shader2.turnOff();

windowManager->swapTheBuffers();
}
}

void GLApplication::destroy() {
if (windowManager) {
delete windowManager;
windowManager = nullptr;
}

shader.destroy();

glDisableVertexAttribArray(0);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &VBO);
glBindVertexArray(0);
glDeleteVertexArrays(1, &VAO);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &VBO2);
glBindVertexArray(0);
glDeleteVertexArrays(1, &VAO2);
}
*/

/* 4  -  Crear un programa que dibuje un cubo, el color del cubo debe pasarse al shader como atributo de
         vertice, como se mostro en la clase, se debe de ver como se hace interpolacion de los colores.
   7  -  Utilizando el ejercicio 4 hacer que el cubo rote, para ello se necesita manejar los eventos del teclado,
         posicion y click. Los movimientos debe de realizarse en los dos ejes.*/
/*
void GLApplication::initialize() {
	if (!windowManager
		|| !windowManager->initialize(800, 700, "Practica 1", false)) {
		this->destroy();
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	shader.initialize("Shaders/basic.vs", "Shaders/basic.fs");

	// Set up vertex data (and buffer(s)) and attribute pointers
	VertexColorTexture vertices[8] = {
		{ glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 0
		{ glm::vec3(0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 0.0f } }, // 1
		{ glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 2
		{ glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 1.0f } }, // 3

		{ glm::vec3(0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 4
		{ glm::vec3(0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 0.0f } }, // 5
		{ glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 6
		{ glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 1.0f } }, // 7
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*) sizeof(vertices[0].m_Pos));
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
		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;
		// Create transformations
		glm::mat4 transform = glm::toMat4(windowManager->inputManager.transform);

		//transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
		//transform = glm::rotate(transform, (GLfloat)timeValue * 3.0f, glm::vec3(1.0f, 0.0f, 0.0f));//rot(X,Y,Z)
		// Get matrix's uniform location and set matrix
		GLint transformLoc = shader.getUniformLocation("transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		shader.turnOff();

		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}

	shader.destroy();

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
}
*/

/* 8  -  Actualice el ejercicio 7 para que el cubo tenga mapeada una textura.*/

void GLApplication::initialize() {
	if (!windowManager
		|| !windowManager->initialize(800, 700, "Practica 1", false)) {
		this->destroy();
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	shader.initialize("Shaders/basic.vs", "Shaders/basic.fs");
	shader2.initialize("Shaders/texture.vs", "Shaders/texture.fs");

	// Set up vertex data (and buffer(s)) and attribute pointers
	VertexColorTexture vertices[24] = {
		//Frontal
		{ glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 0
		{ glm::vec3(0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 0.0f } }, // 1
		{ glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 2
		{ glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 1.0f } }, // 3
		//Trasera
		{ glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 4
		{ glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 1.0f, 0.0f } }, // 5
		{ glm::vec3(0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 0.0f } }, // 6
		{ glm::vec3(0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 0.0f, 1.0f } }, // 7
		//Izquierda
		{ glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 8
		{ glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 1.0f, 0.0f } }, // 9
		{ glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 10
		{ glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 1.0f } }, // 11
		//Derecha
		{ glm::vec3(0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 12
		{ glm::vec3(0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 0.0f } }, // 13
		{ glm::vec3(0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 0.0f } }, // 14
		{ glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 0.0f, 1.0f } }, // 15
		//Superior
		{ glm::vec3(0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 16
		{ glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2{ 1.0f, 0.0f } }, // 17
		{ glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 0.0f } }, // 18
		{ glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2{ 0.0f, 1.0f } }, // 19
		//Inferior
		{ glm::vec3(0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 1.0f } }, // 20
		{ glm::vec3(0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2{ 1.0f, 0.0f } }, // 21
		{ glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 22
		{ glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2{ 0.0f, 1.0f } }, // 23

	};
	GLuint indices[] = {  // Note that we start from 0!
		0,1,3,1,2,3,  //Cara Frontal
		12,13,15,13,14,15, //Cara Derecha
		4,5,7,5,6,7, // Cara Trasera
		8,9,11,9,10,11, //Cara Izquierda
		16,17,19,17,18,19, // Cara Superior
		20,21,23,21,22,23 //Cara Inferior
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*) sizeof(vertices[0].m_Pos));
	glEnableVertexAttribArray(1);
	//Texture Mapping attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)(sizeof(vertices[0].m_Color) + sizeof(vertices[0].m_Pos)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	texture1 = new Texture(GL_TEXTURE_2D, "Textures/awesomeface.png");
	texture1->load();
}

void GLApplication::applicationLoop() {
	bool processInput = true;
	double lastTime = TimeManager::Instance().GetTime();
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		shader.turnOn();
		shader2.turnOn();
		texture1->bind(GL_TEXTURE0);
		glUniform1i(shader2.getUniformLocation("ourTexture1"), 0);

		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;
		// Create transformations
		glm::mat4 transform = glm::toMat4(windowManager->inputManager.transform);

		// Get matrix's uniform location and set matrix
		GLint transformLoc = shader.getUniformLocation("transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		shader2.turnOff();
		shader.turnOff();

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

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

	delete (texture1);
}
