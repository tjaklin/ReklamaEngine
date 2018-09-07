#include "Texture.h"

/*
Texture::Texture( const char* ID, const char* texturePath ){

//	Tu se loada Texture!
	if( ID && texturePath )
	{
		mID = ID;
		mTexture = loadBMP_custom( texturePath );
	}
	else
		std::cout << "Greska u Texture::Texture()." << ID << " " << texturePath << std::endl;
}
*/

Texture::Texture(){

}

bool Texture::loadTextureHandler( GLuint texture ){
	mTextureHandler = texture;
}

void Texture::setType( std::string type ){
    mType = type;
}

void Texture::setPath( std::string path ){
    mPath = path;
}

GLuint Texture::getTexture()
{
return mTextureHandler;
}

std::string Texture::getType()
{
return mType;
}

std::string Texture::getPath()
{
return mPath;
}
