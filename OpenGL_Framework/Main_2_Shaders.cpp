/************
* The window is first setup using the glfw library.
* This platform-independent library maps the OS window interface
* onto the glfw specification
*
* The glew library allows us to use the OpenGL library
* However the OpenGL lib file is already on the computer
* provided by the manufacturer of the graphics card
*
* All OpenGL objects have a unique ID (of type GLuint)
* The ID and OpenGL object are generated by a function
* however the actual OpenGL object is gernerally hidden
* from the user, and accessed only through its ID
*
************/


#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	//glViewport(GLint left_edge, GLint top_edge, GLint width, GLint height);
	glViewport(0, 0, width, height);

	Shader shaderProgram("../OpenGL_Framework/VertexShader.glsl", "../OpenGL_Framework/FragmentShader.glsl");
		
	// wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Lint nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions         // Colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2
	};

	/* The vertex buffer object (VBO) allows us to manage memory in th GPU
	* This will allow us to send all the vertices at once to the GPU
	*
	* OpenGL has many types of buffer objects
	* the buffer type of a vertex buffer object is GL_ARRAY_BUFFER.
	*
	* The VAO (Vertex array object) is used to store the state of the
	* VBO and how the memory should be interpreted
	* Whenever we want to draw an object, we bind the corresponding VAO
	*/

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	// generate the buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	{
		// set the VBO as the current buffer in OpenGL's state machine
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// set the size of the buffer and copy the vertices
		// GL_STATIC_DRAW means we wont be changing this often, so it is put into slow memory
		// GL_DYNAMIC_DRAW = likely to change, GL_STREAM_DRAW = will change every frame
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// attach a GL_ELEMENT_ARRAY_BUFFER to EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Tell OpenGL how it should interpret the data in the GL_ARRAY_BUFFER
		//glVertexAttribPointer(???, size of attribute, type of data, normalise data?, stride, offset)
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat val = (sin(glfwGetTime()) / 2);

		// request location of uniforms
		GLint xoff = glGetUniformLocation(shaderProgram.Program, "xOffset");

		// Draw our first triangle
		shaderProgram.Use();

		//set values of uniforms
		glUniform1f(xoff, val);

		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}