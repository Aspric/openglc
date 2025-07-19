#include "checkError.h"
#include "glad/glad.h"
#include <string>
#include <iostream>
#include <assert.h>

void checkError() {
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR) {
		std::string errorStr = "";
		switch (errorCode) {
		case GL_INVALID_ENUM:errorStr = "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE:errorStr = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:errorStr = "GL_INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY:errorStr = "GL_OUT_OF_MEMORY"; break;
		default:errorStr = "UNKOWN";
		}

		std::cout << "glad error:" << errorStr << "\n";
		assert(false);
	}

}