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
//# GameObjectFactory sirve para crear todos los objetos necesarios  #
//#   para crear el nivel.                                           #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include "../Motor3D/Motor3DLUM/Motor3DLUM.hpp"

#include "../picoJSON/picojson.hpp"
#include <string>
#include <string_view>
#include <wchar.h>
#include <fstream>
#include "../cmp/physics.hpp"
#include "../cmp/render.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/health.hpp"
#include "../cmp/camera.hpp"
#include "../cmp/control.hpp"
#include "../cmp/hud.hpp"
#include "../cmp/puntos.hpp"
#include "../cmp/follow.hpp"
#include "../cmp/stamina.hpp"
#include "../cmp/sound.hpp"
#include "../cmp/ia.hpp"
#include "../cmp/blackboard.hpp"

#include "../man/entitymanager.hpp"

#include "timer.hpp"


//Forward declaration
namespace ECS {
    struct EntityManager_t;
    struct Entity_t;
}

struct GameObjectFactory_t {
    explicit GameObjectFactory_t(ECS::EntityManager_t& EntityMan, Motor3DLUM* motor) : m_EntMan(EntityMan), motor(motor) {
        terremoto_timer.init(8);
    }

    ECS::Entity_t& createEntity(int32_t x, int32_t y, const std::string_view filename) const;
    ECS::Entity_t& createPlayer(const picojson::array &player) const;
    ECS::Entity_t& createCamera(int32_t x, int32_t y, uint32_t w, uint32_t h) const;
    ECS::Entity_t& createMeta(const picojson::array &meta) const;
    ECS::Entity_t& createArrow(const picojson::array &arrow) const;

    void createBT(BehaviourTree_t*) const ;
    ECS::Entity_t& createEnemy(const picojson::value &enemy, BehaviourTree_t *) const;
    void crearEnemigos (BehaviourTree_t*, const picojson::array &enemies) const;

    ECS::Entity_t& createRoca(int32_t x, int32_t y, int32_t z, float vel, bool mover, ECS::EntityID_t my_sal) const;
    void crearRocas (uint32_t cant) const;

    ECS::Entity_t& createSaliente(const picojson::value &saliente) const;
    void crearSalientes(const picojson::array &salientes) const;

    ECS::Entity_t& createNido(const picojson::value &nido) const;
    void crearNidos(const picojson::array &nidos, const picojson::array &crias) const;
    ECS::Entity_t& createCria(const picojson::value &cria, ECS::Entity_t& follow) const;

    ECS::Entity_t& createArbusto(const picojson::value &arbusto) const;
    void crearArbustos(const picojson::array &arbustos) const;

    ECS::Entity_t& createCascada(const picojson::value &cascada) const;
    void crearCascadas(const picojson::array &cascadas) const;

    ECS::Entity_t& createSemilla(const picojson::value &semilla) const;
    void crearSemillas(const picojson::array &semillas) const;

    ECS::Entity_t& createEnganche(const picojson::value &enganche, int pos) const;
    void crearEnganches(const picojson::array &enganches) const;

    ECS::Entity_t& createAgujero(const picojson::value &agujero) const;
    void crearAgujeros(const picojson::array &agujeros) const;

    ECS::Entity_t& createTelaranya(int32_t x, int32_t y, int32_t vel) const;

    ECS::Entity_t& createTrampolin(const picojson::value &trampolin) const;
    void crearTrampolines(const picojson::array &trampolines) const;

    void crearPlano(const picojson::array &plano) const;

    ECS::Entity_t& createMusgo(const picojson::value &musgo) const;
    void crearMusgos(const picojson::array &musgos) const;

    ECS::Entity_t& createHielo(const picojson::value &hielo) const;
    void crearHielos(const picojson::array &hielos) const;

    ECS::Entity_t& createNubes(int32_t x, int32_t y, int32_t z,ECS::EntityID_t player) const;

    ECS::Entity_t& createPalo(int32_t x, int32_t y, int32_t vel, ECS::EntityID_t Entfollow) const;
    ECS::Entity_t& createPalosPlace(const picojson::value &palo) const;
    void createPalosPlaces(const picojson::array &palos) const;

    void unfollowPalo(ECS::EntityID_t Entounfollow) const;


    ECS::Entity_t& createPlanosEspeciales(const picojson::value &planoespecial) const;
    void crearPlanosEspeciales(const picojson::array &planosespeciales) const;

    

    void createTerremoto() ;

    ECS::Entity_t& createHud() const;


    void loadLevelJSON(std::string_view filename, BehaviourTree_t*) const;

    private:
        ECS::EntityManager_t& m_EntMan;
        Motor3DLUM* motor;
        temporizador terremoto_timer;
};