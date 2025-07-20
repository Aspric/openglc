#pragma once
#include <cstdint>

/*
* ��װApplication
* ������
*/

class GLFWwindow;
// ��������ָ������
using ResizeCallback = void(*)(int width, int height);
using KeyCallback = void(*)(int key, int scancode, int action, int mods);

class Application {
public:
	~Application();

	// ��ȡʵ��
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
	// ȫ��Ψһ�ľ�̬����ʵ��
	static Application* mInstance;
	ResizeCallback mResizeCallback{ nullptr };
	KeyCallback mKeyCallback{ nullptr };
	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };

	GLFWwindow* mWindow{ nullptr };
	Application();
};