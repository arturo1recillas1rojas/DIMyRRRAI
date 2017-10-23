#include <iostream>

#include "Headers/InputManager.h"
#include "Headers/TimeManager.h"

InputCodes InputManager::toApplicationKey(int key) {
	switch (key) {
	case 256:
		return InputCodes::kEscape;
	case 87:
		return InputCodes::W;
	case 83:
		return InputCodes::S;
	case 65:
		return InputCodes::A;
	case 68:
		return InputCodes::D;
	case 265:
		return InputCodes::Up;
	case 264:
		return InputCodes::Down;
	case 263:
		return InputCodes::Left;
	case 262:
		return InputCodes::Right;
	}
}

State InputManager::toApplicationState(int state) {
	switch (state) {
	case 0:
		return State::RELESED;
	case 1:
		return State::PRESSED;
	}
}

MouseButtonIndex InputManager::toMouseButtonIndex(int button) {
	switch (button) {
	case 0:
		return MouseButtonIndex::LEFT;
	case 1:
		return MouseButtonIndex::RIGHT;
	case 2:
		return MouseButtonIndex::MIDDLE;
	}
}

void InputManager::keyPressed(InputCodes code, float deltaTime, State state) {
	keyState[code] = state;
}

void InputManager::mouseMoved(float mouseX, float mouseY) {//ej 7
	if (mouseButtomState[MouseButtonIndex::LEFT]) {

		float xoffset = lastMousePos.x - mouseX;
		float yoffset = lastMousePos.y - mouseY;
		lastMousePos = glm::vec2(mouseX, mouseY);

		float sensitivity = 0.1;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
	
		glm::quat qx = glm::angleAxis<float>(yoffset, glm::vec3(1, 0, 0));//glm::vec3(angulo de giro, eje de giro)
		glm::quat qy = glm::angleAxis<float>(xoffset, glm::vec3(0, 1, 0));
		//transform = qx * qy;

		//premultiplicando
		//transform = transform * qx * qy;

		//posmultiplicarlo
		transform = qx * qy * transform;
		
	}
}

void InputManager::mouseClicked(MouseButtonIndex code, float mouseX,
		float mouseY, State state) {
	switch (code) {
	case RIGHT:
		std::cout << "lastMousePos.x:" << lastMousePos.x << std::endl;
		break;
	case LEFT:
		std::cout << "lastMousePos.y:" << lastMousePos.y << std::endl;
		lastMousePos.x = mouseX;
		lastMousePos.y = mouseY;
		mouseButtomState[code] = state;
		break;
	case MIDDLE:
		std::cout << "lastMousePos.x:" << lastMousePos.x << std::endl;
		std::cout << "lastMousePos.y:" << lastMousePos.y << std::endl;
		break;
	}
}

void InputManager::mouseScroll(float yoffset) {
}

void InputManager::do_movement(float deltaTime) {
	
}
