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
#include "../Vector3d.hpp"
#include "Shaders/Shader.hpp"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
    
}

struct LightLUM : public EntityLUM
{
    //light Attributes
    LightLUM();
    LightLUM(glm::vec3 pos, glm::vec3 color);
 
    glm::vec3 lightPos{0.0f,0.0f,0.0f};
    glm::vec3 lightColor{0.990f, 0.948f, 0.851f};
    float intensity{1.0f};

    void setlightColor(Vector3d& vequi);
        
    
    void      draw         (Shader &shader);
    std::string getPath();

   

};
