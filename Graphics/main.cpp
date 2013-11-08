#include <iostream>

#include <Windows.h>

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

	glEnable(GL_TEXTURE_2D);

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

	//glUseProgram(shaderID);

	unsigned char header[124];

	FILE *fp;

	fopen_s(&fp, "..\\resources\\Gust.dds", "rb");

	char filecode[4];
	fread(filecode, 1, 4, fp);
	if(strncmp(filecode, "DDS ", 4) != 0)
	{
		fclose(fp);
		return 0;
	}

	fread(&header, 124, 1, fp);
	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	unsigned char* buffer;
	unsigned int bufsize;
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	auto rv = fread(buffer, 1, bufsize, fp);
	fclose(fp);

	unsigned int components = (fourCC == mmioFOURCC('D', 'X', 'T', '1'));
	unsigned int format;
	switch(fourCC)
	{
	case mmioFOURCC('D','X','T','1'):
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case mmioFOURCC('D','X','T','3'):
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case mmioFOURCC('D','X','T','5'):
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	for(unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3)/4) * ((height + 3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);
		offset += size;
		width /= 2;
		height /= 2;
	}
	free(buffer);

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
		glTexCoord2f(0, 0);
		glColor3f(1, 0, 0);
		glVertex3f(-0.6f, -0.6f, 0);
		glTexCoord2f(1, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0.6f, -0.6f, 0);
		glTexCoord2f(1, 1);
		glColor3f(0, 0, 1);
		glVertex3f(0.6f, 0.6f, 0);
		glTexCoord2f(0, 1);
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