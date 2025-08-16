#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "../wrapper/checkError.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Shader::Shader(const char* vertextFilePath, const char* fragmentFilePath)
{
	std::string vertexCode;
	std::string fragmentCode;
	// ���ڶ�ȡvs fs�ļ���inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// ���ļ�
		vShaderFile.open(vertextFilePath);
		fShaderFile.open(fragmentFilePath);
		// ���ļ��������ַ������뵽stringStream
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// �ر��ļ�
		vShaderFile.close();
		fShaderFile.close();
		// ��ȡ��
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "��ȡ�ļ�����:" << e.what() << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

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
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &isSuccess);
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
	// ����һ��mProgram����
	mProgram = glCreateProgram();
	// ����õ�fs vs����program
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);
	// program�������ɿ�ִ�г���
	glLinkProgram(mProgram);
	glGetProgramiv(mProgram, GL_LINK_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetProgramInfoLog(mProgram, 1024, NULL, infoLog);
		std::cout << "��ɫ�����ӳ���:\n" << infoLog << "\n";
	}
	// ����
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::begin()
{
	glUseProgram(mProgram);
}

void Shader::end()
{
	glUseProgram(0);
}

void Shader::setFloat(const std::string& name, float value)
{
	// ��ȡ��Ϊname��uniform���ڵ�λ��
	GLuint location = glGetUniformLocation(mProgram, name.c_str());
	// ����
	glUniform1f(location, value);
}

void Shader::setVector3(const std::string& name, float value1, float value2, float value3)
{
	// ��ȡ��Ϊname��uniform���ڵ�λ��
	GLuint location = glGetUniformLocation(mProgram, name.c_str());
	// ����
	glUniform3f(location, value1, value2, value3);
}
