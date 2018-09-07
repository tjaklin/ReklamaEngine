#include "GameObject.h"

GameObject::GameObject(){

}

bool GameObject::fillData(const GLfloat* vbo, const int vbo_size)
{
	if( !vbo )
		return false;

    // Prima informacije o tockama koje cine ovaj objekt te ih salje OpenGL-u
    // mem. lokaciju tih informacija sprema u mVBO
    
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vbo_size, vbo, GL_STATIC_DRAW);

	mNUM_VERTICES = vbo_size/32;

glBindBuffer(GL_ARRAY_BUFFER, 0);

if(mVBO == 0)
	return false;
return true;
}
// Setter funkcije
void GameObject::setScale( float factor ){
	mScale     = glm::scale( glm::mat4(1.0f), glm::vec3(factor) );
}
void GameObject::setRotate( glm::vec3 vector, float angle ){
	mRotate    = glm::rotate( glm::mat4(1.0f), angle, vector);
}
void GameObject::setTranslate( glm::vec3 vector ){
	mTranslate = glm::translate( glm::mat4(1.0f), vector);
}
void GameObject::setModel(){
	mModel = mTranslate * mRotate * mScale;
}
void GameObject::setTexture( Texture textureID ){
	mTexture = textureID;
}
void GameObject::draw(){

    // Ova funkcija koristi mVBO informacije kako bi se nacrtao objekt u sceni
    
	glBindBuffer( GL_ARRAY_BUFFER, mVBO );
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0 );

	// 2nd attribute buffer : Normalss
	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*) (3*sizeof(GLfloat)) );

	// 3rd attribute buffer : UVs
	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*) (6*sizeof(GLfloat)) );

	// Draw the triangle !
	glDrawArrays( GL_TRIANGLES, 0, mNUM_VERTICES );

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );
}

const GLfloat* GameObject::getScale() { return &mScale[0][0]; }
const GLfloat* GameObject::getRotate() { return &mRotate[0][0]; }
const GLfloat* GameObject::getTranslate() { return &mTranslate[0][0]; }
const GLfloat* GameObject::getModelFLOAT() { return &mModel[0][0]; }
glm::mat4 GameObject::getModelMAT() { return mModel; }
Texture GameObject::getTexture() { return mTexture; }
