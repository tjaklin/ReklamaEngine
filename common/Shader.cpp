#include "Shader.h"

/*
Shader::Shader( const char* ID, const char* vertShader, const char* fragShader ){

//	Tu se loada ShaderProgram!
	mID = ID;
	mProgram = LoadShaders( vertShader , fragShader );
	if( mID == NULL || mProgram == 0 )
		std::cout << "Greska u Shader::Shader()." << ID << " " << vertShader << " " << fragShader << " " << std::endl;
}
*/

Shader::Shader(){
}

bool Shader::loadProgramHandler( GLuint program ){
	mProgramHandler = program;
}

void Shader::activate( ){
	glUseProgram( mProgramHandler );
}

void Shader::deactivate( ){
	glUseProgram( 0 );
}

void Shader::set1i( const char* variableID, uint variableData ){
	glUniform1i( glGetUniformLocation( mProgramHandler, variableID ), variableData );
}

void Shader::set1f( const char* variableID, float variableData ){
	glUniform1f( glGetUniformLocation( mProgramHandler, variableID ), variableData );
}

void Shader::set2f( const char* variableID, glm::vec2 variableData ){
	glUniform2f( glGetUniformLocation( mProgramHandler, variableID ), variableData.x, variableData.y );
}

void Shader::set2fv( const char* variableID, glm::vec2 variableData ){
	glUniform2fv( glGetUniformLocation( mProgramHandler, variableID ), 1, &variableData[0] );
}

void Shader::set3f( const char* variableID, glm::vec3 variableData ){
	glUniform3f( glGetUniformLocation( mProgramHandler, variableID ), variableData.x, variableData.y, variableData.z );
}

void Shader::set3fv( const char* variableID, glm::vec3 variableData ){
	glUniform3fv( glGetUniformLocation( mProgramHandler, variableID ), 1, &variableData[0] );
}

void Shader::setMatrix4fv( const char* variableID, glm::mat4 variableData ){
	glUniformMatrix4fv( glGetUniformLocation( mProgramHandler, variableID ), 1, GL_FALSE, &variableData[0][0] );
}

GLuint Shader::getProgram(){
    return mProgramHandler;
}
