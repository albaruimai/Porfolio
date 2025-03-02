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

#include "sound.hpp"
#include <chrono>

template <typename GameCTX_t>
SoundSystem_t<GameCTX_t>::SoundSystem_t() : sound{std::make_unique<MotorSonido_t>()}
{
    //el constructor del sistema de sonido:
    //-Inicializa los bancos de FMOD

    InitBanks();
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::InitBanks()
{
    //llamamos al motor de sonido para que nos inicialice los master banks
    sound->InitBanks("fmod/Assets/FMOD_BANKS/Master.bank", "fmod/Assets/FMOD_BANKS/Master.strings.bank");
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::InitEvent(const std::string& evento, bool ismusic)
{
    //pasandole el nombre del evento como parametro, inicializamos el evento de FMOD
    sound->InitEvent(evento, ismusic);
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::InitEventWithParameter(const std::string& evento, const std::string& nombre, bool ismusic) {
    //le pasamos al motor de sonido tanto el nombre del evento, 
    //como el nombre del parametro para inicializar el evento
    sound->InitEventWithParameter(evento, nombre, ismusic);
}

template <typename GameCTX_t>
SoundSystem_t<GameCTX_t>::~SoundSystem_t() = default;

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::updatePositions(GameCTX_t& g) noexcept {
    for (auto& sou: g.template getComponents<SoundComponent_t>()) {
        auto* col { g.template getRequiredComponent<SoundComponent_t, ColliderComponent_t>(sou) };
        auto* phy { g.template getRequiredComponent<SoundComponent_t, PhysicsComponent_t>(sou) };

        if (col != nullptr && phy != nullptr) {
            if (col->properties & ColliderComponent_t::P_IsPlayer) {
                FMOD_3D_ATTRIBUTES l_listenerAttributes {FMOD_VECTOR{phy->x, phy->y, 0}, FMOD_VECTOR{0,0,0}, FMOD_VECTOR{0,0,1}, FMOD_VECTOR{0,1,0}};
                
                sound->setListenerAttributes(&l_listenerAttributes);

                //std::cout << "Player " << l_listenerAttributes.position.x << " " << l_listenerAttributes.position.y << " " << l_listenerAttributes.position.z << "\n";

                break;
            }
        }
    }  
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::update(GameCTX_t& g) noexcept {
    changeVolumen(volumenMusic, true);
    changeVolumen(volumenEffects, false);
    

    updatePositions(g);
    
    for(auto& sou: g.template getComponents<SoundComponent_t>()){
        //std::cout << sou.event_id << sound->getplayback(sou.event_id).c_str() << "\n";

        if (noreproducir == true) {
            //-1 no init, 0 init, 1 play, 2 stop

            if (sou.marked_for_init != 0) {
                sou.antes_pausa = 0;
            }
            if (sou.marked_for_play != 0) {
                sou.antes_pausa = 1;
            }
            if (sou.marked_for_stop != 0) {
                sou.antes_pausa = 2;
            }

            sou.marked_for_init = 0;
            sou.marked_for_play = 0;
            sou.marked_for_stop = 1;
        } 

        if (strcmp((sou.event_id_ant).c_str(), "") != 0) {
            sound->stopEvent(sou.event_id_ant);
            sou.event_id_ant = "";
        }

        if (sou.marked_for_init == 1) {
            sound->InitEvent(sou.event_id, sou.isMusic);

            if (sou.isEvent3D == true) {
                auto* phy { g.template getRequiredComponent<SoundComponent_t, PhysicsComponent_t>(sou) };

                if (phy != nullptr) {
                    FMOD_3D_ATTRIBUTES l_eventAttributes {FMOD_VECTOR{phy->x, phy->y, 0}, FMOD_VECTOR{0,0,0}, FMOD_VECTOR{0,0,1}, FMOD_VECTOR{0,1,0}};

                    sound->set3DAttributes(sou.event_id, &l_eventAttributes);

                    //std::cout << "obj " << l_eventAttributes.position.x << " " << l_eventAttributes.position.y << " " << l_eventAttributes.position.z << "\n";   
                }
                
            } 
            sou.marked_for_init = 0;           
        }

        if (sou.marked_for_play == 1 && noreproducir == false) {
            //std::cout << sound->getplayback(sou.event_id).c_str() << "\n";
            if (strcmp(sound->getplayback(sou.event_id).c_str(), "playing") != 0) {
                //std::cout << "hola " << sou.event_id << "\n";
                sound->playEvent(sou.event_id);

                if(sou.alwaysPlay != true)
                    sou.marked_for_play = 0;

                if(sou.isEventParameter == true)
                    sou.marked_for_play = 0;

                auto* ia { g.template getRequiredComponent<SoundComponent_t, IAComponent_t>(sou) };

                if (ia != nullptr) {
                    ia->meGolpean = false;
                }
            }            
        }

        if (sou.marked_for_stop == 1) {
            //llamar a stop event
            sound->stopEvent(sou.event_id);
            sou.marked_for_stop = 0;
            sou.parado = true;
        }

//        if (sou.actual != "" && sou.actual != sou.event_id) {
//            sou.event_id = sou.actual;
//        }
    }

    sound->update();
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::iniciar(const std::string& evento) {
    //reproduce el evento pasado por parametro
    sound->playEvent(evento);  
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::stop(const std::string& evento) {
    //para el evento pasado por parametro
    sound->stopEvent(evento);  
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::menos(const std::string& evento) {
    //al evento pasado por parametro, se le resta uno al valor del parametro del evento
    sound->menosValor(evento);
    sound->playEvent(evento);
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::mas(const std::string& evento) {
    //al evento pasado por parametro, se le suma uno al valor del parametro del evento
    sound->masValor(evento);
    sound->playEvent(evento);
}

template <typename GameCTX_t>
std::string SoundSystem_t<GameCTX_t>::reproduciendo(const std::string& evento) {
    return sound->getplayback(evento);
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::desactivarVolumen() {
    sound->desactivarVolumen();

    volumenMusic = 0.0;
    volumenEffects = 0.0;
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::activarVolumen() {
    sound->activarVolumen();

    volumenMusic = 1.0;
    volumenEffects = 1.0;
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::changeVolumen(float volume, bool ismusic) {
    sound->setAllVolumeEvent(volume, ismusic);

    if (ismusic == true) {
        volumenMusic = volume;
    } else {
        volumenEffects = volume;
    }    
}