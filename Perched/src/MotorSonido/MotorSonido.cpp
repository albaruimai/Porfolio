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

#include "MotorSonido.hpp"
#include <chrono>

void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line)
{
    if(result != FMOD_OK)
    {
        std::cerr << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}
#define ERRCHECK(_result) ERRCHECK_FMOD(_result, __FILE__, __LINE__)

MotorSonido_t::MotorSonido_t()
{
    ERRCHECK(FMOD_Studio_System_Create(&system, FMOD_VERSION));
    ERRCHECK(FMOD_Studio_System_GetCoreSystem(system, &coreSystem));
    ERRCHECK(FMOD_System_SetSoftwareFormat(coreSystem, 0, FMOD_SPEAKERMODE_5POINT1, 0));    
    //ERRCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));

    //sustituir FMOD_STUDIO_INIT_NORMAL por FMOD_STUDIO_INIT_LIVEUPDATE para profiler
    
    ERRCHECK(FMOD_Studio_System_Initialize(system, 48, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
}

MotorSonido_t::~MotorSonido_t()
{
    //el destructor del motor de sonido libera la memoria de los eventos, de los bancos
    // y del sistema de FMOD

    for(const auto& eventDesc : eventMap)
    {
        FMOD_Studio_EventDescription_ReleaseAllInstances(eventDesc.second);
    }

    for(const auto& instance : eventInstances)
    {
        FMOD_Studio_EventInstance_Release(instance.second.first);
    }

    ERRCHECK(FMOD_Studio_EventInstance_Release(eventInstance));

    ERRCHECK(FMOD_Studio_Bank_Unload(masterBank));
    ERRCHECK(FMOD_Studio_Bank_Unload(stringsBank));
    ERRCHECK(FMOD_Studio_System_Release(system));
}

void MotorSonido_t::InitBanks(const std::string& sMaster, const std::string& sMasterString)
{
    ERRCHECK(FMOD_Studio_System_LoadBankFile(system, sMaster.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
    ERRCHECK(FMOD_Studio_System_LoadBankFile(system, sMasterString.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
}

void MotorSonido_t::AddEvent(const std::string& evento, bool ismusic) {
    //nos pasan un evento por parametro y se inserta en los maps de descripciones e instancias

    ERRCHECK(FMOD_Studio_System_GetEvent(system, evento.c_str(), &eveDescription) );

    eventMap.insert({evento, eveDescription});

    ERRCHECK(FMOD_Studio_EventDescription_CreateInstance(eveDescription, &eventInstance));

    eventInstances.insert({evento, {eventInstance, ismusic}});
}

void MotorSonido_t::InitEvent(const std::string& evento, bool ismusic)
{
    //nos pasan un evento por parametro, sino es encontrado en el map, se inserta en el

    auto it { eventMap.find(evento) };

    if (it == eventMap.end()) {
        AddEvent(evento, ismusic);
    } /*else {
        std::cout << "Init: El evento ya estaba creado" << evento << "\n";
    }*/    
}

void MotorSonido_t::InitEventWithParameter(const std::string& evento, const std::string& nombreParam, bool ismusic) {
    //nos pasan un evento por parametro y el nombre del parametro que se modificara
    //, sino es encontrado en el map, se inserta en el

    auto it { eventMap.find(evento) };

    if (it == eventMap.end()) {
        AddEvent(evento, ismusic);

        FMOD_Studio_EventDescription_GetParameterDescriptionByName(eveDescription, nombreParam.c_str(), &paramDesc);
        surfaceID = paramDesc.id;

        FMOD_Studio_EventInstance_SetParameterByID(eventInstance, surfaceID, surfaceParameterValue, false);
    } /*else {
        std::cout << "InitP: El evento ya estaba creado" << evento << "\n";
    }*/
}

void MotorSonido_t::setListenerAttributes(FMOD_3D_ATTRIBUTES *att) {
    ERRCHECK( FMOD_Studio_System_SetListenerAttributes(system, 0, att, nullptr) );
}

void MotorSonido_t::set3DAttributes(const std::string& evento, FMOD_3D_ATTRIBUTES *att) {
    auto it { eventInstances.find(evento) };

    if (it != eventInstances.end()) {
        ERRCHECK( FMOD_Studio_EventInstance_Set3DAttributes(it->second.first, att) );
    } /*else {
        std::cout << "3DAt: No existe ese evento" << evento << "\n";
    }*/     
}

void MotorSonido_t::update() const noexcept {
    ERRCHECK(FMOD_Studio_System_Update(system));
}

float MotorSonido_t::getVolumeEvent(const std::string& evento) {
    float volume { 0.0 };
    float finalvolume { 0.0 };

    FMOD_RESULT result { FMOD_Studio_EventInstance_GetVolume(eventInstances.at(evento).first, &volume, &finalvolume) };

    //std::cout << "Volumen: " << volume << "\n";

    return volume;
}

void MotorSonido_t::setVolumeEvent(const std::string& evento, float volume) {
    FMOD_Studio_EventInstance_SetVolume(eventInstances.at(evento).first, volume);
}

void MotorSonido_t::setAllVolumeEvent(float volume, bool ismusic) {
    for(const auto& instance : eventInstances)
    {
        if (instance.second.second == ismusic) {
            setVolumeEvent(instance.first, volume);
        } 
    }
}

void MotorSonido_t::desactivarVolumen() {
    for(const auto& instance : eventInstances)
    {
        setVolumeEvent(instance.first, 0.0);
    }
}

void MotorSonido_t::activarVolumen() {
    for(const auto& instance : eventInstances)
    {
        setVolumeEvent(instance.first, 1.0);
    }
}

void MotorSonido_t::playEvent(const std::string& evento) {
    //nos pasan un evento por parametro, si es encontrado en el map, se reproduce

    auto it { eventInstances.find(evento) };

    if (it != eventInstances.end()) {
        ERRCHECK(FMOD_Studio_EventInstance_Start(it->second.first));
    } /*else {
        std::cout << "Play: No existe ese evento" << evento << "\n";
    }*/  
}

void MotorSonido_t::menosValor(const std::string& evento) {
    //nos pasan un evento por parametro, si es encontrado en el map, 
    // se le resta uno al valor del parametro que tiene el evento

    auto it { eventInstances.find(evento) };

    if (it != eventInstances.end()) {
        surfaceParameterValue = std::max(paramDesc.minimum, surfaceParameterValue - 1.0f);
        ERRCHECK(FMOD_Studio_EventInstance_SetParameterByID(it->second.first, surfaceID, surfaceParameterValue, false));
    } /*else {
        std::cout << "Menos: No existe ese evento" << evento << "\n";
    }*/
}

void MotorSonido_t::masValor(const std::string& evento) {
    //nos pasan un evento por parametro, si es encontrado en el map, 
    // se le suma uno al valor del parametro que tiene el evento

    auto it { eventInstances.find(evento) };

    if (it != eventInstances.end()) {
        surfaceParameterValue = std::min(surfaceParameterValue + 1.0f, paramDesc.maximum);
        ERRCHECK(FMOD_Studio_EventInstance_SetParameterByID(it->second.first, surfaceID, surfaceParameterValue, false));
    } /*else {
        std::cout << "Mas: No existe ese evento" << evento << "\n";
    }*/ 
}

void MotorSonido_t::stopEvent(const std::string& evento) {
    auto it { eventInstances.find(evento) };

    if (it != eventInstances.end()) {
        ERRCHECK(FMOD_Studio_EventInstance_Stop(it->second.first, FMOD_STUDIO_STOP_IMMEDIATE));
    } /*else {
        std::cout << "Stop: No existe ese evento: " << evento << "\n";
    }*/
}

std::string MotorSonido_t::getplayback(const std::string& evento) {
    auto it { eventInstances.find(evento) };

    std::string estado {""};

    if (it != eventInstances.end()) {
        FMOD_STUDIO_PLAYBACK_STATE playback;

        FMOD_Studio_EventInstance_GetPlaybackState(it->second.first, &playback);

        switch (playback) {
            case FMOD_STUDIO_PLAYBACK_PLAYING:
                //playbackeStateStr = "PLAYING"; break;
                //std::cout << "playing\n";
                estado = "playing";
                break;
            case FMOD_STUDIO_PLAYBACK_STOPPED:
                //playbackeStateStr = "STOPPED"; break;
                //std::cout << "stopped\n";
                estado = "stopped";
                break;
            case FMOD_STUDIO_PLAYBACK_SUSTAINING:
                //playbackeStateStr = "SUSTAINING"; break;
                //std::cout << "sustaining\n";
                estado = "sustaining";
                break;
        }    
    } /*else {
        std::cout << "Playback: No existe ese evento" << evento << "\n";
    }*/

    return estado;
}