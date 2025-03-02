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

#include "AnimationLUM.hpp"
#include <filesystem>
#include <iostream>

AnimationLUM::AnimationLUM(const std::string& path, int inicial, int distFrames, TextureManager * tm) : tm_{tm}{
    this->path = path;
    this->frameIni = inicial;
    this->distFrames = distFrames;

    //std::cout<<"se crea\n";
    std::filesystem::path p1{path};

    std::string filename {""};

    animationIni = inicial;

    int cont { animationIni };
    
    //Estoy consciente de que este for es una guarrada
    for(auto& p : std::filesystem::directory_iterator(p1)){
        filename = (p.path().stem()).string();

        if (filename.find("C:\\") == std::string::npos)
            break;
    }


    //Sacara el nombre en comun
    filename = filename.substr(0, filename.find("_"));
    filename = filename + "_";

    for(auto& p : std::filesystem::directory_iterator(p1)){

        //Diferencia de ceros
        int dif { static_cast<int>(6 - (std::to_string(cont).length())) };

        //Path completo del archivo
        std::string real { path + filename + std::string(dif, '0') + std::to_string(cont) + ".obj" };

        if(!p.path().extension().compare(".obj")){
            //Agregar el modelo al array de modelos
            frames_.push_back(std::make_unique<ModelLUM>(real, false, tm_));
            

            cont=cont+distFrames;
        }
    }

    numFrames = (cont-animationIni)/distFrames;
    //std::cout << "numFrames" << numFrames << "\n";
    
    animationFin = cont - distFrames;
}