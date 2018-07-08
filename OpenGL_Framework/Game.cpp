#include <iostream>
#include <memory>

#include "Game.h"
#include "shader.h"

using glm::mat4;
using glm::vec4;
using glm::vec3;
using std::cout;
using std::endl;

ShaderProgram shaderProgram;
Texture img1, img2 ,img3;
GLuint VBO, VAO, EBO;

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

Game::Game(Keyboard& kbd, Mouse& a_mouse)
	: keyboard(kbd), mouse(a_mouse)
{
}

glm::vec3 cameraPos, cameraFront, cameraUp;

static ShaderProgram sprogram;

void Game::setup()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	sprogram.setVertexShader(std::make_shared<VertexShader>("shaders/VS_math.glsl"));
	sprogram.setFragmentShader(std::make_shared<FragmentShader>("shaders/FS_math.glsl"));
	sprogram.compile();
	
	img1.loadImage("container.jpg");
	img2.loadImage("awesomeface.png");
	img3.loadImage("wall.jpg");

	glEnable(GL_DEPTH_TEST);

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// position          //tex coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	// generate the buffers

	/*
	 The vertex shader then processes as much vertices as we tell it to from its memory.

We manage this memory via so called vertex buffer objects (VBO) that can store a large number of vertices in the GPU's memory. 
The advantage of using those buffer objects is that we can send large batches of data all at once to the graphics card without 
having to send data a vertex a time.

A vertex buffer object is our first occurrence of an OpenGL object as we've discussed in the OpenGL tutorial. Just like any 
object in OpenGL this buffer has a unique ID corresponding to that buffer, so we can generate one with a buffer ID using
the glGenBuffers function:
	
	*/
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	{
		// set the VBO as the current buffer in OpenGL's state machine
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// set the size of the buffer and copy the vertices
		// GL_STATIC_DRAW means we wont be changing this often, so it is put into slow memory
		// GL_DYNAMIC_DRAW = likely to change, GL_STREAM_DRAW = will change every frame

		// copy user-defined data into the currently bound buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// attach a GL_ELEMENT_ARRAY_BUFFER to EBO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Tell OpenGL how it should interpret the data in the GL_ARRAY_BUFFER
		//glVertexAttribPointer(position number, size of attribute, type of data, normalise data?, stride, offset)
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);

		//texture attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);
}

GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame 
GLfloat yaw = 0.0;
GLfloat pitch = 0.0;
GLfloat fov = 45.0;


/*    -------------------------------- DRAW ----------------------------------    */
void Game::draw()
{
	// activate shader program
	sprogram.setActive();

	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//lookup uniforms
	GLuint model_loc = glGetUniformLocation(sprogram.m_program_id, "model"); // HACK
	GLuint view_loc = glGetUniformLocation(sprogram.m_program_id, "view");
	GLuint proj_loc = glGetUniformLocation(sprogram.m_program_id, "proj");

	mat4 view, proj;
	GLfloat radius = 10.0f;
	GLfloat camX = sin(glm::radians(glfwGetTime())*7) * radius;
	GLfloat camZ = cos(glm::radians(glfwGetTime())*9) * radius;

	fov = 22.5 + 22.5 * mouse.scrollY() / 100.0;

	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;

	yaw += mouse.dx()*0.05;
	pitch += mouse.dy()*0.05;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	GLfloat cameraSpeed = 5.0f * deltaTime * 10;
	if (keyboard.keys[GLFW_KEY_W] || keyboard.keys[GLFW_KEY_UP])
		cameraPos += cameraSpeed * cameraFront;
	if (keyboard.keys[GLFW_KEY_S] || keyboard.keys[GLFW_KEY_DOWN])
		cameraPos -= cameraSpeed * cameraFront;
	if (keyboard.keys[GLFW_KEY_A] || keyboard.keys[GLFW_KEY_LEFT])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keyboard.keys[GLFW_KEY_D] || keyboard.keys[GLFW_KEY_RIGHT])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	proj = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

	img1.bind();
	glUniform1i(glGetUniformLocation(sprogram.m_program_id, "ourTexture1"), 0);

	img2.bind();
	glUniform1i(glGetUniformLocation(sprogram.m_program_id, "ourTexture2"), 1);

	glBindVertexArray(VAO);
	for (GLuint i = 0; i < 10; i++)
	{
		mat4 model;
		model = glm::translate(model, cubePositions[i]);
		model = glm::translate(model, vec3(0,0,10));
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle, vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}

Game::~Game()
{
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
