#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <iostream>
// ShaderProgram ima svoje jedinstvene UNIFORM varijable koje mora primiti da bi ispravno funkcionirao.
// ShaderProgram moze imati razlicite shadere koje kompajlira. Npr. moze i ne mora imati geometry shader...


// Klasa koja ujedinjuje sva svojstva i funkcije za manipulaciju shaderima.

class Shader{

private:
    // Ova varijabla mi cuva memorijsku lokaciju na kojoj je loadan sam shader.
    GLuint mProgramHandler;
//	const char* mID;

public:
	// set Constructor
//	Shader( const char* ID, const char* vertShader, const char* fragShader );
    // Koristim prazan konstruktor
    Shader();

    
	bool loadProgramHandler( GLuint program );     // Funkcija koja prima memorijsku lokaciju shadera kao parametar
                                                   // pa tu memorijsku lokaciju sprema u mProgramHandler
	void activate();       // Aktivira shader koristeci funkciju knjiznice glew
	void deactivate();     // Deativira shader koristeci funkciju knjiznice glew

	// set ShaderProgram's variables!
    // Ove funkcije koriste funkcije knjiznice glew kako bi podatke koje prime kao parametre poslali svom shaderu

    void set1i( const char* variableID, uint variableData );
//   glUniform1f(glGetUniformLocation(shader_lightingID, "shadowMap"), offset);
	void set1f( const char* variableID, float variableData );

//   glUniform2f( glGetUniformLocation(shader_blurID,"ScaleU") , 1.0/(WINDOW_WIDTH * 0.5 * 0.25), 0.0);
	void set2f( const char* variableID, glm::vec2 variableData );
//   glUniform2fv( glGetUniformLocation(shader_blurID,"ScaleU"), 1, &pos[0] );
	void set2fv( const char* variableID, glm::vec2 variableData );

//   glUniform3f(glGetUniformLocation(shader_lightingID, "lightDir"), lightDir.x, lightDir.y, lightDir.z);
	void set3f( const char* variableID, glm::vec3 variableData );
//   glUniform3fv(glGetUniformLocation(shader_lightingID, "pLight.position"), 1, &pos[0]);
	void set3fv( const char* variableID, glm::vec3 variableData );

//   glUniformMatrix4fv(glGetUniformLocation(shader_lightingID, "model"), 1, GL_FALSE, &Model[0][0]);
	void setMatrix4fv( const char* variableID, glm::mat4 variableData );

// NAPOMENA: Mozda da dodam getMatrix4fv() tipa funkcije koje mi naprave cout trenutno loadanog stanja!
    // ova funkcija vraca mProgramHandler
    GLuint getProgram();
};

#endif
