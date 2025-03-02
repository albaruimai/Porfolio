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

#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(
    Texture2D* texture,
    glm::vec2 position, 
    glm::vec2 size, 
    float rotate, 
    glm::vec3 color
) :
    position_{position},
    size_{size},
    rotate_{rotate},
    color_{color},
    texture_{texture}
{
    this->initRenderData();
}
SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO_);
}
void SpriteRenderer::DrawSprite(Shader &s)
{
    // prepare transformations
    s.use();
    glm::mat4 model {1.0f};
    model = glm::translate(model, glm::vec3(position_, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
    model = glm::translate(model, glm::vec3(0.5f * size_.x, 0.5f * size_.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate_), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size_.x, -0.5f * size_.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size_, 1.0f)); // last scale
    s.setMat4("model", model);

    // render textured quad
    s.setVec3("spriteColor", color_);

    glActiveTexture(GL_TEXTURE0);
    texture_->Bind();

    glBindVertexArray(quadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO_);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/*GETTERS*/
const uint32_t  & SpriteRenderer::getQuadVAO()    {return quadVAO_;}
const Texture2D * SpriteRenderer::getTexture()    {return texture_;}
const glm::vec2 & SpriteRenderer::getPosition()   {return position_;}
const glm::vec2 & SpriteRenderer::getSize()       {return size_;}
const float     & SpriteRenderer::getRotate()     {return rotate_;} 
const glm::vec3 & SpriteRenderer::getColor()      {return color_;}
const float     & SpriteRenderer::getAlpha()      {return alpha_;}
glm::vec2         SpriteRenderer::getWindowSize() {return window_;}
/*SETTERS*/
void SpriteRenderer::setQuadVAO    (uint32_t uint)   {quadVAO_=uint;}
void SpriteRenderer::setTexture    (Texture2D * tex) {texture_=tex;}
void SpriteRenderer::setPosition   (glm::vec2 p)     {position_=p;}
void SpriteRenderer::setSize       (glm::vec2 s)     {size_=s;}
void SpriteRenderer::setRotate     (float r)         {rotate_=r;}
void SpriteRenderer::setColor      (glm::vec3 c)     {color_=c;}
void SpriteRenderer::setAlpha      (float a)         {alpha_=a;}
void SpriteRenderer::setWindowSize (glm::vec2 w)     {window_=w;}