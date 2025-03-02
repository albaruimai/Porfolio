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
#include <vector>
#include "ModelLUM.hpp"
#include <string>
#include "Resources/TextureManager.hpp"

struct ModelLUM;

struct AnimationLUM{


    AnimationLUM(const std::string& path, int inicial, int distFrames, TextureManager * tm); //pasar path mas i (que sera el numero de fotograma)
    AnimationLUM() = default;
    
    std::vector<std::unique_ptr<ModelLUM>>frames_;
    int numFrames {0};

    std::string path {""};
    int frameIni {0};
    int distFrames {0};

    int getAnimationIni() { return animationIni; };
    int getAnimationFin() { return animationFin; };

    private:
        int animationIni {0};
        int animationFin {0};
        TextureManager * tm_;
};