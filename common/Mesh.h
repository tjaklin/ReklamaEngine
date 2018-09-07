#ifndef MESH_H
#define MESH_H

// Include GLEW
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

//using namespace std;

// Struktura koja opisuje od cega se sastoji vertex. Ovo je potrebno da si olaksamo situaciju prilikom lodanja modela
// preko ASSIMP. To loadanje se odvija u klasi Model.h
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

class Mesh {
public:
    // Vektor koji pamti sve vertexe potrebne za crtanje ovog mesha.
    std::vector<Vertex> vertices;
    // Indices se koristi kako bi se iskoristila OpenGL-ova tehnika glDrawElements, umjesto glDrawArray koju koristim
    // u klasi GameObject. Indices zapravo pamti redosljed vertexa prilikom crtanja modela, a sluzi samo kako bi se
    // proces crtanja malo ubrzao.

    std::vector<unsigned int> indices;
    unsigned int VAO;

    // Konstruktor prima sve potrebne informacije za inicijalizaciju Mesha objekta
    Mesh( std::vector<Vertex> vertices, std::vector<unsigned int> indices );

    // Crta koristeci parametar shader-a
    void Draw(Shader shader);
private:
    // VBO, kao i u GameObject klasi, sprema informacije o vertexima.
    // EBO se koristi zajedno s indices i funkcijom glDrawElements, pamti redosljed indices.
    unsigned int VBO, EBO;

    // loada sve podatke, a mem. lokacija na kojima su spremljeni vraca u VBO, EBO i VAO
    void setupMesh();
};
#endif
