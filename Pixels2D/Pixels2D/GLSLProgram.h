#ifndef GLSLPROGRAM_HGUARD
#define GLSLPROGRAM_HGUARD

#include <GL/glew.h>

#include <iostream>
#include <string>

namespace Pixels2D
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		void linkShaders();
		void addAttribute(const std::string &attributeName);
		GLuint getUniformLocation(const std::string &uniformName);
		void use();
		void unuse();

	private:
		GLuint m_programID;
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;

		int m_numAttributes;

	private:
		// compiles a single shader file
		void compileShader(const std::string& filePath, GLuint shaderID);
	};
}

#endif // !GLSLPROGRAM_HGUARD