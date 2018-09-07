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
#include <vector>
#include <map>

#include "shaderLoader.h"
#include "textureLoader.h"
#include "Shader.h"
#include "Texture.h"

//    Model ourModel( "objects/nanosuit/nanosuit.obj" );

class ResourceManager{

    // Bit ove klase je da na jednom mjestu cuva sve vanjske graficke i tekstualne resurse, koji se u program loadaju
    // odmah na pocetku izvrsavanja. Zatim, kako i kada je potrebno se preko jednostavnih getter funkcija mogu poslati
    // na koristenje nekim drugim klasama. Uglavnom, kako ne bih iste teksture i shadere morao loadati vise puta nego
    // samo jednom.

private:
    // Mapa koja sprema neki loadani Shader pod imenom tipa const char*. Npr. ( Shader na adresi xyz : 'osnovniShader' )
    static std::map< const char*,  Shader > mShaderMap;
    // Ova mapa sprema samo 2D teksture, tj. teksture koje koriste objekti u sceni.
	static std::map< const char*,  Texture > m2DTextureMap;
    // Ova mapa je  samo za teksture koje se koriste u svrhu SkyBox. Razlika izmedu 2D i Skybox je da Skybox ima vise
    // tekstura i moraju se loadati specificnim redosljedom.
	static std::map< const char*,  Texture > mSkyboxTextureMap;
    // Ovdje se sprema const char* vrijednost koja mi govori u kojoj datoteci i pod kojim imenom se nalaze modeli za
    // objekte.
	static std::map< const char*,  const char* > mPathToModels;


//	bool checkIfLoaded( const char* ID );
public:
	ResourceManager();

    // Setters
    // Obicni setteri
	static bool addShader( const char* ID, const char* vertShader, const char* fragShader );
	static bool add2DTexture( const char* ID, const char* texturePath, const char* type = "texture_diffuse" );
    static bool addSkyboxTexture( const char* ID, std::vector<std::string> faces, const char* type = "texture_diffuse" );
	static bool addPathToModel( const char* ID, const char* path);
    
    // Getters
    // Obicni getteri
    static Shader getShader( const char* ID );
	static Texture get2DTexture( const char* ID );
	static Texture getSkyboxTexture( const char* ID );
	static const char* getPathToModel( const char* ID );

    // Listing methods - they list the contents of private std::map members
    // Ove metode koristim kako bih objektima zadao defaultne modele, a bez da znam gdje se ti modeli nalaze i kako se
    // zovu. Jednostavno uzmem prvi element koji mi vrati ova lista i to je to.
    static std::vector<const char*> listLoadedShaders();
    static std::vector<const char*> listLoaded2DTextures();
    static std::vector<const char*> listLoadedSkyboxTextures();
    static std::vector<const char*> listLoadedPathsToModels();
    
    // Ova funkcija ne radi nista, ali trebala bi po izlazu iz programa brisati sve spremljene shadere, teksture itd.
	static void cleanup();
};
