#include <GL/glew.h>
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "camera.h"
#include "shader.h"

using namespace std;

class Skybox
{
private:
	GLuint vao;
	GLuint vbo;
	Shader shader;
	GLuint textures;
	bool CompileSuccessful(int obj);
public:
	Skybox();
	GLuint loadCubemap(vector<const GLchar*> faces);
	void draw(Camera cam);
};