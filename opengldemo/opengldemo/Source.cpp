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
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.hpp"

float mixvalue = 0.5f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -0.1f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float delatime = 0.0f;
float lasttime = 0.0f;
bool bFirstMouse = true;
float lastX = 400;
float lastY = 300;
float yaw = 0.0f;
float pitch = 0.0f;
float fov = 45.0f;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(1.2f, 0.5f, 2.0f);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (bFirstMouse){
		lastX = xpos;
		lastY = ypos;
		bFirstMouse = false;
		return;
	}
	float offsetX = xpos - lastX;
	float offsetY = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(offsetX, offsetY);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = 0.0005f*delatime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		camera.ProcessKeyboard(FORWARD, delatime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		camera.ProcessKeyboard(BACKWARD, delatime);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		camera.ProcessKeyboard(LEFT, delatime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		camera.ProcessKeyboard(RIGHT, delatime);
	}
}

float firstTriangle[] = {
  0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
 -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
  0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部  // top 
};

float vertices[] = {
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
unsigned int LoadTexTure()
{
	unsigned int texture;
	glGenTextures(1, &texture);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("D:\\PersonGit\\container2.png", &width, &height, &nrChannels, 0);
	if (data){
		GLenum format;
		if (nrChannels == 1){
			format = GL_RED;
		}else if (nrChannels == 3){
			format = GL_RGB;
		}else if (nrChannels == 4){
			format = GL_RGBA;
		}
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	return texture;
}

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
	int nwndWidth = 800;
	int nwndHeight = 600;
	glViewport(0, 0, nwndWidth, nwndHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//------------------------------------------------------------------------------------
	//顶点属性个数
	int nCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nCount);

	Shader lightingshader("D:\\PersonGit\\opengl_learn\\opengldemo\\opengldemo\\vertex.vs","D:\\PersonGit\\opengl_learn\\opengldemo\\opengldemo\\fragment.fs");
	Shader lampshader("D:\\PersonGit\\opengl_learn\\opengldemo\\opengldemo\\lamp.vs", "D:\\PersonGit\\opengl_learn\\opengldemo\\opengldemo\\lamp.fs");

	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int texture = LoadTexTure();
	
	
	lightingshader.use();
	lightingshader.setInt("material.diffuse", 0);


	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	while (!glfwWindowShouldClose(window)){
		float currenttiem = glfwGetTime();
		delatime = currenttiem - lasttime;
		delatime = currenttiem;
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture);

		lightingshader.use();
		lightingshader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		lightingshader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		lightingshader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		lightingshader.setFloat("material.shininess", 32.0f);

		glm::vec3 lightColor = glm::vec3(1.0f,0.5f,0.8f);
		//lightColor.x = sin(glfwGetTime()*2.0f);
		//lightColor.y = sin(glfwGetTime()*0.7f);
		//lightColor.z = sin(glfwGetTime()*1.3f);

		glm::vec3 diffusecolor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientcolor = diffusecolor * glm::vec3(0.2f);
		lightingshader.setVec3("light.diffuse", diffusecolor);
		lightingshader.setVec3("light.ambient", ambientcolor);
		lightingshader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


		lightingshader.setVec3("lightPos", lightPos);
		lightingshader.setVec3("cameraPos", camera.Position);
		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(nwndWidth) / (float)nwndHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightingshader.setMat4("projection", projection);
		lightingshader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		float angel = glfwGetTime();
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.5f, 0.0f));
		lightingshader.setMat4("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lampshader.use();
		lampshader.setMat4("projection", projection);
		lampshader.setMat4("view", view);

		
		lightPos.x = 1.0f + sin(glfwGetTime())*1.0f;
		lightPos.y = 1.0 + sin(glfwGetTime())*1.0f;
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lampshader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}