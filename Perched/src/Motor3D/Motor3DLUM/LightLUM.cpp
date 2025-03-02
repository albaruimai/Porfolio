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

#include "Motor3DLUM.hpp"
#include "LightLUM.hpp"

LightLUM::LightLUM(glm::vec3 pos, glm::vec3 color){
    
    lightPos = pos;
    lightColor = color;

}


void LightLUM::draw (Shader &shader){


}
std::string LightLUM::getPath()
{
    return "no path for a light\n";
}

 void LightLUM::setlightColor(Vector3d& vequi){

     this->lightColor={vequi.getVectorX(),
                        vequi.getVectorY(),
                        vequi.getVectorZ()};
 }