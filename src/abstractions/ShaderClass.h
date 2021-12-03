#pragma once
#include"../dependencies/glad.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


std::string get_file_contents(const char* filename);

class Shader
{
public:
	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);
	GLuint GetUniID(const char* name);

	void SetUniform(GLuint uniID, GLfloat value);
	void SetUniform(GLuint uniID, GLuint value);
	void SetUniform(GLuint uniID, GLint value);
	void SetUniform(GLuint uniID, glm::mat4 value);
	void SetUniform(GLuint uniID, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);
	void SetUniform(GLuint uniID, glm::vec4 vec4);
	void SetUniform(GLuint uniID, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniform(GLuint uniID, glm::vec3 vec3);


	void Activate();
	void Delete();

	GLuint getID();
private:
	void compileError(unsigned int shader, const char* type);
	GLuint ID;
};

