#include "Application.h"
#include "Application.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ��ʼ����̬����
Application* Application::mInstance = nullptr;

Application* Application::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}

bool Application::init(const int& width,const int& height) {
	mWidth = width;
	mHeight = height;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// ��������ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//�����������
	mWindow = glfwCreateWindow(mWidth, mHeight, "OPENGL_STUDY", NULL, NULL);
	if (mWindow == NULL) return false;
	// ����windowΪopengl�Ļ�����̨
	glfwMakeContextCurrent(mWindow);
	// ��������opengl��ʵ�ֺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize GLAD" << "\n";
		return false;
	}
	// ���ûص�
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	glfwSetKeyCallback(mWindow, keyCallback);
	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(mWindow)) return false;

	glfwPollEvents();
	glfwSwapBuffers(mWindow);
	return true;
}

void Application::destory()
{
	glfwTerminate();
}

void Application::frameBufferSizeCallback(GLFWwindow* window,int width, int height)
{
	if (Application::getInstance()->mResizeCallback != nullptr) Application::getInstance()->mResizeCallback(width, height);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (Application::getInstance()->mKeyCallback != nullptr) Application::getInstance()->mKeyCallback(key, scancode, action, mods);
}


Application::Application() {

}

Application::~Application() {

}