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
	

	//���ü����ص�
	app->setResizeCallback(onResize);
	app->setKeyCallback(onKey);


	// ����opengl�ӿ�(���������¿�ʼ��������x���� ������y��)
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);



	// ����ѭ��
	while (app->update()) {
		// ��������
		glClear(GL_COLOR_BUFFER_BIT);
	}

	app->destory();

	return 0;
}


void onResize(int width,int height) {
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
void onKey(int key, int scancode, int action, int mods) {
	std::cout << "key input key:" << key << " scancode:" << scancode << " action:" << action << " mods:" << mods << "\n";
}