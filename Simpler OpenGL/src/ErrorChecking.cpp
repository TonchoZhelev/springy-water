#include "ErrorChecking.h"
#include <iostream>
#include <string>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	bool NoErrFlag = true; //assume there aren't any errors
	std::string errWord = "NoNameError";

	while (GLenum error = glGetError())
	{
		switch (error) {
		case GL_INVALID_ENUM: errWord = "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE: errWord = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: errWord = "GL_INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW: errWord = "GL_STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW: errWord = "GL_STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY: errWord = "GL_OUT_OF_MEMORY"; break;
		}

		std::cout << "[OpenGl Error] (0x" << std::hex << error << ": " << std::dec << errWord << " ): " << function << " " << file << ": " << line << std::endl;
		NoErrFlag = false;
	}

	return NoErrFlag;
}