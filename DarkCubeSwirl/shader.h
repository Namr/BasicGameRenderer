#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h> 

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Shader
{
public:
	GLuint Program;
	Shader(char* vertexPath, char* fragmentPath);
	void use();
private:
	GLuint load_shader(char *filepath, GLenum type);
};

#endif