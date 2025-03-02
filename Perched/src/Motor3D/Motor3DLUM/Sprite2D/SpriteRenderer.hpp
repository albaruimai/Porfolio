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

#include "../Shaders/Shader.hpp"
#include "Texture2D.hpp"
#include "../../../stb/stb_image.h"

struct SpriteRenderer
{
    void DrawSprite(Shader &shader);

    /*GETTERS*/
    const uint32_t  & getQuadVAO();
    const Texture2D * getTexture();
    const glm::vec2 & getPosition();
    const glm::vec2 & getSize();
    const float     & getRotate(); 
    const glm::vec3 & getColor();
    const float     & getAlpha();
    glm::vec2         getWindowSize();

    /*SETTERS*/
    void setQuadVAO    (uint32_t);
    void setTexture    (Texture2D*);
    void setPosition   (glm::vec2);
    void setSize       (glm::vec2);
    void setRotate     (float); 
    void setColor      (glm::vec3);
    void setAlpha      (float);
    void setWindowSize (glm::vec2);

    SpriteRenderer(Texture2D* texture, glm::vec2 position, 
        glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, 
        glm::vec3 color = glm::vec3(1.0f));
    ~SpriteRenderer();
            
private:
    uint32_t  quadVAO_;
    Texture2D* texture_;
    glm::vec2 position_;
    glm::vec2 size_ {10.0f, 10.0f};
    float rotate_ { 0.0f}; 
    glm::vec3 color_ {1.0f};
    float alpha_{1.0f};
    glm::vec2 window_{1280,720};
    void initRenderData();
};