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

#include "../MotorSonido/MotorSonido.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <array>

#include "../cmp/collider.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/sound.hpp"
#include "../cmp/ia.hpp"

template <typename GameCTX_t>
struct SoundSystem_t {
    SoundSystem_t();
    ~SoundSystem_t();

    void InitBanks();
    void InitEvent(const std::string& evento, bool ismusic);
    void InitEventWithParameter(const std::string& evento, const std::string& nombre, bool ismusic);

    void updatePositions(GameCTX_t& g) noexcept;
    void update(GameCTX_t& g) noexcept;

    void iniciar(const std::string& evento);
    void stop(const std::string& evento);

    void menos(const std::string& evento);
    void mas(const std::string& evento);

    std::string reproduciendo(const std::string& evento);

    void desactivarVolumen();
    void activarVolumen();
    void changeVolumen(float volume, bool ismusic);

    std::array<std::string, 32>& getSounds() { return sounds; };

    bool noreproducir { false };

    private:
        float volumenMusic { 1.0 };
        float volumenEffects { 1.0 };

        std::unique_ptr<MotorSonido_t> sound {nullptr};
        //En el sistema de sonido nos guargamos un puntero del motor de sonido para llamar a sus funciones

        //FMOD_3D_ATTRIBUTES attributes = { { 0 } };

        std::array<std::string, 32> sounds {
            "event:/Ambientes/Agua",
            "event:/Ambientes/Arena",
            "event:/Ambientes/Viento",

            "event:/Efectos/Avellana/RecogerFruto",
            "event:/Efectos/Cueva/Agua",
            "event:/Efectos/Enganche/Enganche",
            "event:/Efectos/Naturaleza/Naturaleza",
            "event:/Efectos/Rocas/CaidaRocas",

            "event:/Personajes/Aguila/Graznido",
            "event:/Personajes/Aguila/Ramas",
            "event:/Personajes/Aguila/Aleteo",

            "event:/Personajes/Araña/AtaqueAranya",
            "event:/Personajes/Araña/MovimientoAranya",
            "event:/Personajes/Araña/SonidoAranya",

            "event:/Personajes/Cabra/Avalancha",
            "event:/Personajes/Cabra/GolpeCabra",
            "event:/Personajes/Cabra/HierbaCabra",
            "event:/Personajes/Cabra/PastarCabra",

            "event:/Personajes/Crias/CriaAyuda",
            "event:/Personajes/Crias/CriaRescatada",

            "event:/Personajes/Crias Cueva/CriaAyuda",
            "event:/Personajes/Crias Cueva/CriaRescatada",

            "event:/Personajes/Zacarias/AlegriaFinal",
            "event:/Personajes/Zacarias/Cansancio",
            "event:/Personajes/Zacarias/Daño",
            "event:/Personajes/Zacarias/MuerteCaida",
            "event:/Personajes/Zacarias/MuerteDaño",

            "event:/Personajes/Zacarias Cueva/AlegriaFinal",
            "event:/Personajes/Zacarias Cueva/Cansancio",
            "event:/Personajes/Zacarias Cueva/Daño",
            "event:/Personajes/Zacarias Cueva/MuerteCaida",
            "event:/Personajes/Zacarias Cueva/MuerteDaño"
        };
};