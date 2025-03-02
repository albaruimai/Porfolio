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
//#     BlackboardComponent es un componente SINGLETON que tienen    #
//#     todas las entidades y contiene informacion del mundo         #
//####################################################################


#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"
#include "ia.hpp"


struct BlackboardComponent_t {
    int32_t xminM {0}, xmaxM {0}, yminM {0}, ymaxM {0}; 
    int32_t wM {0}, hM {0};

    std::vector<ECS::Entity_t*> palos_bb;        //Array de palos
    std::vector<ECS::Entity_t*> salientes_bb;    //Array de salientes
    ECS::Entity_t* tunel_bb { nullptr };         //puntero a tunel
    std::vector<ECS::Entity_t*> arbustos_bb;     //Array de arbustos*
    std::vector<ECS::Entity_t*> nidos_bb;        //Array de nidos*

    ECS::EntityID_t playerID { 0 };             //ID player
    bool muriendoplayer { false };
    bool danyoplayer { false };
    bool andandoplayer { false };

    float distxAgujero {0.0}, distyAgujero {0.0};

    bool enCuerda { false };
    bool sigoCuerda { false };
    ECS::EntityID_t cuerdaID { 0 };
    int contCuerda { 0 };
    int timeCuerda { 0 };

    int criasennivel { 0 };
    std::vector<bool> criasrescatadas;

    int levelAct { 0 };
    
    double player_tx {0.0}, player_ty {0.0};    //Posicion del target (Player)
    //SB     behaviour {SB::Seek};              //Por defecto es Seek
    bool   tactive { false };                     //Si el behavior esta activo
    bool   player_is_save { false };

    bool volviPlanoNormal { true };  // False es que esta en tunel, True esta en plano normal

    bool pulsoInteractMando { false };
    bool pulsoPauseMando { false };

    //std::vector<std::vector<int>> salientes;
    int salientes [90][40];
    //std::vector<std::vector<int>> tunel;
    int tunel [90][40];

    bool ponTuto{false};
    uint8_t queTuto{1};
};