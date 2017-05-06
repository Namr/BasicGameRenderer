#include "shader.h"

Shader::Shader(char* vertexPath, char* fragmentPath)
{
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = load_shader(vertexPath, GL_VERTEX_SHADER);
	fragment = load_shader(fragmentPath, GL_FRAGMENT_SHADER);

	glCompileShader(vertex);
	glCompileShader(fragment);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR VERTEX SHADER COMPILE FAILED\n" << infoLog << std::endl;
	};

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR FRAGMENT SHADER COMPILE FAILED\n" << infoLog << std::endl;
	};

	Program = glCreateProgram();
	glAttachShader(Program, vertex);
	glAttachShader(Program, fragment);
	glLinkProgram(Program);
	
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		std::cout << "ERROR CANT LINK SHADERS TO PROGRAM" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() 
{ 
	glUseProgram(Program); 
}

GLuint Shader::load_shader(char *filepath, GLenum type)
{
	FILE *file = fopen(filepath, "rb");
	if (!file) {
		return 0;
	}

	long len;
	if (fseek(file, 0, SEEK_END) != 0 ||
		(len = ftell(file)) == -1L) {
		fclose(file);
		return 0;
	}
	rewind(file);

	char *buffer = (char *)malloc(len);
	if (fread(buffer, 1, len, file) != len) {
		fclose(file);
		free(buffer);
		return 0;
	}
	fclose(file);

	GLuint shader = glCreateShader(type);
	if (shader == 0) {
		free(buffer);
		return 0;
	}

	glShaderSource(shader, 1, (const char * const *)&buffer, (GLint *)&len);
	free(buffer);
	return shader;
}