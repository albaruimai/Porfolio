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
#include "../../cmp/collider.hpp"
#include "../../cmp/physics.hpp"
#include <iterator>
#include <iostream>
#include <exception>
#include <stack>
#include <vector>
#include <array>
#include <cfloat>
#include <tgmath.h>
#include "Casilla.hpp"
#define X_MAX 360
#define X_STEP 12
#define Y_MAX 960
#define Y_STEP 12

#include "../../man/entitymanager.hpp"

//Forward declaration
namespace ECS {
    struct EntityManager_t;
}

   
inline bool operator< (const Casilla& lhs, const Casilla& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

struct PathA_t {

    explicit PathA_t() = default;   //Constructor

	bool isValid(int x, int y, std::vector<ECS::Entity_t *> &bsalientes, ECS::Entity_t* btunel, bool enTunel); //If our Node is an obstacle it is not valid
		
	bool isDestination(int x, int y, Casilla& dest);
		
	double calculateH(int x, int y,Casilla& dest);
	
	std::vector<Casilla> makePath(std::array<std::array < Casilla, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& map, Casilla& dest);
	
	std::vector<Casilla> aStar(Casilla& player, Casilla& dest, std::vector<ECS::Entity_t *> &bsalientes, ECS::Entity_t* btunel, bool enTunel);
};