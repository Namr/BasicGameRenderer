#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "cube.h"
#include "skybox.h"
#include "Model.h"
#include "Camera.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dark Malloc The Wise", nullptr, nullptr); // Windowed
	//GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	
	//one time shop code here
	glEnable(GL_DEPTH_TEST);
	Skybox sky;

	Model nanosuit("nanosuit2.3ds");
	Model dog("3ds file.3DS");
	Shader nanosuitShader("meshVert.glsl","meshFrag.glsl");
	Shader dogShader("meshVert.glsl", "meshFrag.glsl");
	Cube cube;
	Cube cube2;
	Cube cube3;
	Cube cube4;
	Cube cube5;
	Cube cube6;
	Cube cube7;
	Cube cube8;
	Camera cam;
	cam = Camera();
	cam.view = glm::lookAt(
		glm::vec3(1.0f, 3.2f, 5.2f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // camera center
		glm::vec3(0.0f, 0.0f, -1.0f) // up axis
	);

	float t = 0;
	float v = 0;
	float d = 0.1;
	float lastTime = 1;

	// Get mouse position
	double xpos, ypos;
	glm::vec3 position = glm::vec3(0, 0, 5);
	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.03f;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float deltaTime = 0.03;
	//main loop here
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);


		double currentTime = glfwGetTime();

		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

		horizontalAngle -= -mouseSpeed * deltaTime * float(WIDTH / 2 - xpos);
		verticalAngle += mouseSpeed * deltaTime * float(HEIGHT / 2 - ypos);

		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);
		glm::vec3 up = glm::cross(right, direction);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += right * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}

		cam.view = glm::lookAt(
			position, // position
			position + direction, // camera center
			up // up axis
		);

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		t++;
		v += d;
		if (v > 10 || v < -10)
			d *= -1;

		sky.draw(cam);
		cube.draw(cam, 2.0f, 0.0f, 0.0f, t);
		cube2.draw(cam, 0.0f, 2.0f, 0.0f, t);
		cube3.draw(cam, 0.0, -2.0f, 0.0f, t);
		cube4.draw(cam, -2.0f, 0.0f, 0.0f, t);
		cube5.draw(cam, 1.5f, 1.5f, 0.0f, t);
		cube6.draw(cam, -1.5f, 1.5f, 0.0f, t);
		cube7.draw(cam, 1.5f, -1.5, 0.0f, t);
		cube8.draw(cam, -1.5f, -1.5f, 0.0f, t);

		nanosuitShader.use();

		glUniformMatrix4fv(glGetUniformLocation(nanosuitShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(cam.proj));
		glUniformMatrix4fv(glGetUniformLocation(nanosuitShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(cam.view));

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
		glUniformMatrix4fv(glGetUniformLocation(nanosuitShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		nanosuit.draw(nanosuitShader);

		dogShader.use();
		glm::mat4 Dogmodel;
		Dogmodel = glm::translate(Dogmodel, glm::vec3(0.0f, 0.0f, 0.0f));
		Dogmodel = glm::scale(Dogmodel, glm::vec3(0.5f, 1.0f, 0.5f));
		Dogmodel = glm::rotate(Dogmodel, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(dogShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(cam.proj));
		glUniformMatrix4fv(glGetUniformLocation(dogShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(cam.view));
		glUniformMatrix4fv(glGetUniformLocation(dogShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(Dogmodel));
		dog.draw(dogShader);

		lastTime = currentTime;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}