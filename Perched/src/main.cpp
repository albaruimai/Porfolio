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
//# Main sirve para ejecutar el juego y detenerlo cuando ya no hay   #
//#   estados del juego vivos.                                       #
//#                                                                  #
//#                                                                  #
//####################################################################
#include "Motor3D/Motor3DLUM/Motor3DLUM.hpp"
#include "man/game.hpp"
#include "man/state.hpp"
#include "man/menus/InitMenu.hpp"
#include <iostream>
#include <memory>

int main(){
    try {
        StateManager_t States;
        States.addState<MenuState_t>(States);

        while (States.alive()) {
            States.update();
        }    
    } catch (std::exception& e) {
        //std::cout << "[[ EXCEPTION ]]: " << e.what() << "\n\n";
    } catch(...){
        //std::cout << "Capturada : \n";
    }
}