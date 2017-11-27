/*
 * CameraFPS.h
 *
 *  Created on: 06/09/2016
 *      Author: rey
 */
#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class CameraOrbital {
	// Default camera values
	const float SPEED = 3.0f;
	const float SENSITIVTY = 0.25f;
	const float ZOOM = 45.0f;
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::vec3 Target;
	// Eular Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors 
	CameraOrbital(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		      glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
			  float yaw = 45.0, float pitch = 45.0) :
	 MovementSpeed(SPEED), MouseSensitivity(
					SENSITIVTY), Zoom(ZOOM) {
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->Target = glm::vec3(0.0f, 0.0f, -6.0f);
		this->updateCameraVectors();

		glm::vec3 cameraDirection = Position - Target;
		glm::vec3 cameraRight = glm::cross(WorldUp, cameraDirection);
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
		double Origen = glm::dot(-(Position), cameraDirection);
	}

	glm::mat4 GetViewMatrix() {
		//return glm::lookAt(this->Position, this->Position + this->Front, this->WorldUp);
		
		///////////////////Matriz lookAt sin ocupar la funcion glm::lookAt 
		// Calcular Direccion de Camara
		glm::vec3 zaxis = glm::normalize(Position - Target);
		// Obtener RightAxis
		glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(WorldUp), zaxis));
		// Calcular UpAxis
		glm::vec3 yaxis = glm::cross(zaxis, xaxis);

		//Crear matriz de traslación y rotación
		glm::mat4 translation; 
		translation[3][0] = -Position.x; 
		translation[3][1] = -Position.y;
		translation[3][2] = -Position.z;
		glm::mat4 rotation;
		rotation[0][0] = xaxis.x; 
		rotation[1][0] = xaxis.y;
		rotation[2][0] = xaxis.z;
		rotation[0][1] = yaxis.x; 
		rotation[1][1] = yaxis.y;
		rotation[2][1] = yaxis.z;
		rotation[0][2] = zaxis.x; 
		rotation[1][2] = zaxis.y;
		rotation[2][2] = zaxis.z;

		// Devuelve matriz lookAt como combinación de traslación y rotación
		return rotation * translation; 
	}

	void ProcessMouseMovement(float xoffset, float yoffset,
			float dt) {
		float speed = MouseSensitivity;
		Yaw += speed * xoffset;
		Pitch += speed * yoffset;

		if (Pitch < -90){
			Pitch = -89.99;
		}
		if (Pitch>90){
			Pitch = 89.999;
		}
		this->updateCameraVectors();
	}

private:
	void updateCameraVectors() {
		Position.x = Target.x + 10 * cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		Position.y = Target.y + 10 * sin(glm::radians(this->Pitch));
		Position.z = Target.z + 10 * sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(Target - Position);
	}
};
