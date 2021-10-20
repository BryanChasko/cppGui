// All comments and characters entered by ^.^ following Victor Gordan

/* CURRENT WORKSPACE GOAL 29:22 opengl course create 3d and 2d graphics w c++
https://www.youtube.com/watch?v=45MIykWJ-C4
INDEX BUFFERS - We can draw a triangle primitive between 3 vertices. 
vertices 0, 1, and 2. But what if we want to have 3 triangles/3 vertices?
Double the vertices without duplicates. We will accomplish this with 
an index buffer that tells OpenGL what order to go over vertices.
indices = [0, 4, 3,
		   4, 1, 5,
		   3, 5, 2]
First - add the new vertices to our array GLfloat vertices[] =
Second - create a GLuint indices array
Third- create and index buffer
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

// main function initializing our program
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
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		//Inner left
		-0.05f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		//Inner Right
		0.05f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 
		//Inner Down
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
	};

	// create our index array
	GLuint indices[] =
	{
		//Lower left triangle
		0, 3, 5,
		//Lower right triangle
		3, 2, 4,
		//Upper triangle
		5, 4, 1
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

	//create a reference buffer object VBO to score our vertex data
	//create Vertex Array Object to pass multiple VBOs as pointers
	//create referencec for our indeces values
	GLuint VAO, VBO, EBO;

	/* create Vertex Array Object prep for 1 vbo we've created and 
	 point to our VAO reference */
	glGenVertexArrays(1, &VAO);

	//create buffer object VBO giving 1 3d object and point to reference
	glGenBuffers(1, &VBO);

	//create an object to hold values for our indexes buffer
	glGenBuffers(1, &EBO);

	// binding VAO so we can work with it in current buffer
	glBindVertexArray(VAO);

	// binding object to impact current object in array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* 
	Store our verticies in the VBO, type of buffer, size of buffer in bytes,
	actual data, and use of the data (stream, static or dynamic) and draw
	read or copy
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//make our EBO current by binding it and specifying type array_buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	/* 
	Make VAO readable by OpenGL with funciton glVertexAttributePointer
	pass the index of the vertex attribute we want to use,
	communicating with the vertex shader from the outside.
	Position of vertex attribute, how many values per vertex- in our 
	current case we have 3 floats, what kind of values we have- floats,
	coordinates as integers- we don't, sprite of verticies - amount of
	data between each vertices- the size of our 3 floats, offset - 
	pointer to where our vertices begins in the array- the start in
	our case so we'll do a void pointer
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* 
	buffer basics note- the next frame written in the background is the 
	back buffer while front buffer frame is what is displayed at the moment
	
	prepare a new buffer by clearing the buffer in rgb format with last
	number, aka alpha number, setting transparency
	*/
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//execute the command we've prepared on the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	swap our buffers to display the color on the front buffer
	updates the image each frame
	*/
	glfwSwapBuffers(window);

	//keep the window open unless user or another function closes it
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		/*
		draw the type of primitive we want to use, starting vertices index
		and amount of vertices we want to draw - 9 for a triangle
		data type we want to draw, and index of our indices
		*/
//		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		//take care of all GLFW events
		glfwPollEvents();
	}

	// delete the vertex buffer objects we created earlier
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// delete the window when we're done with it
	glfwDestroyWindow(window);

	// terminate the api conneciton to glfw before the function ends
	glfwTerminate();

	// test to ensure project configuration is working successfully
	return 0;
}