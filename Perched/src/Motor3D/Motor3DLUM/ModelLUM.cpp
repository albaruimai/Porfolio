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

#include "ModelLUM.hpp"

#define  STB_IMAGE_IMPLEMENTATION
#include "../../stb/stb_image.h"

// model data 
// constructor, expects a filepath to a 3D model.
ModelLUM::ModelLUM(){

}

ModelLUM::ModelLUM(const std::string& path, bool gamma, TextureManager * tm) : gammaCorrection {gamma}, tm_{tm}
{
    loadModel(path);
}
ModelLUM::~ModelLUM()
{
    for (size_t i {0}; i < static_cast<size_t>(textures_loaded.size()); ++i)
    {
        glDeleteTextures(1,&textures_loaded[i].id);
    }
    for (size_t i {0}; i < static_cast<size_t>(meshes.size()); ++i)
    {
        glDeleteVertexArrays(1,&meshes[i].VAO);
    }
}
// draws the model, and thus all its meshes
void ModelLUM::draw(Shader &shader)
{
    for(uint32_t i {}; i < static_cast<uint32_t>(meshes.size()); ++i)
    {
        meshes[i].draw(shader);
    }
}
// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void ModelLUM::loadModel(const std::string& path)
{
    path_ = path;
    // read file via ASSIMP
    Assimp::Importer importer;
    
    const aiScene* scene { importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace) };
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        //std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));
    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);   
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void ModelLUM::processNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(unsigned int i {0}; i < node->mNumMeshes; ++i)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh { scene->mMeshes[node->mMeshes[i]] };
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i {0}; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
    
}

MeshLUM ModelLUM::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // walk through each of the mesh's vertices
    for(unsigned int i {0}; i < mesh->mNumVertices; ++i)
    {
        VertexLUM vertex;
        glm::vec3 vector {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z}; 
        // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions

        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).

            vertex.TexCoords = glm::vec2 (mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i {0}; i < mesh->mNumFaces; ++i)
    {
        aiFace face { mesh->mFaces[i] };
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j {0}; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);        
    }
    // process materials
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.

    determineAdjacency(indices);
    
    aiMaterial* material { scene->mMaterials[mesh->mMaterialIndex] };    
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // 2. specular maps
    specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // 3. normal maps
    normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. height maps
    heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    // return a mesh object created from the extracted mesh data
    return MeshLUM(vertices, indices, textures);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<TextureLUM> ModelLUM::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName)
{
    std::vector<TextureLUM> textures;
    for(size_t i {0}; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip { false };
        for(size_t j {0}; j < static_cast<size_t>(textures_loaded.size()); ++j)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            TextureLUM texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory, false);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int ModelLUM::TextureFromFile(const char *path, const std::string& directory, bool gamma)
{
    std::string filename {directory + '/' + std::string(path)};
    uint32_t textureID;
    if (tm_->texs3D_.find(path) != tm_->texs3D_.end())
    {
        textureID = tm_->texs3D_[path].id;
        return textureID;
    }
    
    int width, height, nrComponents;
    auto data {stbi_load(filename.c_str(), &width, &height, &nrComponents, 0)};
    
    if (data)
    {
        glGenTextures(1, &textureID);
        GLenum format;

        switch (nrComponents) {
            case 1:
                format = GL_RED;
                break;
            
            case 3:
                format = GL_RGB;
                break;

            case 4:
                format = GL_RGBA;
                break;

            default:
                format = GL_RGBA;
                break;
        }            
       
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        //std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    
    tex.id = textureID;
    tex.path = path;
    tex.type = "";
    tm_->texs3D_.insert({path, tex});
    
    //std::cout << "Size of texture array: " << tm_->texs3D_.size() << "\n";
    using TextIt = std::unordered_map<std::string, TextureLUM>::iterator;
    for (TextIt it { tm_->texs3D_.begin() }; it != tm_->texs3D_.end(); ++it)
    {
        //std::cout << "--Textura cargada: " << it->first << "\n";
    }
    return textureID;
}
std::string ModelLUM::getPath()
{
    return path_;
}

void ModelLUM::determineAdjacency(std::vector<unsigned int> &el)
{
    // Copy and make room for adjacency info
    for (GLuint i {0}; i < static_cast<GLuint>(el.size()); i += 3)
    {
        elAdj.push_back(el[i]);
        elAdj.push_back(-1);
        elAdj.push_back(el[i + 1]);
        elAdj.push_back(-1);
        elAdj.push_back(el[i + 2]);
        elAdj.push_back(-1);
    }

    // Find matching edges
    for (GLuint i {0}; i < static_cast<GLuint>(elAdj.size()); i += 6)
    {
        // A triangle
        int a1 { static_cast<int>(elAdj[i]) };
        int b1 { static_cast<int>(elAdj[i + 2]) };
        int c1 { static_cast<int>(elAdj[i + 4]) };

        // Scan subsequent triangles
        for (GLuint j { i + 6 }; j < static_cast<GLuint>(elAdj.size()); j += 6)
        {
            int a2 { static_cast<int>(elAdj[j]) };
            int b2 { static_cast<int>(elAdj[j + 2]) };
            int c2 { static_cast<int>(elAdj[j + 4]) };

            // Edge 1 == Edge 1
            if ((a1 == a2 && b1 == b2) || (a1 == b2 && b1 == a2))
            {
                elAdj[i + 1] = c2;
                elAdj[j + 1] = c1;
            }
            // Edge 1 == Edge 2
            if ((a1 == b2 && b1 == c2) || (a1 == c2 && b1 == b2))
            {
                elAdj[i + 1] = a2;
                elAdj[j + 3] = c1;
            }
            // Edge 1 == Edge 3
            if ((a1 == c2 && b1 == a2) || (a1 == a2 && b1 == c2))
            {
                elAdj[i + 1] = b2;
                elAdj[j + 5] = c1;
            }
            // Edge 2 == Edge 1
            if ((b1 == a2 && c1 == b2) || (b1 == b2 && c1 == a2))
            {
                elAdj[i + 3] = c2;
                elAdj[j + 1] = a1;
            }
            // Edge 2 == Edge 2
            if ((b1 == b2 && c1 == c2) || (b1 == c2 && c1 == b2))
            {
                elAdj[i + 3] = a2;
                elAdj[j + 3] = a1;
            }
            // Edge 2 == Edge 3
            if ((b1 == c2 && c1 == a2) || (b1 == a2 && c1 == c2))
            {
                elAdj[i + 3] = b2;
                elAdj[j + 5] = a1;
            }
            // Edge 3 == Edge 1
            if ((c1 == a2 && a1 == b2) || (c1 == b2 && a1 == a2))
            {
                elAdj[i + 5] = c2;
                elAdj[j + 1] = b1;
            }
            // Edge 3 == Edge 2
            if ((c1 == b2 && a1 == c2) || (c1 == c2 && a1 == b2))
            {
                elAdj[i + 5] = a2;
                elAdj[j + 3] = b1;
            }
            // Edge 3 == Edge 3
            if ((c1 == c2 && a1 == a2) || (c1 == a2 && a1 == c2))
            {
                elAdj[i + 5] = b2;
                elAdj[j + 5] = b1;
            }
        }
    }

    // Look for any outside edges
    for (GLuint i {0}; i < static_cast<GLuint>(elAdj.size()); i += 6)
    {
        if (elAdj[i + 1] == -1) elAdj[i + 1] = elAdj[i + 4];
        if (elAdj[i + 3] == -1) elAdj[i + 3] = elAdj[i];
        if (elAdj[i + 5] == -1) elAdj[i + 5] = elAdj[i + 2];
    }

    // Copy all data back into el
    el = elAdj;
}

