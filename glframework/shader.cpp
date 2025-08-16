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
	// 用于读取vs fs文件的inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// 打开文件
		vShaderFile.open(vertextFilePath);
		fShaderFile.open(fragmentFilePath);
		// 将文件输入流字符串输入到stringStream
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 关闭文件
		vShaderFile.close();
		fShaderFile.close();
		// 读取流
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "读取文件错误:" << e.what() << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	// 创建vs和fs的shader程序
	GLuint vertex, fragment;//程序的句柄
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	// 为shader程序输入源码
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);//因为source是\0结尾的，无需指定长度
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);//因为source是\0结尾的，无需指定长度
	// 编译shader
	int isSuccess = 0;
	char infoLog[1024];
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "编译顶点着色器出错:\n" << infoLog << "\n";
	}
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		std::cout << "编译片段着色器出错:\n" << infoLog << "\n";
	}
	// 创建一个mProgram程序
	mProgram = glCreateProgram();
	// 编译好的fs vs放入program
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);
	// program链接生成可执行程序
	glLinkProgram(mProgram);
	glGetProgramiv(mProgram, GL_LINK_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetProgramInfoLog(mProgram, 1024, NULL, infoLog);
		std::cout << "着色器链接出错:\n" << infoLog << "\n";
	}
	// 清理
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
	// 获取名为name的uniform所在的位置
	GLuint location = glGetUniformLocation(mProgram, name.c_str());
	// 更新
	glUniform1f(location, value);
}

void Shader::setVector3(const std::string& name, float value1, float value2, float value3)
{
	// 获取名为name的uniform所在的位置
	GLuint location = glGetUniformLocation(mProgram, name.c_str());
	// 更新
	glUniform3f(location, value1, value2, value3);
}
