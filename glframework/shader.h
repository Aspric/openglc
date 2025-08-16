#pragma once

#include "core.h"
#include <string>

class Shader {
public:
	Shader(const char* vertextFilePath,const char* fragmentFilePath);
	~Shader();

	// 开始使用Shader
	void begin();

	// 结束使用Shader
	void end();

	// 设置float类型的uniform
	void setFloat(const std::string& name, float value);

	void setVector3(const std::string& name, float value1, float value2, float value3);
private:
	GLuint mProgram{ 0 };

};
