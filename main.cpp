#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "wrapper/checkError.h"
#include "application/Application.h"

void onResize(int width, int height);
void onKey(int key, int scancode, int action, int mods);

int main() {

	Application* app = Application::getInstance();
	if (!app->init()) {
		return -1;
	}
	

	//设置监听回调
	app->setResizeCallback(onResize);
	app->setKeyCallback(onKey);


	// 设置opengl视口(坐标是左下开始，向右是x正， 向上是y正)
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);



	// 窗体循环
	while (app->update()) {
		// 画布清理
		glClear(GL_COLOR_BUFFER_BIT);
	}

	app->destory();

	return 0;
}


void onResize(int width,int height) {
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
void onKey(int key, int scancode, int action, int mods) {
	std::cout << "key input key:" << key << " scancode:" << scancode << " action:" << action << " mods:" << mods << "\n";
}