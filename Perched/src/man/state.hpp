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
//# StateManager sirve para gestionar los estados por los que pasa   #
//#   el juego, como el menu, el juego, ...                          #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include <stack>
#include <memory>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

#include "entitymanager.hpp"
#include "../sys/render.cpp"
#include "../sys/sound.cpp"

#include "../Motor3D/MyImGui.hpp"

struct StateBase_t {
    virtual void update() = 0;
    virtual bool alive() = 0;
    virtual ~StateBase_t() = default;
};

struct StateManager_t {
    explicit StateManager_t() = default;

    //typename... indica que recibire un paquete de parametros
    template <typename State_t, typename... Ts>
    void addState(Ts&&... args) {
        static_assert(std::is_base_of<StateBase_t, State_t>::value, "ERROR, Invalid State_t");

        //forward<decltype> lo convierte otra vez a temporal
        m_States.push( std::make_unique<State_t>(std::forward<decltype(args)>(args)... ));
    }

    void update() {
        if (alive()) {
            auto& state { m_States.top() };

            if (state && state->alive()) {
                state->update();
            } else {
                m_States.pop();
            }
        }
    }

    bool alive() {
        return !m_States.empty();
    }

    void setAlive() {
        while (alive()) {
            m_States.pop();
        }
    }

    void limpiarPartida() {
        std::ofstream partida;
        std::string levels {""};

        for (size_t i {0}; i < static_cast<size_t>(wasPassed.size()); ++i) {
            if (i==0) {
                wasPassed.at(i) = true;
            } else {
                wasPassed.at(i) = false;
            }

            levels += std::to_string(wasPassed.at(i));

            if (i != wasPassed.size() - 1) {
                levels += ",";
            }
        }

        partida.open("assets/partida.txt", std::ofstream::trunc);
        partida<<levels;
        partida.close();
    }

    void guardarPartida() {
        std::ofstream partida;

        std::string levels {""};

        for (size_t i = 0; i < static_cast<size_t>(wasPassed.size()); ++i) {
            levels += std::to_string(wasPassed.at(i));

            if (i != wasPassed.size() - 1) {
                levels += ",";
            }
        }

        partida.open("assets/partida.txt", std::ofstream::trunc);
        partida<<levels;
        partida.close();
    }

    void leerPartida() {
        std::fstream partida;
        std::string leido {""};
        std::vector<std::string> levels;

        partida.open("assets/partida.txt", std::ios::in);
        getline(partida, leido);

        boost::split(levels, leido, boost::is_any_of(","));

        for (size_t i {0}; i < static_cast<size_t>(levels.size()); ++i) {
            if (levels[i] == "1") {
                wasPassed.at(i) = true;
            } else {
                wasPassed.at(i) = false;
            }
        }

        partida.close();
    }

    MyImGui myimgui {};

    int lastLevelUnlocked {0};
    int levelSelected {0};
    std::array<bool, 10> wasPassed {true, false, false, false, false, false, false, false, false, false};

    bool reset { false };
    bool volverSonidos { false };

    //variables en settings
    bool volActivo { true };
    int mitadMusic {100}, mitadEffects {100};
    int posReso {0};

    private:
        std::stack<std::unique_ptr<StateBase_t>> m_States;
};