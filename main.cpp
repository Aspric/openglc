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
	// 启动核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗体对象
	GLFWwindow* window = glfwCreateWindow(800, 600, "OPENGL_STUDY", NULL, NULL);
	// 设置window为opengl的绘制舞台
	glfwMakeContextCurrent(window);

	//设置监听回调
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	// 加载所有opengl的实现函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize GLAD" << "\n";
		return -1;
	}
	// 设置opengl视口(坐标是左下开始，向右是x正， 向上是y正)
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);



	// 窗体循环
	while (!glfwWindowShouldClose(window)) {
		// 检查并分发消息队列消息
		glfwPollEvents();
		// 画布清理
		glClear(GL_COLOR_BUFFER_BIT);
		// todo 渲染

		//切换双缓存
		glfwSwapBuffers(window);

		checkError();

	}

	// 清理
	glfwTerminate();
	


	return 0;
}


void frameBufferSizeCallback(GLFWwindow* window,int width,int height) {
	std::cout << "new size is:w" << width <<" h" << height << "\n";
	// glfw的画布跟随屏幕大小改变
	glViewport(0, 0, width, height);
}

/*
* key 字母码 
* scancode 物理按键码
* action按下/抬起 
* mods带shift ctrl
*/
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << "key input key:" << key << " scancode:" << scancode << " action:" << action << " mods:" << mods << "\n";
}