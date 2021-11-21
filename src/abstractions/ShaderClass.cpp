#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileError(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileError(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileError(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


GLuint Shader::GetUniID(const char* name) {
	return glGetUniformLocation(ID, name);
}

void Shader::SetUniform(GLuint uniID, GLfloat value) {
	glUniform1f(uniID, value);
}

void Shader::SetUniform(GLuint uniID, GLuint value) {
	glUniform1ui(uniID, value);
}

void Shader::SetUniform(GLuint uniID,glm::mat4 value) {
	glUniformMatrix4fv(uniID,1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(GLuint uniID, GLfloat v1, GLfloat v2, GLfloat v3) {
	glUniform3f(uniID, v1, v2, v3);
}

void Shader::SetUniform(GLuint uniID, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4){
	glUniform4f(uniID, v1, v2, v3, v4);
}

void Shader::SetUniform(GLuint uniID, GLint value) {
	glUniform1i(uniID, value);
}



void Shader::Activate()
{
	glUseProgram(ID);
}


void Shader::Delete()
{
	glDeleteProgram(ID);
}

GLuint Shader::getID()
{
	return ID;
}

// Checks if the different Shaders have compiled properly
void Shader::compileError(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}