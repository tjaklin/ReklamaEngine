#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

class Texture{

    // Klasa koja ujedinjuje sva bitna svojstva teksture te funkcije za manipulaciju istom.
    
private:
    
    // Sprema memorijsku lokaciju na kojoj je loadana tekstura
    
	GLuint mTextureHandler;

    // Tip teksture zadajem sa stringom. Kasnije u kodu se određuje koje teksture se loadaju s obzirom na
    // njihov tip
    std::string mType = "";
    // Ovdje spremam put do teksture
    std::string mPath = "";

public:
	// set Constructor
//	Texture( const char* ID, const char* texturePath );
	Texture();

    // Parametar je memorijska lokacija teksture koju spremam u mTextureHandler. Ne znam zasto je bool jer ne vraca
    // nista.
    bool loadTextureHandler( GLuint texture );

    // obicne setter funkcije
    void setType( std::string type );
	void setPath( std::string path );

    // obicne getter funkcije
    // ova funkcija vraca mTextureHandler
	GLuint getTexture();
    std::string getType();
	std::string getPath();
};

#endif
