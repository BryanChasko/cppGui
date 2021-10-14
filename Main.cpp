// All comments and characters entered by ^.^ following Victor Gordan
#include<iostream>
#include<glad/glad.h>
/* 
GLFW is an Open Source, multi - platform library for OpenGL, OpenGL ESand 
Vulkan development on the desktop.It provides a simple API for creating
windows, contextsand surfaces, receiving inputand events.
*/
#include<GLFW/glfw3.h>

int main()
{
	// ## WINDOW LOGIC ##

	// initialize GLFW so we can use its functions from glfw3.h
	glfwInit();

	/* 
	telling glfw what version of OpenGL we are using, in this case
	c++ OpenGL specification v3.3 core loaded in in Glad
	*/

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Load the package of OpenGl core functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* 
	Create a GLFW window to display our GL assets. Takes 5 inputs:
	width, height, name, full screen/max size, min window size 
	*/

	GLFWwindow* window = glfwCreateWindow(846, 846, "^.^ is THREE-DIMENSIONSAL", NULL, NULL);
	//error checking to pass console message in case of window issue
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//use the window we have created in our configs to open the window
	glfwMakeContextCurrent(window);

	//make our window black
	gladLoadGL();

	//Viewport is the area of the window open to rendering
	glViewport(0, 0, 846, 846);

	/* 
	buffer basics note- the next frame written in the background is the 
	back buffer while front buffer frame is what is displayed at the moment
	
	prepare a new buffer by clearing the buffer in rgb format with last
	number, aka alpha number, setting transparency
	*/

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//execute the command we've prepared on the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//swap our buffers to display the color on the front buffer
	glfwSwapBuffers(window);

	//keep the window open unless user or another function closes it
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	// delete the window when we're done with it
	glfwDestroyWindow(window);

	// terminate the api conneciton to glfw before the function ends
	glfwTerminate();

	// test to ensure project configuration is working successfully
	return 0;
}