// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<time.h>

//#include "Source.cpp"
#include <vector>

// Include GLEW
#include <GL/glew.h>
#include "program.h"
// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>


struct Point {
	float x, y, z;
	Point(float p1, float p2, float p3)
	{
		x = p1;
		y = p2;
		z = p3;
	}
};
/*
class Triangle {
public:
Point p1, p2, p3;
GLfloat color[4];

Triangle(Point p, Point pp, Point ppp, float c1 = 0, float c2 = 0, float c3 = 0, float c4 = 0)
{
p1 = p;
p2 = pp;
p3 = ppp;
color[0] = c1;
color[1] = c2;
color[2] = c3;
color[3] = c4;
}

Triangle(Point p, Point pp, Point ppp, bool gradient = false)
{
p1 = p;
p2 = pp;
p3 = ppp;

if (gradient)
{
color[0] = rand();
color[1] = rand();
color[2] = rand();
}
else
{
color[0] = color[1] = color[2] = rand();
}
}

};
*/
class Mesh {
public:

	//vector<Triangle*> Triangles;
	int vertices = 0;
	GLuint vertexbuffer, colorbuffer;
	Mesh(float* surs) {

		int siz2 = (surs[0] - 1) / 3;
		int siz = siz2 * 4;

		static GLfloat g_vertex_buffer_data[10000];
	//	GLfloat g_color_buffer_data[1000];
		static GLfloat g_color_buffer_data[10000];
		int n = 1;
		GLfloat colr=0.0f,colg=0.0f,colb=0.0f;
		srand(time(NULL));
		for (int i = 0; i < siz; i+=12)
		{
			colr = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			colg = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			colb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g_color_buffer_data[i] = colr;
			g_color_buffer_data[i+ 1] = colg;
			g_color_buffer_data[i + 2] = colb;
			g_color_buffer_data[i + 3] = 1.0f;
			g_color_buffer_data[i + 4] = colr;
			g_color_buffer_data[i + 5] = colg;
			g_color_buffer_data[i + 6] = colb;
			g_color_buffer_data[i + 7] = 1.0f;
			g_color_buffer_data[i + 8] = colr;
			g_color_buffer_data[i + 9] = colg;
			g_color_buffer_data[i + 10] = colb;
			g_color_buffer_data[i + 11] = 1.0f;
		}
		vertices = (int)(surs[0] - 1);
		//Triangles.push_back()
		int index = 1;
		for (index = 1; index <= vertices; index++)
		{
			//	mesh_data[index-1] = surs[index];
			g_vertex_buffer_data[index - 1] = (GLfloat)surs[index];
		//	mesh_color[index - 1] = 0.5f;
		}


		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices, g_vertex_buffer_data, GL_STATIC_DRAW);
		//GLuint MatrixID = glGetUniformLocation(shaderID, "MVP");


		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER,  sizeof(GLfloat) * siz2*4, g_color_buffer_data, GL_STATIC_DRAW);
	}



	void Draw() {

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices); // 3 indices starting at 0 -> 1 triangle
											  //	glDrawArrays(GL_TRIANGLES, 1, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	~Mesh() {
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &colorbuffer);
	}
};

class Camera {
public:
	static float x, y;
	static double zoom;
};

float Camera::x = 0;
float Camera::y = 0;
double Camera::zoom = 10.0f;

class InputManager {
public:
	static struct mPOS {
		double x, y;
	}mouse_pos, last_pos;
	static int LB_PRESS;
	static void lastPos() {
		last_pos.x = mouse_pos.x;
		last_pos.y = mouse_pos.y;
	}
};
int InputManager::LB_PRESS = 0;
InputManager::mPOS InputManager::mouse_pos = mPOS();
InputManager::mPOS InputManager::last_pos = mPOS();

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::zoom -= yoffset / 20;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//InputManager::LB_PRESS = 0;
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		InputManager::LB_PRESS = 1;
	}
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Playground", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetScrollCallback(window, scroll_callback);



	// Dark blue background
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(Camera::x, Camera::y, 1 + Camera::zoom), // Camera is at (4,3,-3), in World Space
		glm::vec3(Camera::x, Camera::y, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	//input

	ifstream input_file("input.txt");
	float temp1, temp2;
	int nrel;
	float *data_changed, *data_unchanged;
	//static float *final_draw;
	input_file >> nrel;
	data_changed = new float[nrel * 2 + 1];
	data_unchanged = new float[nrel * 2 + 1];
	data_changed[0] = data_unchanged[0] = nrel;
	for (int i = 0; i < nrel; i++) {
		input_file >> data_unchanged[i * 2 + 1] >> data_unchanged[i * 2 + 2];
		data_changed[i * 2 + 1] = data_unchanged[i * 2 + 1];
		data_changed[i * 2 + 2] = data_unchanged[i * 2 + 2];
	}
	float afin11, afin12, afin21, afin22;
	input_file >> afin11 >> afin12 >> afin21 >> afin22;
	//	float temp1, temp2;
	/*for (int i = 0; i < nrel; i++)
	{
		temp1 = data_changed[i * 2 + 1];
		temp2 = data_changed[i * 2 + 2];
		data_changed[i * 2 + 1] = temp1*afin11 + temp2*afin12;
		data_changed[i * 2 + 2] = temp1*afin21 + temp2*afin22;
	}*/
	program::Triangulate(data_unchanged);
	program::final_draw[0] = (nrel - 2) * 3 * 3 * 2 + 1;
	for (int i = 0; i < (nrel - 2) * 3; i++)
	{
		temp1 = program::mash[i * 3 + 1];
		temp2 = program::mash[i * 3 + 2];
		program::final_draw[i * 3 + 1] = temp1*afin11 + temp2*afin12;
		program::final_draw[i * 3 + 2] = temp1*afin21 + temp2*afin22;
		program::final_draw[i * 3 + 3] = 0;
	}
	program::Triangulate(data_changed);

	const float DISTANTA = 6;


	for (int i = 0; i < (nrel - 2) * 3; i++)
	{
		temp1 = program::mash[i * 3 + 1];
		temp2 = program::mash[i * 3 + 2];
		program::final_draw[(i + (nrel - 2) * 3) * 3 + 1] = temp1 + DISTANTA;
		program::final_draw[(i + (nrel - 2) * 3) * 3 + 2] = temp2;
		program::final_draw[(i + (nrel - 2) * 3) * 3 + 3] = 0;
	}

	Mesh ourMesh(program::final_draw);

	do {



		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			if (InputManager::LB_PRESS == 0)
			{
				glfwGetCursorPos(window, &InputManager::mouse_pos.x, &InputManager::mouse_pos.y);
				InputManager::lastPos();
			}
			InputManager::LB_PRESS = 1;
		}
		else
		{
			InputManager::LB_PRESS = 0;
		}
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		if (InputManager::LB_PRESS) {
			InputManager::lastPos();
			glfwGetCursorPos(window, &InputManager::mouse_pos.x, &InputManager::mouse_pos.y);
			Camera::x += (InputManager::last_pos.x - InputManager::mouse_pos.x) / (10 * Camera::zoom);
			Camera::y -= (InputManager::last_pos.y - InputManager::mouse_pos.y) / 10 / Camera::zoom;

		//	std::cout << "campos x: " << Camera::x << " ";
		//	std::cout << "campos y: " << Camera::y << "\n";

			//std::cout << "lastpos x: " << InputManager::last_pos.x << " ";
			//	std::cout << "lastpos y: " << InputManager::last_pos.y<<"\n";
		}


		glm::mat4 View = glm::lookAt(
			glm::vec3(Camera::x, Camera::y, 1 + Camera::zoom), // Camera is at (4,3,-3), in World Space
			glm::vec3(Camera::x, Camera::y, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		// Our ModelViewProjection : multiplication of our 3 matrices
		MVP = Projection * View * Model;


		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		/*
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		4,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3 * 4); // 3 indices starting at 0 -> 1 triangle
		//	glDrawArrays(GL_TRIANGLES, 1, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		*/

		ourMesh.Draw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	//Cleanup VBO
	//glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);


	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

