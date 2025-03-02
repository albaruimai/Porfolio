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

#include <iostream>
#include <vector>
#include <time.h>

#include "../../cmp/collider.hpp"
#include "../../cmp/physics.hpp"
#include "../../cmp/entity.hpp"
#include "../../cmp/blackboard.hpp"
#include "Casilla.hpp"

//Forward declaration
namespace ECS {
    struct EntityManager_t;
}

struct PathP_t {
    explicit PathP_t(uint32_t tamx, uint32_t tamy);   //Constructor

    bool isValid(int x, int y, int M, int N);
    void printPath(std::vector<int> const &path, int last, std::vector<std::vector<int>> const &mat);
    void findPaths(std::vector<std::vector<int>> const &mat, std::vector<int> &path, int i, int j, int M, int N, bool enTunel, BlackboardComponent_t& black);
    
    std::vector<Casilla> buscar(int xIni, int yIni, int xFin, int yFin, bool enTunel, BlackboardComponent_t& black);

    private:
        std::vector<std::vector<Casilla>> caminos;

        std::vector<std::vector<int>> mat;

        int tamx_ {0}, tamy_ {0};
        int cont {0};
        
        //int sal[30][80];
        int dirX {0}, dirY {0};
        int sumX1 {0}, sumY1 {0}, sumX2 {0}, sumY2 {0};
        int sumDX1 {0}, sumDY1 {0}, sumDX2 {0}, sumDY2 {0};
        int MM {0};
        int NN {0};
};