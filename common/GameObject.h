#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "meshVertices.cpp"
#include "Texture.h"

// Ova klasa je ujedinjuje sva svojstva i funkcije jednog objekta koji se koristi u sceni.

class GameObject{

private:
    // OpenGL koristi Vertex buffer object kako bi zna kako izgleda neki objekt/model
    // Tipa GLuint je zato sto samo sprema mem. lokaciju na kojoj su upute kako izgleda taj objekt/model
    GLuint mVBO = 0;
    // Svaki objket moze imati neku svoju teksturu
	Texture mTexture;

	glm::mat4 mScale  = glm::mat4(1.0f);       // matrica za skaliranje
	glm::mat4 mRotate = glm::mat4(1.0f);       // matrica za rotiranje
	glm::mat4 mTranslate = glm::mat4(1.0f);    // matrica za translatiranje objekta
	glm::mat4 mModel = glm::mat4(1.0f);        // mModel matrica je umnozak gornjih 3 matrica
                                            // mModel se mnozi sa matricama View i Projection, koje su u klasi camera
                                            // a s ciljem tranlatiranja na odgovarajucu poziciju u sceni

    // broj vetrtexa ovog objekta. ova informacija mi je bitna za glDrawArrays() funkciju koja je ugradena glew funkcija.
    GLuint mNUM_VERTICES = 0;
//	bool isVolume = false;

public:
	GameObject();

    // Ovo su obicni setteri
	void setScale( float factor );
	void setRotate( glm::vec3 vector, float angle );
	void setTranslate( glm::vec3 vector );
	void setModel();
	void setTexture( Texture textureID );

    // ova funkcija zove puno glew funkcija kako bi se model crtao u sceni
	void draw();

    // a ovo su obicni getteri
	const GLfloat* getScale();
	const GLfloat* getRotate();
	const GLfloat* getTranslate();
	const GLfloat* getModelFLOAT();
	glm::mat4      getModelMAT();
	Texture getTexture();

    // ova funkcija prima skup tocaka/vertexa koje cine jedan objekt/model te ih posalje OpenGL-u. OpenGL sprema te 
    // informacije, a kao rezultat vraca memorijsku lokaciju gdje su spremljene te informacije. To se sprema u mVBO
    // s pocetka klase
	bool fillData(const GLfloat* vbo, const int vbo_size);
};
