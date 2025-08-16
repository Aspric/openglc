#pragma once

#include "core.h"
#include <string>

class Shader {
public:
	Shader(const char* vertextFilePath,const char* fragmentFilePath);
	~Shader();

	// ��ʼʹ��Shader
	void begin();

	// ����ʹ��Shader
	void end();

	// ����float���͵�uniform
	void setFloat(const std::string& name, float value);

	void setVector3(const std::string& name, float value1, float value2, float value3);
private:
	GLuint mProgram{ 0 };

};
