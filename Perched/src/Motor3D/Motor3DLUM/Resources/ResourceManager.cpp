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

#include "ResourceManager.hpp"

ModelLUM* ResourceManager::modelLoaded(const std::string & path)
{
    //auto start {std::chrono::system_clock::now()};
    for (size_t i {0}; i < static_cast<size_t>(models_.size()); ++i)
    {
        if (models_[i]->getPath() == path)
        {
            return models_[i].get(); 
        } 
    }
    auto end {std::chrono::system_clock::now()};
    //std::chrono::duration<float,std::milli> duration = end - start;
    //std::cout << "COMPROBACION SI EL MODELO ESTA CARGADO: " << duration.count() <<" ms\n";
    return nullptr;
}

ResourceManager::~ResourceManager()
{
    for (size_t i {0}; i < static_cast<size_t>(models_.size()); ++i)
    {
        for (size_t j {0}; j < static_cast<size_t>(models_[i].get()->textures_loaded.size()); ++j)
        {
            glDeleteTextures(1, &models_[i].get()->textures_loaded[j].id);
        }
    }
    //models_.clear();
    //lights_.clear();
    //cameras_.clear();
}

Texture2D* ResourceManager::textureLoaded(const std::string & key)
{
    if (texs2D_.find(key) != texs2D_.end())
    {
        return &texs2D_[key];
    }
    return nullptr;
}