// All comments and characters entered by ^.^ following Victor Gordan

/* CURRENT WORKSPACE GOAL 38:38 opengl course create 3d and 2d graphics w c++
https://www.youtube.com/watch?v=45MIykWJ-C4
 */

#include<iostream>
#include<glad/glad.h>

 /* 
GLFW is an Open Source, multi - platform library for OpenGL, OpenGL ESand 
Vulkan development on the desktop.It provides a simple API for creating
windows, contextsand surfaces, receiving inputand events.
*/
#include<GLFW/glfw3.h>

//Call our functions and classes from other files utilizing OOP
#include "shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//coordinates for vertices
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
};

//Indices to order vertices
GLuint indices[] =
{
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};

// main function initializing our program
int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(846, 846, "^.^ is THREE-DIMENSIONSAL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 846, 846);

	//Generate Shader object using shader files
	Shader shaderProgram("default.vert", "default.frag");

	//Generates Vertex Array Object and binds it to pass to buffer
	VAO VAO1;
	VAO1.Bind();

	//Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	//Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	//Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	//Unbind all to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		//background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clean back buffer and assign color to it
		glClear(GL_COLOR_BUFFER_BIT);
		//tell OpenGL which Shader Program to use
		shaderProgram.Activate();
		//
		VAO1.Bind();
		//draw primitives, numer of indicies, dataype of indices, index
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//swap back buffer with front buffer
		glfwSwapBuffers(window);
		//take care of all GLFW events
		glfwPollEvents();
	}
	//delete all objects we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}