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

#include "../ModelLUM.hpp"
#include "../LightLUM.hpp"
#include "../Sprite2D/SpriteRenderer.hpp"
#include "../ParticleSystem/ParticleSys.hpp"


#include <vector>
#include <map>
#include <memory>
#include <string>
#include <chrono>

struct ResourceManager
{
    ResourceManager() : cameras_{}, models_{}, lights_{}, sprites_{}, partSys_{}, texs2D_{}{/*std::cout << "CREO UN RESOURCE MANAGER\n";*/}
    ~ResourceManager();
    ModelLUM*  modelLoaded  (const std::string &);
    Texture2D* textureLoaded(const std::string &);

    std::vector<std::unique_ptr<CameraLUM>> cameras_;
    std::vector<std::unique_ptr<ModelLUM>>  models_;
    std::vector<std::unique_ptr<LightLUM>>  lights_;

    std::vector<std::unique_ptr<SpriteRenderer>> sprites_;
    std::vector<std::unique_ptr<ParticleSys>>    partSys_;  
    std::unordered_map<std::string, Texture2D>   texs2D_;
};