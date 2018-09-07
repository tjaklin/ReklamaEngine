#include "Model.h"

void Model::Draw(Shader shader)
{
    // prolazi kroz sve Mesheve i crta ih
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}


void Model::loadModel(std::string const &path)
{
    // Svaki put kada loada novi model mora izbrisati stare mesheve
    meshes.clear();

    // Koristeci Assimp loada datoteku koja opisuje model
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // Ukoliko je doslo do gresaka 
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}
    
void Model::processNode(aiNode *node, const aiScene *scene)
{
    // Prolazak kroz svaki mesh u node-u
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // nakon ovog nodea, zovemo novu instancu ove iste funkcije u kojoj rekurzivno procesuiramo node-dijete.
    // i tako proilazimo kroz sve cvorove
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // Ovdje ce se spremiti sve tocke nekog mesha
    std::vector<Vertex> vertices;
    // Indices se koristi kako bi se jednostavnije crtao neki niz vertexa. Ovo je tehnika iz OpenGL,
    // a jedina prednost koristenja je dobivanje na brzini.
    std::vector<unsigned int> indices;

    // Prolazi se tocka po tocka u svakom meshu
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        // Ovdje spremamo pozicije
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        // Ovdje spremamo normale, kako bi znali racunati osvjetljenje
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        // Takoder spremamo i tangente
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;

        // Te bitangente
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }

    // Za svako lice nekog mesha
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // ovdje popunjavamo indices vektor. Ponovo, ovo se radi samo kako bi se kasnije dobilo na brzini prilikom
        // crtanja objekta. Nije nista bitno za sam program.
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    return Mesh( vertices, indices );
}    

////////////////////////////////////////////////
// SETTERS AND GETTERS
void Model::setScale( float factor ){
    mScaleFactor = factor;
	mScale     = glm::scale( glm::mat4(1.0f), glm::vec3(factor) );
}
void Model::setRotate( glm::vec3 vector, float angle ){
    mRotateVector = vector; mRotateAngle = angle;
    mRotate    = glm::rotate( glm::mat4(1.0f), angle, vector);
}
void Model::setTranslate( glm::vec3 vector ){
    mTranslateVector = vector;
    mTranslate = glm::translate( glm::mat4(1.0f), vector);
}
void Model::setModel(){
	mModel = mTranslate * mRotate * mScale;
}

void Model::updateObjectData(){
    setScale( mScaleFactor );
    setRotate( mRotateVector, mRotateAngle );
    setTranslate( mTranslateVector );
    setModel();
}

const GLfloat* Model::getScale() { return &mScale[0][0]; }
const GLfloat* Model::getRotate() { return &mRotate[0][0]; }
const GLfloat* Model::getTranslate() { return &mTranslate[0][0]; }
const GLfloat* Model::getModelFLOAT() { return &mModel[0][0]; }
glm::mat4 Model::getModelMAT() { return mModel; }
    // By Reference
float& Model::getScaleFactorRef() { return mScaleFactor; }
glm::vec3& Model::getRotateVectorRef() { return mRotateVector; }
float& Model::getRotateAngleRef() { return mRotateAngle; }
glm::vec3& Model::getTranslateVectorRef() { return mTranslateVector; }
