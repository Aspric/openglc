#pragma once
#include <cstdint>

/*
* 封装Application
* 单例类
*/

class GLFWwindow;
// 声明函数指针类型
using ResizeCallback = void(*)(int width, int height);
using KeyCallback = void(*)(int key, int scancode, int action, int mods);

class Application {
public:
	~Application();

	// 获取实例
	static Application* getInstance();

	bool init(const int& width=800, const int& height=600);

	bool update();

	void destory();

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyCallback(KeyCallback callback) { mKeyCallback = callback; }

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }
private:
	static void frameBufferSizeCallback(GLFWwindow* window,int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	// 全局唯一的静态变量实例
	static Application* mInstance;
	ResizeCallback mResizeCallback{ nullptr };
	KeyCallback mKeyCallback{ nullptr };
	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };

	GLFWwindow* mWindow{ nullptr };
	Application();
};