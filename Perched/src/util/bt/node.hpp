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
#include <cstdint>
#include "../stbe/Steering.hpp"

#include "../../cmp/ia.hpp"
#include "../../cmp/entity.hpp"
#include "../../cmp/physics.hpp"
#include "../../cmp/follow.hpp"
#include "../../cmp/collider.hpp"
#include "../../cmp/blackboard.hpp"

#include "../../man/entitymanager.hpp"
#include "../gameobjectfactory.hpp"

namespace ECS {
    struct EntityManager_t;
}

struct GameObjectFactory_t;

struct EntityContext_t{
    ECS::Entity_t           *enty;
    IAComponent_t           *ia;
    PhysicsComponent_t      *phy;
    ColliderComponent_t     *col;
    BlackboardComponent_t   *bb;
    ECS::EntityManager_t    *EM;
    GameObjectFactory_t     *gof;
};

enum class IA_Stats {
    Energia,
    Ira,
    Cansancio
};

enum class BTNodeStatus_t : uint8_t{
    success,
    fail,
    running
};

struct BTNode_t{
    struct Deleter { void operator()(BTNode_t* n){ n->~BTNode_t(); } };
    BTNode_t()                           = default;
    BTNode_t(const BTNode_t&)            = delete;
    BTNode_t( BTNode_t&)                 = delete;
    BTNode_t& operator=(const BTNode_t&) = delete;
    BTNode_t& operator=( BTNode_t&&)     = delete;



    virtual BTNodeStatus_t run(EntityContext_t &ectx) noexcept = 0;

    virtual ~BTNode_t() = default;
};