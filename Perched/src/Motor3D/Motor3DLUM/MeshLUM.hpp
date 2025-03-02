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

#include "NodeLUM.hpp"
#include "Shaders/Shader.hpp"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "TextureLUM.hpp"
#include "VertexLUM.hpp"
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}

#include <iostream>
#include <vector>

struct MeshLUM {
    // mesh Data
    std::vector<VertexLUM>   vertices;
    std::vector<uint32_t>    indices;
    std::vector<TextureLUM>  textures;
    uint32_t VAO;

    // constructor
    MeshLUM(std::vector<VertexLUM> vertices, std::vector<uint32_t> indices, std::vector<TextureLUM> textures);
    ~MeshLUM();

    // render the mesh
    void draw(Shader &shader);
   

    private:
        // render data 
        uint32_t VBO, EBO;
        // initializes all the buffer objects/arrays
        void setupMesh();

        // bind appropriate textures
        unsigned int diffuseNr  {1};
        unsigned int specularNr {1};
        unsigned int normalNr   {1};
        unsigned int heightNr   {1};

        // retrieve texture number (the N in diffuse_textureN)
        std::string number {""};
        std::string name {""};
};

