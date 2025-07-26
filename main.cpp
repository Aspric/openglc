#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "wrapper/checkError.h"
#include "application/Application.h"

void onResize(int width, int height);
void onKey(int key, int scancode, int action, int mods);
void testShader();
void testBindInterleavedBuffer();
void render();

GLint program;
GLuint vao;

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

	testShader();
	testBindInterleavedBuffer();

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

void testShader() {
	const char* vertexShaderSource = 
		"#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}\0";
	const char* fragmentShaderSource = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f,0.5f,0.2f,1.0);\n"
		"}\0";
	// ����vs��fs��shader����
	GLuint vertex, fragment;//����ľ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	// Ϊshader��������Դ��
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);//��Ϊsource��\0��β�ģ�����ָ������
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);//��Ϊsource��\0��β�ģ�����ָ������
	// ����shader
	int isSuccess = 0;
	char infoLog[1024];
	glCompileShader(vertex);
	glGetShaderiv(vertex,GL_COMPILE_STATUS,&isSuccess);
	if (!isSuccess) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "���붥����ɫ������:\n" << infoLog << "\n";
	}
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		std::cout << "����Ƭ����ɫ������:\n" << infoLog << "\n";
	}
	// ����һ��program����
	program = 0;
	program = glCreateProgram();
	// ����õ�fs vs����program
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	// program�������ɿ�ִ�г���
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		std::cout << "��ɫ�����ӳ���:\n" << infoLog << "\n";
	}
	// ����
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void render() {
	// ��������
	glClear(GL_COLOR_BUFFER_BIT);
	// ��program
	glUseProgram(program);
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
	glDrawArrays(GL_TRIANGLES, 0, 3);
}