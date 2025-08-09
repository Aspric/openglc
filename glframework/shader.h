#pragma once

#include "core.h"

class Shader {
public:
	Shader(const char* vertextFilePath,const char* fragmentFilePath);
	~Shader();

	// 开始使用Shader
	void begin();

	// 结束使用Shader
	void end();
private:
	GLuint mProgram{ 0 };

};
