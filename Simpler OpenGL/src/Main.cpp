#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

#include "ErrorChecking.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include "Water.h"

float ASPECT_RATIO = 16.0f / 9.0f; // should be AspectRatio - uppercase names are usually for macros
unsigned int HEIGHT = 720;
unsigned int WIDTH = HEIGHT * ASPECT_RATIO;
bool lockmouse = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		if (!lockmouse) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//lock cursor to window
			lockmouse = true;
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//unlock cursor from window
			lockmouse = false;
		}
	}
}

int main()
{

	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Simpler OpenGL", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//lock cursor to window
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		//GL hasn't been init-ed properly
		std::cerr << "Can NOT init GLEW" << std::endl;
	}

	GLCALL(std::cout << glGetString(GL_VERSION) << std::endl);

	glClearColor(0.6f, 0.8f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	MeshGenerator::Mesh newPlane = MeshGenerator::GenerateSquarePlane(9);

	VertexArray nPlaneVA;
	VertexBuffer nPlaneVB(newPlane.verteces.data(), newPlane.verteces.size() * sizeof(float));
	VertexBufferLayout nPlaneLayout;
	nPlaneLayout.Push(GL_FLOAT, 4, GL_FALSE);
	nPlaneLayout.Push(GL_FLOAT, 4, GL_FALSE);
	nPlaneVA.AddBuffer(nPlaneVB, nPlaneLayout);
	IndexBuffer nPlaneIB(newPlane.indeces.data(), newPlane.indeces.size());

	Plane2D plane;

	VertexArray fva;
	VertexBuffer fvb(plane.Vertices, plane.VerticesCount * sizeof(float));
	VertexBufferLayout flayout;
	flayout.Push(GL_FLOAT, 4, GL_FALSE);
	flayout.Push(GL_FLOAT, 4, GL_FALSE);
	fva.AddBuffer(fvb, flayout);
	IndexBuffer fib(plane.Indeces, plane.IndecesCount);

	TShape2D TShape;

	VertexArray tva;
	VertexBuffer tvb(TShape.Vertices, TShape.VerticesCount * sizeof(float));
	VertexBufferLayout tlayout;
	tlayout.Push(GL_FLOAT, 4, GL_FALSE);
	tlayout.Push(GL_FLOAT, 4, GL_FALSE);
	tva.AddBuffer(tvb, tlayout);
	IndexBuffer tib(TShape.Indeces, TShape.IndecesCount);

	Cube cubemesh;

	VertexArray cva;
	VertexBuffer cvb(cubemesh.Vertices, cubemesh.VerticesCount * sizeof(float));
	VertexBufferLayout clayout;
	clayout.Push(GL_FLOAT, 4, GL_FALSE);
	clayout.Push(GL_FLOAT, 4, GL_FALSE);
	clayout.Push(GL_FLOAT, 2, GL_FALSE);
	cva.AddBuffer(cvb, clayout);
	IndexBuffer cib(cubemesh.Indeces, cubemesh.IndecesCount);

	Shader shader("res/shaders/Shader.glsl");
	shader.Bind();

	glm::vec3 pos(0.0f, 1.3f, -10.0f);
	glm::vec3 lookpos(0.0f, 0.0f, 0.0f);

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 1000.0f);
	glm::mat4 View = glm::lookAt(
		pos,
		lookpos,
		glm::vec3(0, 1, 0)
	);

	glm::mat4 MVP = glm::mat4(1.0f)*Projection*View;

	float mouseSpeed = 0.05, deltaTime;
	float horizontalAngle = 0, verticalAngle = 0;
	double xpos, ypos;
	glfwSetCursorPos(window, (double)WIDTH / 2, (double)HEIGHT / 2);

	glm::mat4 ModelTrans(1.0f);
	glm::mat4 ScaleFloor = glm::scale(glm::mat4(1.f), glm::vec3(100.0f, 1.0f, 100.0f));
	glm::mat4 TranslateFloor = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 10.0f, 0.0f));

	glm::mat4 ScalePlane = glm::scale(glm::mat4(1.f), glm::vec3(10.0f, 1.0f, 10.0f));
	glm::mat4 TranslatePlane = glm::translate(glm::mat4(1.f), glm::vec3(20.0f, 2.f, 20.0f));

	glm::mat4 ScaleT(1.f);
	glm::mat4 TranslateT = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 1.0f, 50.0f));

	glm::mat4 ScaleC(1.f);
	glm::mat4 TranslateC = glm::translate(glm::mat4(1.f), glm::vec3(10.0f, 1.0f, 50.0f));


	glm::vec3 vel(0);
	float speed = 10.0f;

	double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();

	spring TestSp( .0f, .025f, .04f);

	TestSp.Height = 5.0;

	//Water water(30, .0005f, .0100f, .0006f, 2, shader);
	Water water(30, .005f, .04f, .025f, 2, shader);

	glm::mat4 ScaleWater = glm::scale(glm::mat4(1.f), glm::vec3(20.0f, 1.0f, 20.0f));
	glm::mat4 TranslateWater = glm::translate(glm::mat4(1.f), glm::vec3( .0f, 2.f, .0f));

	water.ReFactor(TranslateWater, glm::mat4(1.f), ScaleWater);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		std::cout << "FPS: " << 1 / deltaTime << std::endl;

		if (lockmouse) {
			glfwGetCursorPos(window, &xpos, &ypos);
			glfwSetCursorPos(window, (double)WIDTH / 2, (double)HEIGHT / 2);
		}

		// Compute new orientation
		horizontalAngle += mouseSpeed * deltaTime * float(WIDTH / 2 - xpos);
		verticalAngle += mouseSpeed * deltaTime * float(HEIGHT / 2 - ypos);

		const float HalfPI = 3.14f / 2.f;

		if (verticalAngle < -HalfPI) verticalAngle = -HalfPI;
		else if (verticalAngle > HalfPI) verticalAngle = HalfPI;

		//std::cout << "[H]: " << horizontalAngle << "[V]: " << verticalAngle << std::endl;

		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		glm::vec3 mvmtDirection(
			sin(horizontalAngle),
			0,
			cos(horizontalAngle)
		);

		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);


		if (glfwGetKey(window, GLFW_KEY_A) == 1) {
			vel -= right * deltaTime * speed;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == 1) {
			vel += right * deltaTime * speed;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == 1) {
			vel += mvmtDirection * deltaTime * speed;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == 1) {
			vel -= mvmtDirection * deltaTime * speed;
		}

		//vel.y = 0;

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == 1) {
			vel.y += deltaTime * speed;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == 1) {
			vel.y -= deltaTime * speed;
		}

		pos += vel;

		View = glm::lookAt(
			pos,
			pos + direction,
			glm::vec3(0, 1, 0)
		);

		MVP = Projection * View * glm::mat4(1.0f);

		shader.Bind();
		shader.SetUniformMatrix4fv("MVP", 1, GL_FALSE, &MVP[0][0]);

		ModelTrans = ScaleFloor;
		GLCALL(glDisable(GL_CULL_FACE));
		shader.SetUniform4f("u_color", 0.5f, 0.5f, 0.5f, 2.0f);
		shader.SetUniformMatrix4fv("ModelTrans", 1, GL_FALSE, &ModelTrans[0][0]);

		fva.Bind();
		fib.Bind();

		glDrawElements(GL_TRIANGLES, plane.IndecesCount, GL_UNSIGNED_INT, 0);
		GLCALL(glEnable(GL_CULL_FACE));

		ModelTrans = TranslateT * ScaleT;
		GLCALL(glDisable(GL_CULL_FACE));
		shader.SetUniform4f("u_color", 0.5f, 0.5f, 0.5f, 2.0f);
		shader.SetUniformMatrix4fv("ModelTrans", 1, GL_FALSE, &ModelTrans[0][0]);

		tva.Bind();
		tib.Bind();

		glDrawElements(GL_TRIANGLES, TShape.IndecesCount, GL_UNSIGNED_INT, 0);
		GLCALL(glEnable(GL_CULL_FACE));

		GLCALL(glEnable(GL_CULL_FACE));

		//ModelTrans = TranslateC * ScaleC;
		shader.SetUniform4f("u_color", 1.f, 1.f, 1.f, 1.f);
		shader.SetUniformMatrix4fv("ModelTrans", 1, GL_FALSE, &ModelTrans[0][0]);

		cva.Bind();
		cib.Bind();

		glDrawElements(GL_TRIANGLES, cubemesh.IndecesCount, GL_UNSIGNED_INT, 0);
		GLCALL(glEnable(GL_CULL_FACE));

		ModelTrans = TranslatePlane * ScalePlane;
		GLCALL(glDisable(GL_CULL_FACE));
		shader.SetUniform4f("u_color", 1.f, 1.f, 1.f, 1.f);
		shader.SetUniformMatrix4fv("ModelTrans", 1, GL_FALSE, &ModelTrans[0][0]);

		if (glfwGetKey(window, GLFW_KEY_SPACE) == 1) {
			TestSp.Speed += .1f;
		}

		TestSp.update();

		nPlaneVA.Bind();
		nPlaneIB.Bind();

		newPlane.verteces[353] = TestSp.Height;
		
		nPlaneVB.setData(newPlane.verteces.data(), newPlane.verteces.size() * sizeof(float));

		glDrawElements(GL_TRIANGLES, newPlane.indeces.size(), GL_UNSIGNED_INT, 0);
		GLCALL(glEnable(GL_CULL_FACE));

		//water.update(TestSp.Speed);
		water.render();

		vel = glm::vec3(0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
