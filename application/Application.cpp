#include "Application.h"
#include "Application.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 初始化静态变量
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
	// 启动核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//创建窗体对象
	mWindow = glfwCreateWindow(mWidth, mHeight, "OPENGL_STUDY", NULL, NULL);
	if (mWindow == NULL) return false;
	// 设置window为opengl的绘制舞台
	glfwMakeContextCurrent(mWindow);
	// 加载所有opengl的实现函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize GLAD" << "\n";
		return false;
	}
	// 设置回调
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