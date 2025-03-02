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

class Vector3d
{
private:
    float x, y, z;
public:
    Vector3d();
    Vector3d(float x, float y, float z);
    ~Vector3d();

    float getVectorX();
    float getVectorY();
    float getVectorZ();
    void setVectorX(float mx);
    void setVectorY(float my);
    void setVectorZ(float mz);
};

