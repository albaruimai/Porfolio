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

#include "pathP.hpp"

PathP_t::PathP_t(uint32_t tamx, uint32_t tamy) {
    tamx_ = tamy;
    tamy_ = tamx;

    int i {1};

    for (int x {0}; x < tamx; ++x) {
        std::vector<int> v1;

		for (int y {0}; y < tamy; ++y) { 
            v1.push_back(i);
            ++i;
        }
        mat.push_back(v1);
    }
}
 
// Function to check if (i, j) is a valid matrix coordinate
bool PathP_t::isValid(int x, int y, int M, int N) {
    if (dirX == 1 && dirY == 1) { //right-up
        return (x >= 0 && (x < M || x == M) && y >= 0 && (y < N || y == N));
    }

    if (dirX == -1 && dirY == 1) { //left-up
        //std::cout << M << " " << x << " " << y << " " << N << "\n";
        return (x >= 0 && (M < x || M == x) && y >= 0 && (y < N || y == N));
    }

    if (dirX == -1 && dirY == -1) { //left-down
        return (x >= 0 && (M < x || M == x) && y >= 0 && (N < y || N == y));
    }

    if (dirX == 1 && dirY == -1) { //right-down
        return (x >= 0 && (x < M || x == M) && y >= 0 && (N < y || N == y));
    }

    //return (x >= 0 && x < tamx_ && y >= 0 && y < tamy_);

    return false;
}
 
// Function to print the route taken
void PathP_t::printPath(std::vector<int> const &path, int last, std::vector<std::vector<int>> const &mat)
{
    std::vector<Casilla> camino;

    for (int i: path) {
        //std::cout << i << "( ";

        for (int x {0}; x < 90; ++x) {
            for (int y {0}; y < 40; ++y) { 
                if (x < mat.size() && y < mat[x].size() && mat[x][y] == i) {
                    Casilla uno;
                    uno.x = x;
                    uno.y = y;
                    //std::cout << x << "," << y;
                    camino.push_back(uno);
                }
            }
        }
        //std::cout << " ),";
    }

    //std::cout << last << "( ";

    for (int x {0}; x < 90; ++x) {
        for (int y {0}; y < 40; ++y) { 
            if (x < mat.size() && y < mat[x].size() && mat[x][y] == last) {
                Casilla ultima;
                ultima.x = x;
                ultima.y = y;
                //std::cout << x << "," << y;
                camino.push_back(ultima);
            }
        }
    }
    //std::cout << " )\n";
    caminos.push_back(camino);
    //std::cout << "\n";
}

void PathP_t::findPaths(std::vector<std::vector<int>> const &mat, std::vector<int> &path, int i, int j, int M, int N, bool enTunel, BlackboardComponent_t& black)
{  
    // base case
    if (mat.size() == 0) {
        return;
    }
 
    // if the last cell is reached, print the route
    if (i == MM && j == NN)
    {
        printPath(path, mat[i][j], mat);
        return;
    } 

    if(i<mat.size() && j<mat[i].size() && caminos.size() < 3){
        // include the current cell in the path
        path.push_back(mat[i][j]);
        ++cont;
        if (cont > 100) {
            return;
        }

        if (enTunel == false) {
            //pathplanning en plano normal

            if ((i+sumX1 >= 0 && i+sumX1 < sizeof(black.salientes)) && (i+sumX2 >= 0 && i+sumX2 < sizeof(black.salientes))
                && (j+sumY1 >= 0 && j+sumY1 < sizeof(black.salientes[0])) && (j+sumY2 >= 0 && j+sumY2 < sizeof(black.salientes[0]))) {

                if (i+sumX1 < 90 && i+sumY1 < 40 && black.salientes[i+sumX1][j+sumY1]==1 && black.salientes[i+sumX2][j+sumY2]==1) {
                    //move diagonal 
                    if (i+sumDX1 < 90 && i+sumDY1 < 40 && black.salientes[i+sumDX1][j+sumDY1]!=1 && isValid(i+sumDX1, j+sumDY1, M, N)) {
                        findPaths(mat, path, i+sumDX1, j+sumDY1, M, N, enTunel, black);
                    }else{
                        if (i+sumDX1 < 90 && i+sumDY1 < 40 &&black.salientes[i+sumDX2][j+sumDY2]!=1 && isValid(i+sumDX2, j+sumDY2, M, N)) {
                            findPaths(mat, path, i+sumDX2, j+sumDY2, M, N, enTunel, black);
                        }
                    }
                } else {
                    // move X
                    if (i+sumX1 < 90 && i+sumY1 < 40 &&black.salientes[i+sumX1][j+sumY1]!=1 && isValid(i+sumX1, j+sumY1, M, N)) {
                        findPaths(mat, path, i+sumX1, j+sumY1, M, N, enTunel, black);
                    }
                    // move Y
                    if (i+sumX1 < 90 && i+sumY1 < 40 &&black.salientes[i+sumX2][j+sumY2]!=1 && isValid(i+sumX2, j+sumY2, M, N)) {
                        findPaths(mat, path, i+sumX2, j+sumY2, M, N, enTunel, black);
                    }
                }
            }
        } else {
            //pathplanning en tunel

            if ((i+sumX1 >= 0 && i+sumX1 < sizeof(black.tunel)) && (i+sumX2 >= 0 && i+sumX2 < sizeof(black.tunel))
                && (j+sumY1 >= 0 && j+sumY1 < sizeof(black.tunel[0])) && (j+sumY2 >= 0 && j+sumY2 < sizeof(black.tunel[0]))) {

                if (black.tunel[i+sumX1][j+sumY1]==1 && black.tunel[i+sumX2][j+sumY2]==1) {
                    //move diagonal 
                    if (i+sumDX1 < 90 && i+sumDY1 < 40 && black.tunel[i+sumDX1][j+sumDY1]!=1 && isValid(i+sumDX1, j+sumDY1, M, N)) {
                        findPaths(mat, path, i+sumDX1, j+sumDY1, M, N, enTunel, black);
                    }else{
                        if (i+sumDX1 < 90 && i+sumDY1 < 40 &&black.tunel[i+sumDX2][j+sumDY2]!=1 && isValid(i+sumDX2, j+sumDY2, M, N)) {
                            findPaths(mat, path, i+sumDX2, j+sumDY2, M, N, enTunel, black);
                        }
                    }
                } else {
                    // move X
                    if (i+sumX1 < 90 && i+sumY1 < 40 &&black.tunel[i+sumX1][j+sumY1]!=1 && isValid(i+sumX1, j+sumY1, M, N)) {
                        findPaths(mat, path, i+sumX1, j+sumY1, M, N, enTunel, black);
                    }
                    
                    // move Y
                    if (i+sumX1 < 90 && i+sumY1 < 40 &&black.tunel[i+sumX2][j+sumY2]!=1 && isValid(i+sumX2, j+sumY2, M, N)) {
                        findPaths(mat, path, i+sumX2, j+sumY2, M, N, enTunel, black);
                    }
                }
            }
        }

        
        // backtrack: remove the current cell from the path
        path.pop_back();
    }
    /*else
    {
        std::cout << "HA HABIDO UN ERROR.\n";
    }*/
    
}

std::vector<Casilla> PathP_t::buscar(int xIni, int yIni, int xFin, int yFin, bool enTunel, BlackboardComponent_t& black)
{     
    std::vector<Casilla> ruta;

    std::vector<int> path;
 
    // start cell (x,y) - destination cell (M,N)
    //int x = 28, y = 9;
    //int M = 23, N = 0;

    if (xIni <= xFin) {
        dirX = 1;

        if (xIni == xFin) {
            MM = xFin;
        } else {
            MM = xFin-1;
        }

        sumDX1 = -1; //diagonal X left
        sumDX2 = -1; //diagonal X left
        sumX1 = +1; //move right
        sumX2 = 0;
    } else {
        dirX = -1;

        MM = xFin+1;
        sumDX1 = +1; //diagonal X right
        sumDX2 = +1; //diagonal X right
        sumX1 = -1; //move right
        sumX2 = 0;
    }

    if (yIni <= yFin) {
        dirY = 1;

        if (yIni == yFin) {
            NN = yFin;  
        } else {
            NN = yFin-1;
        }

        sumDY1 = +1; //diagonal Y up
        sumDY2 = -1; //diagonal Y down
        sumY1 = 0;
        sumY2 = +1; //move up
    } else {
        dirY = -1;

        NN = yFin+1;
        sumDY1 = -1; //diagonal Y down
        sumDY2 = +1; //diagonal Y up
        sumY1 = 0;
        sumY2 = -1; //move down
    }

    //comprobar si start cell es distinta a final cell
    //comprobar que final cell no es saliente
    if (xIni!=xFin || yIni!=yFin) {
        if (enTunel == true) {
            if (xFin < 90 && yFin < 40 && black.tunel[xFin][yFin]!=1) {
                return ruta;
            }
        } else {
            if (xFin < 90 && yFin < 40 && black.salientes[xFin][yFin]!=1) {
                return ruta;
            }
        }

        findPaths(mat, path, xIni, yIni, xFin, yFin, enTunel, black);

        //std::cout << "Size: " << caminos.size() << "\n";

        srand (time(NULL));

        //std::cout << caminos.size() << "\n";

        if (caminos.size() > 0) {
            if (caminos.size() != 1) {
                size_t randi { rand() % caminos.size() };

                return caminos[randi];
            } else {
                return caminos[0];
            }
            
        } else {
            //std::cout << "No hay caminos\n";
            
            return ruta;
        }

        //for (int x = 0; x < caminos.size(); x++) {
        //    for (int y = 0; y < caminos[x].size(); y++) { 
        //        std::cout << "( " << caminos[x][y].x << "," << caminos[x][y].y << " ) ";
        //    }
        //    std::cout << "\n";
        //}
    } else {
        //std::cout << "Soy el destino o mi destino es saliente\n";

        return ruta;
    }
 
    return ruta;
}