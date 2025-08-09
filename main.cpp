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
	

	//设置监听回调
	app->setResizeCallback(onResize);
	app->setKeyCallback(onKey);


	// 设置opengl视口(坐标是左下开始，向右是x正， 向上是y正)
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	shader = new Shader("assets/shaders/vertex.glsl","assets/shaders/fragment.glsl");

	//testBindInterleavedBuffer();
	prepareVAO();
	// 窗体循环
	while (app->update()) {

		render();

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

/*
* vbo 保存mesh信息
* vao 为了快速读取vbo信息，比如mesh的第n个法线、位置是多少
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

	//生成posVbo colorVbo
	GLuint posVbo, colorVbo;
	glGenBuffers(1, &posVbo);
	glGenBuffers(1, &colorVbo);

	//切换状态机到数组缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	//传入缓冲区对象
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	//生成vao
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 向vao添加posVbo colorVbo
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);//切换状态机上下文
	glEnableVertexAttribArray(0);//激活当前上下文的VertexArrayd的0号位

	/*
	* --------------------------------------------------------------- 
	* |	1	2	3	4	5 .....    123是一个顶点数据  345是一个顶点数据	|
	* | 该数据是float类型的											|
	* ---------------------------------------------------------------
	*/
	glVertexAttribPointer(0,//vao中的位置
		3,					//当前数据有几个
		GL_FLOAT,			//类型
		GL_FALSE,			//是否归一化
		3 * sizeof(float),	//数据之间的跨度大小
		(void*)0);			//开始读取的偏移量(可以直接写0)

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);//激活当前上下文的VertexArrayd的1号位
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);//将当前的vao解绑
}

void testBindInterleavedBuffer() {
	//将位置和颜色保存在一个对象中   位置-颜色
	float vertices[] = {
		-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,
		1.0f,0.3f,0.6f,0.0f,0.0f,1.0f,
	};


	//生成posVbo colorVbo
	GLuint vbo;
	glGenBuffers(1, &vbo);

	//切换状态机到数组缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//传入缓冲区对象
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//生成vao
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 向vao添加vbo
	glEnableVertexAttribArray(0);//激活当前上下文的VertexArrayd的0号位
	// 添加位置信息
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(1);//激活当前上下文的VertexArrayd的1号位
	// 添加颜色信息
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	glBindVertexArray(0);//将当前的vao解绑
}

void render() {
	// 画布清理
	glClear(GL_COLOR_BUFFER_BIT);
	shader->begin();
	// 绑定vao
	glBindVertexArray(vao);
	// 绘制
	/* 有点 0 1 2 3 4 5 6   
	* GL_TRIANGLES 0 1 2|3 4 5 不足的不绘制
	* GL_TRIANGLE_STRIP  0 1 2| 2 1 3|2 3 4|4 3 5   一个三角形最后一个Index为n n为奇数 [n-2,n-1,n] n为偶数 [n-1,n-2,n](总会保持逆时针的顺序)
	* GL_TRIANGLE_FAN 扇形绘制 0 1 2|0 2 3|0 3 4|0 5 6
	* GL_LINES 0 1|2 3|3 4|4 5|5 6
	* GL_LINES_STRIP 0 1|1 2|2 3|3 4|4 5|5 6
	*/
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 
					6,					// 读几次索引
					GL_UNSIGNED_INT,
					0);					// 偏移量 比如要偏移3个就写 (void*)(sizeof(int)*3)
	shader->end();
}

// 创建vbo ebo vao数据
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
	// 创建vbo
	GLuint positionVbo = 0,colorVbo = 0;
	glGenBuffers(1, &positionVbo);
	glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//创建ebo
	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//创建vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//绑定vbo
	glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 将Ebo和vao关联
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// 切换vao为空状态
	glBindVertexArray(0);
}