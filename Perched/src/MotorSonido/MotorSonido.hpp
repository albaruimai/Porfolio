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

#include "../../fmod/fmod/core/inc/fmod_errors.h"
#include "../../fmod/fmod/studio/inc/fmod_studio.h"
#include "../../fmod/fmod/core/inc/fmod.h"
#include "../../fmod/fmod/core/lib/common.h"
#include <iostream>
#include <map>

struct MotorSonido_t {
    MotorSonido_t();
    ~MotorSonido_t();

    void InitBanks(const std::string& sMaster, const std::string& sMasterString);
    void AddEvent(const std::string& evento, bool ismusic);
    void InitEvent(const std::string& evento, bool ismusic);
    void InitEventWithParameter(const std::string& evento, const std::string& nombreParam, bool ismusic);

    std::string getplayback(const std::string& evento);
    void stopEvent(const std::string& evento);

    void setListenerAttributes(FMOD_3D_ATTRIBUTES *att);
    void set3DAttributes(const std::string& evento, FMOD_3D_ATTRIBUTES *att);

    void update() const noexcept;

    void playEvent(const std::string& evento);

    void menosValor(const std::string& evento);
    void masValor(const std::string& evento);

    float getVolumeEvent(const std::string& evento);
    void setVolumeEvent(const std::string& evento, float volume);

    void setAllVolumeEvent(float volume, bool ismusic);

    void desactivarVolumen();
    void activarVolumen();

    private:
        FMOD_SYSTEM* coreSystem {NULL};
        FMOD_STUDIO_SYSTEM* system {NULL};

        FMOD_STUDIO_BANK* masterBank {NULL};
        FMOD_STUDIO_BANK* stringsBank {NULL};

        FMOD_STUDIO_EVENTDESCRIPTION* eveDescription {NULL};
        FMOD_STUDIO_EVENTINSTANCE* eventInstance {NULL};

        FMOD_STUDIO_PARAMETER_DESCRIPTION paramDesc;
        FMOD_STUDIO_PARAMETER_ID surfaceID;
        float surfaceParameterValue { 1.0f };

        std::map<std::string, FMOD_STUDIO_EVENTDESCRIPTION*> eventMap;
        std::map<std::string, std::pair<FMOD_STUDIO_EVENTINSTANCE*, bool>> eventInstances;
};