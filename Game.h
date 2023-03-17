#pragma once
#include "Debug.h"
#include "Shader.h"
#include "Input.h"
#include "Window.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "Model.h"

class Game
{
public:
	Game(int width, int height, const char* title);
	~Game();

	void Start();
	void Stop();


private:
	bool _isRunning = false;
	Window* _window;
	Material* _material;
	Mesh* _mesh;
	Model* _model;
	Transform* _transform;
	Camera* _camera;
	DirectionalLight* _dirLight;
	int lastX = 0, lastY = 0;

	void run();
};

