#pragma once

#include "core.h"

class Shader {
public:
	Shader(const char* vertextFilePath,const char* fragmentFilePath);
	~Shader();

	// ��ʼʹ��Shader
	void begin();

	// ����ʹ��Shader
	void end();
private:
	GLuint mProgram{ 0 };

};
