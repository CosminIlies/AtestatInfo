#include "Game.h"
#include<iostream>

Game::Game(int width, int height, const char* title)
{
	//Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
	//						Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
	//						Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0), glm::vec3(0.0, 0.0, 1.0))
	//};
	std::vector<Vertex> vertices = { Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
								Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
								Vertex(glm::vec3(-0.5, 0.5, 0.0), glm::vec2(0, 1.0), glm::vec3(0.0, 0.0, 1.0)),
								Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec2(1, 1.0), glm::vec3(0.0, 0.0, 1.0))
	}; 

	std::vector<unsigned int> indices = {0, 1, 2, 1, 3, 2};

	_window = new Window(width, height, title);
	_material = new Material("./res/Shaders/default", "./res/Textures/dragon.png", 32, 2);
	//_mesh = new Mesh("./res/Models/car.fbx");
	_model = new Model("./res/Models/dragon.fbx");
	_mesh = new Mesh(vertices, indices);
	_transform = new Transform();
	_camera = new Camera();
	_dirLight = new DirectionalLight(glm::vec3(0.0, 0.0, -1.0), glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0);
	_transform->rotation.x = -3.15/2;
	//_transform->rotation.z = -3.15 / 2;
	_transform->position.y = -5;

}

Game::~Game()
{
	delete _window;
	delete _material;
	delete _mesh;
	delete _transform;
	delete _camera;
	delete _dirLight;
	delete _model;
	Debug::Log("Game was destroy!");
}

void Game::Start()
{
	_isRunning = true;
	run();
}

void Game::Stop()
{
	_isRunning = false;
}

void Game::run() {



	while (_isRunning) {
		_window->ClearScreen();
		if (Input::getInstance().GetKey(GLFW_KEY_ESCAPE) || _window->ShouldCloseTheWindow()) {
			Stop();
		}	

		//update
		glm::vec2 _walkdir = glm::vec2(0.0, 0.0);

		if (Input::getInstance().GetKey(GLFW_KEY_W)) {
			_walkdir.y -= 1;
		}

		if (Input::getInstance().GetKey(GLFW_KEY_S)) {
			_walkdir.y += 1;
		}

		if (Input::getInstance().GetKey(GLFW_KEY_A)) {
			_walkdir.x -= 1;
		}

		if (Input::getInstance().GetKey(GLFW_KEY_D)) {
			_walkdir.x += 1;
		}
		
		_walkdir = glm::normalize(_walkdir);


		int _currentX = Input::getInstance().GetMousePosition().x;
		int _currentY = Input::getInstance().GetMousePosition().y;

		_camera->rotation.x -= (lastY - _currentY) * 0.001;
		_camera->rotation.y -= (lastX - _currentX) * 0.001;

		float angle = _camera->rotation.y;



		if ( glm::length(_walkdir) > 0.1f) {
			_camera->position.x += -_walkdir.y * glm::sin(angle) * 0.1f + _walkdir.x * glm::cos(angle) * 0.1f;

			_camera->position.z += _walkdir.y * glm::cos(angle) * 0.1f + _walkdir.x * glm::sin(angle) * 0.1f;
		}

		lastX = _currentX;
		lastY = _currentY;


		_transform->rotation.z -= 0.01;
		//renderer
		_material->Bind(*_transform, *_camera, *_dirLight, *_window);


		_model->Draw();




		_window->UpdateWindow();
	}
}
