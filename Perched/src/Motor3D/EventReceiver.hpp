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
#include "Motor3D.hpp"
#include "../util/MyKeycodes.h"
#define KEYBOARD_KEYS 50

struct EventReceiver
{
    EventReceiver(GLFWwindow* w)
    {
        window = w;
    }
    EventReceiver(){}

    bool IsKeyDown(keys::KEY_CODE_G keyCode)
    {
        if ((glfwGetKey(window, keyCode) == GLFW_PRESS))
            return true;
        return false;
    }
private:
    GLFWwindow* window;
};