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
#include <unordered_map>
#include <memory>
#include <string>
#include <chrono>
#include "../TextureLUM.hpp"


struct TextureManager
{
    std::unordered_map<std::string, TextureLUM> texs3D_{};
    TextureManager(){/*std::cout << "CREO UN TEXTURE MANAGER\n";*/}
};