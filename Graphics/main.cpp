#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int main(int argc, char** argv)
{
	if(!glfwInit())
	{
		cerr <<"Failed to initialize GLFW" <<endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK)
	{
		cerr <<"Failed to initialize GLEW" <<endl;
		return -1;
	}

	GLuint shaderVP = glCreateShader(GL_VERTEX_SHADER);
	GLuint shaderFP = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText = "void main() { gl_FrontColor = gl_Color; gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; }";
	const char* fsText = "void main() { gl_FragColor = normalize(vec4(0.0, 0.25, 0.0, 0.0) + (gl_Color * 0.5)); }";

	glShaderSource(shaderVP, 1, &vsText, 0);
	glShaderSource(shaderFP, 1, &fsText, 0);

	glCompileShader(shaderVP);
	glCompileShader(shaderFP);

	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, shaderFP);
	glAttachShader(shaderID, shaderVP);
	glLinkProgram(shaderID);

	glUseProgram(shaderID);

	while (!glfwWindowShouldClose(window))
	{
		double ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		ratio = width / (double)height;
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1, 1, 1, -1);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glRotatef((float) glfwGetTime() * 50, 0, 0, 1);

		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3f(-0.6f, -0.6f, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0.6f, -0.6f, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0.6f, 0.6f, 0);
		glColor3f(1, 1, 0);
		glVertex3f(-0.6f, 0.6f, 0);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDetachShader(shaderID, shaderFP);
	glDetachShader(shaderID, shaderVP);

	glDeleteShader(shaderFP);
	glDeleteShader(shaderVP);
	glDeleteShader(shaderID);

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}