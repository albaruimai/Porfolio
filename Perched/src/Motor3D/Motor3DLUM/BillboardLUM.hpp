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

#include "../Vector3d.hpp"
#include "ModelLUM.hpp"
#include "TextureLUM.hpp"
#include "../../stb/stb_image.h"

struct BillboardLUM {

    BillboardLUM(const std::string& path, glm::vec3 position, glm::vec3 size, glm::vec3 normal);
    BillboardLUM();

    void draw (Shader &shader);
    std::string getPath();

    private:
        glm::vec3   b_position_ {};
        glm::vec3   b_scale_    {};
        glm::vec3   b_normal_   {};
        std::string b_path_     {};

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[32] {
             // positions         // colors           // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };

        /* Indices to not repeat vertexes */
        unsigned int indices[6] {
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        float borderColor[4] {1.0f, 1.0f, 0.0f, 1.0f};
};