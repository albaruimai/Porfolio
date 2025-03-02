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
#include "component.hpp"
#include <iostream>
#include <map>

struct SoundComponent_t : public ECS::ComponentBase_t<SoundComponent_t> {
    explicit SoundComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    std::vector<std::string> my_events;

    std::string event_id_ant;
    std::string event_id;
    std::map<std::string, float> floatparameters;
    std::map<std::string, int> intparameters;

    uint8_t marked_for_parameter_update { 0 }; //actualizar parametro
    uint8_t marked_for_stop { 0 }; //parar evento
    uint8_t marked_for_play { 0 }; //reproducir evento
    uint8_t marked_for_init { 0 }; //inicializar evento

    bool alwaysPlay          { false };
    bool isEvent3D           { false };
    bool isEventParameter    { false };
    bool isMusic             { false };

    bool parado {false};

    int8_t antes_pausa { -1 }; //-1 no init, 0 init, 1 play, 2 stop
};