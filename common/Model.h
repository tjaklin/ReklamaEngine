#ifndef MODEL_H
#define MODEL_H

// Include GLEW
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// Ovo je najbitnija klasa u cijelom programu zato sto omogucuje loadanje modela razlicitih formata,
// a sve na jednostavan nacin. Za loadanje samih modela koristi se nekoliko klasa iz knjiznice ASSIMP!

class Model 
{
private:
    /* Model Data */
    glm::mat4 mScale  = glm::mat4(1.0f);
	glm::mat4 mRotate = glm::mat4(1.0f);
	glm::mat4 mTranslate = glm::mat4(1.0f);
	glm::mat4 mModel = glm::mat4(1.0f);
        // Manje bitni podaci
        float mScaleFactor = 1.0f;
        glm::vec3 mRotateVector = glm::vec3( 0.0f, 1.0f, 0.0f );
        float mRotateAngle = 10.0f;
        glm::vec3 mTranslateVector = glm::vec3( 0.0f );

        
    void processNode(aiNode *node, const aiScene *scene);
    
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

public:
    Model(std::string const &path )
    {
        // Prima putanju do modela, tj datoteke koja ga sadrzi.
        loadModel( path );
    }

    std::vector<Mesh> meshes;
    std::string directory;


    void loadModel(std::string const &path);

    // Setter funkcije
    void setScale( float factor );
	void setRotate( glm::vec3 vector, float angle );
	void setTranslate( glm::vec3 vector );
	void setModel();
    void updateObjectData();

    // getter funkcije
    const GLfloat* getScale();
	const GLfloat* getRotate();
	const GLfloat* getTranslate();
	const GLfloat* getModelFLOAT();
	glm::mat4      getModelMAT();
    
    float& getScaleFactorRef();
    glm::vec3& getRotateVectorRef();
    float& getRotateAngleRef();
    glm::vec3& getTranslateVectorRef();
    
    void Draw(Shader shader);   // Crta model, Kao parametar prima Shader koji ce koristiti

};

#endif

