#include "GLSLProgram.h"
#include "Errors.h"
#include <vector>
#include <fstream>
namespace Aether
{
	GLSLProgram::GLSLProgram() :
		m_NumAttributes(0),
		m_ProgramID(0),
		m_VertexShaderID(0),
		m_FragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{

		m_ProgramID = glCreateProgram();

		m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (m_VertexShaderID == 0)
		{
			fatalError("Vertex Shader failed to be created!");
		}

		m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_FragmentShaderID == 0)
		{
			fatalError("Fragment Shader failed to be created!");
		}

		compileShader(vertexShaderFilePath, m_VertexShaderID);
		compileShader(fragmentShaderFilePath, m_FragmentShaderID);

	}

	void GLSLProgram::LinkShaders()
	{
		//Vertex and fragment shaders are successfully compiled.
		//Now time to link them together into a program.

		//Attach our shaders to our program
		glAttachShader(m_ProgramID, m_VertexShaderID);
		glAttachShader(m_ProgramID, m_FragmentShaderID);

		//Link our program
		glLinkProgram(m_ProgramID);

		//Note the different functions here: glGetProgram* instead of glGetShader*/
		GLint isLinked = 0;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(m_ProgramID);
			//Don't leak the shaders either.
			glDeleteShader(m_VertexShaderID);
			glDeleteShader(m_FragmentShaderID);

			//Use the infoLog as you see fit.
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to Link");
			//in this simple program, we'll just leave
		}

		//Always deatch shaders after a successful link.
		glDetachShader(m_ProgramID, m_VertexShaderID);
		glDetachShader(m_ProgramID, m_FragmentShaderID);


	}

	void GLSLProgram::addAttribute(const std::string & attributeName)
	{
		glBindAttribLocation(m_ProgramID, m_NumAttributes++, attributeName.c_str());
	}

	void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
	{
		std::ifstream shaderFile(filePath);
		if (shaderFile.fail())
		{
			perror(filePath.c_str());
			fatalError("Failed ot open " + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(shaderFile, line))
		{
			fileContents += line + "\n";
		}

		shaderFile.close();
		const char* contentPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Provide the infolog in whatever manor you deem best.
			//Exit with failure
			glDeleteShader(id); //Don't leak the shader

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile");


			return;
		}
	}

	GLuint GLSLProgram::GetUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniformName + " not found in shader!");
		}
		return location;
	}

	void GLSLProgram::UseProgram()
	{
		glUseProgram(m_ProgramID);
		for (int i = 0; i < m_NumAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::UnuseProgram()
	{
		glUseProgram(0);
		for (int i = 0; i < m_NumAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}
}