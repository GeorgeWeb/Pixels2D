#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

using namespace std;
using namespace Pixels2D;

GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
{}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const string &vertexShaderPath, const string &fragmentShaderPath)
{
	// get a shader program object
	_programID = glCreateProgram();

	// get a vertex shader object
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) // check for errors
		Errors::fatalError("Vertex shader failed to be created!");
	
	// get a fragment shader object
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) // check for errors
		Errors::fatalError("Fragment shader failed to be created!");

	// compile each shader
	compileShader(vertexShaderPath, _vertexShaderID);
	compileShader(fragmentShaderPath, _fragmentShaderID);
}

void GLSLProgram::linkShaders()
{
	// attach shaders to program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// link program
	glLinkProgram(_programID);

	// check program - 'if shaders are linked'
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked); // could use safer 'reinterpret_cast<int*>' but cannot with GLint...
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength includes the NULL character
		vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		// don't need the program anymore
		glDeleteProgram(_programID);
		// avoid leaks in shaders either
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		// print the infolog and exit with failure
		printf("%s\n", &errorLog[0]);
		Errors::fatalError("Shaders failed to link!");
	}

	// detach shaders after a successful link
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	// avoid leaks in shaders either
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const string &attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLuint GLSLProgram::getUniformLocation(const string &uniformName)
{
	// save uniform location
	GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
	// check for any errors/if exists
	if (location == GL_INVALID_INDEX)
		Errors::fatalError("Uniform " + uniformName + " not found in shader!");
	// return the GLuint location object
	return location;
}

void GLSLProgram::use()
{
	// bind shader program
	glUseProgram(_programID);
	// enable vertex attributes
	for (unsigned int i = 0; i < _numAttributes; i++)
		glEnableVertexAttribArray(i);
}

void GLSLProgram::unuse()
{
	// unbind shader program
	glUseProgram(0);
	// disable vertex attributes
	for (unsigned int i = 0; i < _numAttributes; i++)
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