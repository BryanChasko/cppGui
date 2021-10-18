// All comments and characters entered by ^.^ following Victor Gordan

/* CURRENT WORKSPACE GOAL 20:05 opengl course create 3d and 2d graphics w c++

Current task - Adding Vertiex and Fragment Shaders
 Vertex Shader is a colleciton of points that allows for shape assembly
 into a primitive. Following rasterization into pixels, the fragment shader 
 allows coloring to the pixels.
 */

#include<iostream>
#include<glad/glad.h>
/* 
GLFW is an Open Source, multi - platform library for OpenGL, OpenGL ESand 
Vulkan development on the desktop.It provides a simple API for creating
windows, contextsand surfaces, receiving inputand events.
*/
#include<GLFW/glfw3.h>

//Victor Gordan fragment shader code for constructing
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4*(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f;\n"
"}\n\0";

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

	//Array of type GLfloat to create fragment shader triangle on
	GLfloat vertices[] =
	{
		//every 3 floats represents one coordinate
		//left corner
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		//right corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		//top corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

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

	//reference to store our vertex shader in using GL unsigned integer
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//reference value, using 1 string for shader, source code,
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compile above shader info into machine language and apply to buffer
	glCompileShader(vertexShader);

	//reference to store our fragment shader in using GL unsigned integer
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//reference value, using 1 string for shader, source code,
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compile above shader info into machine language and apply to buffer
	glCompileShader(fragmentShader);

	//wraping the shaders into a shader program 
	//create reference to create the program
	GLuint shaderProgram = glCreateProgram();

	//attach the shaders to the program just created
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//place the shader program in a wrapper to pass the refences.
	glLinkProgram(shaderProgram);
	//delete the shaders once we have passed them into our program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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