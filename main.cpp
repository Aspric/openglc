#include <iostream>
#include "glframework/core.h"
#include "glframework/shader.h"
#include "wrapper/checkError.h"
#include "application/Application.h"

void onResize(int width, int height);
void onKey(int key, int scancode, int action, int mods);
void testBindInterleavedBuffer();
void prepareVAO();
void render();

GLuint vao;
Shader* shader;

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

	shader = new Shader("assets/shaders/vertex.glsl","assets/shaders/fragment.glsl");

	//testBindInterleavedBuffer();
	prepareVAO();
	// ����ѭ��
	while (app->update()) {

		render();

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
	vao = 0;
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
		1.0f,0.3f,0.6f,0.0f,0.0f,1.0f,
	};


	//����posVbo colorVbo
	GLuint vbo;
	glGenBuffers(1, &vbo);

	//�л�״̬�������黺����
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//���뻺��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//����vao
	vao = 0;
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

void render() {
	// ��������
	glClear(GL_COLOR_BUFFER_BIT);
	shader->begin();
	// ��vao
	glBindVertexArray(vao);
	// ����
	/* �е� 0 1 2 3 4 5 6   
	* GL_TRIANGLES 0 1 2|3 4 5 ����Ĳ�����
	* GL_TRIANGLE_STRIP  0 1 2| 2 1 3|2 3 4|4 3 5   һ�����������һ��IndexΪn nΪ���� [n-2,n-1,n] nΪż�� [n-1,n-2,n](�ܻᱣ����ʱ���˳��)
	* GL_TRIANGLE_FAN ���λ��� 0 1 2|0 2 3|0 3 4|0 5 6
	* GL_LINES 0 1|2 3|3 4|4 5|5 6
	* GL_LINES_STRIP 0 1|1 2|2 3|3 4|4 5|5 6
	*/
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 
					6,					// ����������
					GL_UNSIGNED_INT,
					0);					// ƫ���� ����Ҫƫ��3����д (void*)(sizeof(int)*3)
	shader->end();
}

// ����vbo ebo vao����
void prepareVAO() {
	float positions[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.4f,0.0f,
		0.0f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
	};
	float colors[] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
		1.0f,1.0f,0.0f
	};
	unsigned int indices[] = {
		0,1,2,
		2,1,3
	};
	// ����vbo
	GLuint positionVbo = 0,colorVbo = 0;
	glGenBuffers(1, &positionVbo);
	glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//����ebo
	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//����vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//��vbo
	glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// ��Ebo��vao����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// �л�vaoΪ��״̬
	glBindVertexArray(0);
}