#include "GLSLProgram.h"
#include "Pixels2DErrors.h"

#include <fstream>
#include <vector>

using namespace std;
using namespace Pixels2D;

GLSLProgram::GLSLProgram() : m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_numAttributes(0)
{}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const string &vertexShaderPath, const string &fragmentShaderPath)
{
	// get a shader program object
	m_programID = glCreateProgram();

	// get a vertex shader object
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0) // check for errors
		Errors::fatalError("Vertex shader failed to be created!");
	
	// get a fragment shader object
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0) // check for errors
		Errors::fatalError("Fragment shader failed to be created!");

	// compile each shader
	compileShader(vertexShaderPath, m_vertexShaderID);
	compileShader(fragmentShaderPath, m_fragmentShaderID);
}

void GLSLProgram::linkShaders()
{
	// attach shaders to program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	// link program
	glLinkProgram(m_programID);

	// check program - 'if shaders are linked'
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked); // could use safer 'reinterpret_cast<int*>' but cannot with GLint...
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength includes the NULL character
		vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		// don't need the program anymore
		glDeleteProgram(m_programID);
		// avoid leaks in shaders either
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		// print the infolog and exit with failure
		printf("%s\n", &errorLog[0]);
		Errors::fatalError("Shaders failed to link!");
	}

	// detach shaders after a successful link
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	// avoid leaks in shaders either
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::addAttribute(const string &attributeName)
{
	glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

GLuint GLSLProgram::getUniformLocation(const string &uniformName)
{
	// save uniform location
	GLuint location = glGetUniformLocation(m_programID, uniformName.c_str());
	// check for any errors/if exists
	if (location == GL_INVALID_INDEX)
		Errors::fatalError("Uniform " + uniformName + " not found in shader!");
	// return the GLuint location object
	return location;
}

void GLSLProgram::use()
{
	// bind shader program
	glUseProgram(m_programID);
	// enable vertex attributes
	for (unsigned int i = 0; i < m_numAttributes; i++)
		glEnableVertexAttribArray(i);
}

void GLSLProgram::unuse()
{
	// unbind shader program
	glUseProgram(0);
	// disable vertex attributes
	for (unsigned int i = 0; i < m_numAttributes; i++)
		glDisableVertexAttribArray(i);
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint shaderID) {

	//Open the file
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail()) {
		perror(filePath.c_str());
		Errors::fatalError("Failed to open " + filePath);
	}

	//File contents stores all the text in the file
	std::string fileContents = "";
	//line is used to grab each line of the file
	std::string line;

	//Get all the lines in the file and add it to the contents
	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}

	shaderFile.close();

	//get a pointer to our file contents c string;
	const char* contentsPtr = fileContents.c_str();
	//tell opengl that we want to use fileContents as the contents of the shader file
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);

	//compile the shader
	glCompileShader(shaderID);

	//check for errors
	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		//Provide the infolog in whatever manor you deem best.
		//Exit with failure.
		glDeleteShader(shaderID); //Don't leak the shader.

							//Print error log and quit
		printf("%s\n", &(errorLog[0]));
		Errors::fatalError("Shader " + filePath + " failed to compile");
	}
}