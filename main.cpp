#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "wrapper/checkError.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// ��������ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�����������
	GLFWwindow* window = glfwCreateWindow(800, 600, "OPENGL_STUDY", NULL, NULL);
	// ����windowΪopengl�Ļ�����̨
	glfwMakeContextCurrent(window);

	//���ü����ص�
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	// ��������opengl��ʵ�ֺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize GLAD" << "\n";
		return -1;
	}
	// ����opengl�ӿ�(���������¿�ʼ��������x���� ������y��)
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);



	// ����ѭ��
	while (!glfwWindowShouldClose(window)) {
		// ��鲢�ַ���Ϣ������Ϣ
		glfwPollEvents();
		// ��������
		glClear(GL_COLOR_BUFFER_BIT);
		// todo ��Ⱦ

		//�л�˫����
		glfwSwapBuffers(window);

		checkError();

	}

	// ����
	glfwTerminate();
	


	return 0;
}


void frameBufferSizeCallback(GLFWwindow* window,int width,int height) {
	std::cout << "new size is:w" << width <<" h" << height << "\n";
	// glfw�Ļ���������Ļ��С�ı�
	glViewport(0, 0, width, height);
}

/*
* key ��ĸ�� 
* scancode ��������
* action����/̧�� 
* mods��shift ctrl
*/
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << "key input key:" << key << " scancode:" << scancode << " action:" << action << " mods:" << mods << "\n";
}