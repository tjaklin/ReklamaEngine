#include "ResourceManager.h"

// Instantiate static variables
std::map< const char*, Shader> ResourceManager::mShaderMap;
std::map< const char*, Texture> ResourceManager::m2DTextureMap;
std::map< const char*,  Texture > ResourceManager::mSkyboxTextureMap;
std::map< const char*,  const char* > ResourceManager::mPathToModels;


ResourceManager::ResourceManager(){

}

/*
bool ResourceManager::checkIfLoaded( const char* ID ){

	auto result = mShaderMap.find( ID );
	if( result != mShaderMap.end() )
	{
		if( result->first == ID )
		{
			return true;
		}
	return false;
	}
}
*/
//////// Setters
bool ResourceManager::addShader( const char* ID, const char* vertShader, const char* fragShader ){

	Shader newShaderObject;

    // Loada shader u novostvoreni Shader objekt. Parametar metode loadProgramHandler je memorijska lokacija
    // loadanog shadera.
    
	newShaderObject.loadProgramHandler( LoadShaders( vertShader , fragShader ) );

    // novostvoreni Shader objekt koji je popunjen podacima sprema u svoju mapu
	mShaderMap[ ID ] = newShaderObject;
    // bool je da utvrdim je li uspio s loadanjem Shadera
    return true;
}
bool ResourceManager::add2DTexture( const char* ID, const char* texturePath, const char* type ){

	Texture newTextureObject;

    // Ova funkcaja radi isto sta i addShader
    
	newTextureObject.loadTextureHandler( TextureLoader::loadBMP_2D( texturePath ) );
    // Ovdje se dodjeljuje tip teksture, koji je obican string. Kasnije se na temelju tipova razlikuju teksture.
    newTextureObject.setType( type );
    
	m2DTextureMap[ ID ] = newTextureObject;
	return true;
}
bool ResourceManager::addSkyboxTexture( const char* ID, std::vector<std::string> faces, const char* type ){

	Texture newTextureObject;

    // Slican proces loadanja, ali ovo je za SkyBox, koji prima 6 tekstura. Zato je parametar faces tipa vektor.
    // On sadrzi 6 putanja do tekstura
	newTextureObject.loadTextureHandler( TextureLoader::loadCubemap( faces ) );
    newTextureObject.setType( type );

	mSkyboxTextureMap[ ID ] = newTextureObject;
	return true;
}
bool ResourceManager::addPathToModel( const char* ID, const char* path){
    // Sprema putanju do .obj ( ili neki drugi format ) modela
    mPathToModels[ ID ] = path;
}

/////////// Getters
// Obicne getter funkcije
Shader ResourceManager::getShader( const char* ID ){
	return mShaderMap[ ID ];
}
Texture ResourceManager::get2DTexture( const char* ID ){
	return m2DTextureMap[ ID ];
}
Texture ResourceManager::getSkyboxTexture( const char* ID ){
	return mSkyboxTextureMap[ ID ];
}
const char* ResourceManager::getPathToModel( const char* ID ){
    return mPathToModels[ ID ];
}

//////////// Listing methods
// Funckije koje izlistaju sadrzaje mapa...
std::vector<const char*> ResourceManager::listLoadedShaders(){ 
    std::vector <const char*> result;
    for( auto const& [ id , value ] : mShaderMap )
    {
        result.push_back( id );
    }
return result;
}
std::vector<const char*> ResourceManager::listLoaded2DTextures(){
    std::vector <const char*> result;
    for( auto const& [ id , value ] : m2DTextureMap )
    {
        result.push_back( id );
    }
return result;    
}
std::vector<const char*> ResourceManager::listLoadedSkyboxTextures(){
    std::vector <const char*> result;
    for( auto const& [ id , value ] : mSkyboxTextureMap )
    {
        result.push_back( id );
    }
return result;    
}
std::vector<const char*> ResourceManager::listLoadedPathsToModels(){
    std::vector <const char*> result;
    for( auto const& [ id , value ] : mPathToModels )
    {
        result.push_back( id );
    }
return result;    
}

void ResourceManager::cleanup(){
// OVO MORAM POGLEDATI!!
/*
	for( auto const& x : mTextureMap )
		glDeleteTextures( 1, &x.second.getTexture() );
	for( auto const& x : mShaderMap )
		glDeleteProgram( x.second.getProgram() );
*/
}
