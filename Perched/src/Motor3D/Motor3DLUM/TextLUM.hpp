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

#include <iostream>
#include <map>
#include <string>

#include "../../glad/glad.h"
#include <GLFW/glfw3.h>

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>

#include "../Vector3d.hpp"
#include "Shaders/Shader.hpp"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

struct TextLUM {
    TextLUM();
    TextLUM(Shader &shader, unsigned int width, unsigned int height);

    void draw(const std::string& text, float x, float y, float scale, Vector3d color);

    unsigned int VAO, VBO;

    private:
        std::map<GLchar, Character> Characters;
        Shader *shader_ {nullptr};
};