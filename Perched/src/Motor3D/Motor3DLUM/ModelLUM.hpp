//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include "EntityLUM.hpp"
#include "MeshLUM.hpp"
#include "TextureLUM.hpp"
#include "VertexLUM.hpp"
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Shaders/Shader.hpp"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Resources/TextureManager.hpp"

struct MeshLUM;

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


struct ModelLUM : public EntityLUM
{
   
    public:
    // model data 
    std::vector<TextureLUM> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<MeshLUM>    meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    ModelLUM();
    ModelLUM(const std::string& path, bool gamma, TextureManager * tm);
    ~ModelLUM();
    // draws the model, and thus all its meshes
    void draw(Shader &shader);
    std::string getPath();
   
private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(const std::string& path);
    
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);
    MeshLUM processMesh(aiMesh *mesh, const aiScene *scene);
    unsigned int TextureFromFile(const char *path, const std::string& directory, bool gamma);
    std::vector<TextureLUM> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    std::string path_ {""};
    void determineAdjacency(std::vector<unsigned int> &el);

    // data to fill
    std::vector<VertexLUM> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureLUM> textures;

    std::vector<TextureLUM> diffuseMaps {};
    std::vector<TextureLUM> specularMaps {};
    std::vector<TextureLUM> normalMaps {};
    std::vector<TextureLUM> heightMaps {};

    TextureLUM tex {};
    TextureManager * tm_;

    // Elements with adjacency info
	std::vector<unsigned int> elAdj {};
};

