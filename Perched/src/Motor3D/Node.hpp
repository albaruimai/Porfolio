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

#include "Vector3d.hpp"
#include <string>
#include "Motor3DLUM/EntityLUM.hpp"
#include "Motor3DLUM/CameraLUM.hpp"
class Node
{

public:

    virtual void remove() = 0;
    virtual float getX() = 0;
    virtual float getY() = 0;
    virtual float getZ() = 0;
    virtual void setID(int) = 0;
    virtual int getNodeID() = 0;
    virtual int getSize() = 0;
    virtual Vector3d getPosition() = 0;
    virtual void setPosition(Vector3d) = 0;
    virtual void setTarget(Vector3d) = 0;
    virtual Vector3d getTarget() = 0;
    virtual EntityLUM* getEntity() = 0;
    virtual bool setEntity(EntityLUM*) = 0;
    virtual void setAnimation(std::string path, int inicial) = 0;
    virtual std::string getAnimation() = 0;
    virtual void ActualizarFrame(int dura) = 0;
    virtual void ActualizarAnimation(std::string const & nomAnim) = 0;
    virtual int getActualFrame() = 0;
    virtual int getFinalFrame() = 0;
    virtual void setsegundoshader(bool) = 0;
    virtual bool getsegundoshader() = 0;
    virtual void ResetFrame() = 0;
    // Setters for initial traslation, rotation and scale
    virtual void setTranslation      (Vector3d) = 0;
    virtual void setRotation         (Vector3d) = 0;
    virtual void setScale            (Vector3d) = 0;
    // Traslate, rotate and sclae modifiers
    virtual void translate           (Vector3d) = 0;
    virtual void scale               (Vector3d) = 0;
    virtual void rotate              (Vector3d) = 0;
    // Getters
    virtual Vector3d  getTranslation () = 0;
    virtual Vector3d  getRotation    () = 0;
    virtual Vector3d  getScale       () = 0;
    virtual Node*     getCamera      () = 0;
    virtual float     getAlpha       () = 0;
    virtual void      setAlpha       (float) = 0;
    virtual void      setNodeShader  (int) = 0;
};
