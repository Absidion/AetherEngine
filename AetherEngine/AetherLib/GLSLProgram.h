#pragma once

#include <glew.h>
#include <string>

namespace Aether
{

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void LinkShaders();

		void addAttribute(const std::string& attributeName);

		GLuint GetUniformLocation(const std::string& uniformName);

		void UseProgram();
		void UnuseProgram();

	private:

		void compileShader(const std::string& filePath, GLuint id);

		int m_NumAttributes;

		GLuint m_ProgramID;

		GLuint m_VertexShaderID;
		GLuint m_FragmentShaderID;


	};
}

