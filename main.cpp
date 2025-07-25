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

/*
* vbo ����mesh��Ϣ
* vao Ϊ�˿��ٶ�ȡvbo��Ϣ������mesh�ĵ�n�����ߡ�λ���Ƕ���
*/

void testBindSingleBuffer() {
	float position[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f,
	};
	float color[] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
	};

	//����posVbo colorVbo
	GLuint posVbo, colorVbo;
	glGenBuffers(1, &posVbo);
	glGenBuffers(1, &colorVbo);

	//�л�״̬�������黺����
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	//���뻺��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	//����vao
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// ��vao���posVbo colorVbo
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);//�л�״̬��������
	glEnableVertexAttribArray(0);//���ǰ�����ĵ�VertexArrayd��0��λ

	/*
	* --------------------------------------------------------------- 
	* |	1	2	3	4	5 .....    123��һ����������  345��һ����������	|
	* | ��������float���͵�											|
	* ---------------------------------------------------------------
	*/
	glVertexAttribPointer(0,//vao�е�λ��
		3,					//��ǰ�����м���
		GL_FLOAT,			//����
		GL_FALSE,			//�Ƿ��һ��
		3 * sizeof(float),	//����֮��Ŀ�ȴ�С
		(void*)0);			//��ʼ��ȡ��ƫ����(����ֱ��д0)

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);//���ǰ�����ĵ�VertexArrayd��1��λ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);//����ǰ��vao���
}

void testBindInterleavedBuffer() {
	//��λ�ú���ɫ������һ��������   λ��-��ɫ
	float vertices[] = {
		-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,
	};


	//����posVbo colorVbo
	GLuint vbo;
	glGenBuffers(1, &vbo);

	//�л�״̬�������黺����
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//���뻺��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//����vao
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// ��vao���vbo
	glEnableVertexAttribArray(0);//���ǰ�����ĵ�VertexArrayd��0��λ
	// ���λ����Ϣ
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(1);//���ǰ�����ĵ�VertexArrayd��1��λ
	// �����ɫ��Ϣ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	glBindVertexArray(0);//����ǰ��vao���
}