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

#include "Vector3d.hpp"

Vector3d::Vector3d(){ x=0; y=0; z=0;  }

Vector3d::Vector3d(float nx, float ny, float nz){
    x = nx;
    y = ny;
    z = nz;
}

Vector3d::~Vector3d()
{

}

float Vector3d::getVectorX(){return x;}
float Vector3d::getVectorY(){return y;}
float Vector3d::getVectorZ(){return z;}

void Vector3d::setVectorX(float mx){ x = mx; }
void Vector3d::setVectorY(float my){ y = my; }
void Vector3d::setVectorZ(float mz){ z = mz; }