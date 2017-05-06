#ifndef CUBE_H
#define CUBE_H
#include <GL/glew.h>
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "Camera.h"
#include "shader.h"
using namespace std;

class Cube
{
private:
	GLuint vao;
	GLuint vbo;
	Shader shader;
public:
	Cube();
	void draw(Camera &camera, float x, float y, float z, float r);
};
#endif