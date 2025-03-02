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
//# Keyboard sirve para almacenar las teclas que se pueden pulsar    #
//#   y gestionar las pulsaciones de teclado.                        #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include "../util/MyKeycodes.h"
#include "../Motor3D/Motor3DLUM/Motor3DLUM.hpp"

#include <unordered_map>
#include <optional>

namespace ECS {
    struct Keyboard_t {
        using OpIter = std::optional<std::unordered_map<keys::KEY_CODE_G, bool>::iterator>;

        explicit Keyboard_t() = default;

        Keyboard_t(const Keyboard_t&) = delete;
        Keyboard_t(Keyboard_t&&) = delete;
        Keyboard_t& operator=(const Keyboard_t&) = delete;
        Keyboard_t& operator=(Keyboard_t&&) = delete;

        bool isKeyPressed (keys::KEY_CODE_G k, EventReceiver* receiver) noexcept;

        void keyPressed(keys::KEY_CODE_G k) noexcept {
            auto it = getIterator(k);

            if (it) {
                (*it)->second = true;
            }
        }

        void keyReleased(keys::KEY_CODE_G k) noexcept {
            auto it = getIterator(k);

            if (it) {
                (*it)->second = false;
            }
        }

        void reset() noexcept {
            for (auto& [_ , st] : m_pressedKeys) {
                st = false;
            }
        }

        private:
            OpIter getIterator(keys::KEY_CODE_G k) noexcept;

            std::unordered_map<keys::KEY_CODE_G, bool> m_pressedKeys {

                {keys::KEY_CODE_G::KEY_ESCAPE, false},
                {keys::KEY_CODE_G::KEY_A, false},
                {keys::KEY_CODE_G::KEY_B, false},
                {keys::KEY_CODE_G::KEY_C, false},            
                {keys::KEY_CODE_G::KEY_D, false},            
                {keys::KEY_CODE_G::KEY_E, false},            
                {keys::KEY_CODE_G::KEY_F, false},            
                {keys::KEY_CODE_G::KEY_G, false},            
                {keys::KEY_CODE_G::KEY_H, false},            
                {keys::KEY_CODE_G::KEY_I, false},            
                {keys::KEY_CODE_G::KEY_J, false},            
                {keys::KEY_CODE_G::KEY_K, false},            
                {keys::KEY_CODE_G::KEY_L, false},            
                {keys::KEY_CODE_G::KEY_M, false},            
                {keys::KEY_CODE_G::KEY_N, false},            
                {keys::KEY_CODE_G::KEY_O, false},            
                {keys::KEY_CODE_G::KEY_P, false},            
                {keys::KEY_CODE_G::KEY_Q, false},            
                {keys::KEY_CODE_G::KEY_R, false},            
                {keys::KEY_CODE_G::KEY_S, false},            
                {keys::KEY_CODE_G::KEY_T, false},            
                {keys::KEY_CODE_G::KEY_U, false},            
                {keys::KEY_CODE_G::KEY_V, false},            
                {keys::KEY_CODE_G::KEY_W, false},            
                {keys::KEY_CODE_G::KEY_X, false},            
                {keys::KEY_CODE_G::KEY_Y, false},            
                {keys::KEY_CODE_G::KEY_Z, false},
                {keys::KEY_CODE_G::KEY_SPACE, false}
            };
    };
}