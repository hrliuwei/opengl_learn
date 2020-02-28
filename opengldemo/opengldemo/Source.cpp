//#include "GLFW/"
//typedef void(*GL_GENBUFFERS)(GLsizei, GLuint*);
//GL_GENBUFFERS glGenbuffers = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
//GLuint buffer;
//glGenbuffers(1, &buffer);
//#define GLEW_STATIC
//#define GLEW_STATIC
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup")
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}

const char *vertextShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"    ourColor = aColor;\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"in vec3 ourColor;\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(ourColor,1.0);\n"
	"}\0";

float vertices2[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices2[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

float firstTriangle[] = {
  0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
 -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
  0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部  // top 
};
float secondTriangle[] = {
	0.5f, -0.5f, 0.0f,  // left
	-0.5f, -0.5f, 0.0f,  // right
	-0.5f, 0.5f, 0.0f   // top 
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "failed initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	//------------------------------------------------------------------------------------
	//顶点属性个数
	int nCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nCount);

	Shader shader("D:\\PersonGit\\opengl_learn\\opengldemo\\Debug\\vertex.vs","D:\\PersonGit\\opengl_learn\\opengldemo\\Debug\\fragment.fs");
	//Shader shader("vertex.vs", "fragment.fs");

	////顶点着色器
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);
	//glCompileShader(vertexShader);

	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success){
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	int i = 0;
	//	++i;
	//}
	////片段着色器
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success){
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//}
	//

	////链接
	//int shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success){
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//}

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);


	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);


	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//------------------------------------------------------------------------------------
	shader.use();
	while (!glfwWindowShouldClose(window)){
		processInput(window);
		//----------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//----------------------

		//画三角形
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}