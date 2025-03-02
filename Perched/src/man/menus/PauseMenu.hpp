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
#include "../state.hpp"
#include "../../util/MyKeycodes.h"

#include <iostream>
#include <stdio.h>
#include <string>

struct GameManager_t;

struct PauseMenuState_t : StateBase_t {
    explicit PauseMenuState_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h, GameObjectFactory_t*gof) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h), gof_{gof}{
        Sound->InitEvent("event:/Musica/Menus/MenuPausa/MenuPausa", true);
        Sound->iniciar("event:/Musica/Menus/MenuPausa/MenuPausa");

        if (wWidth == 0 && wHeight == 0) {
            wWidth = 1280;
            wHeight = 720;
        }

        if (wWidth == 1280 && wHeight == 720) {
            rutaF = "assets/menus/1280x720/menu_screen.png";
            xIni = 100;
            yIni = 250;

            xRet = 100;
            yRet = 400;


            rutaG = "assets/menus/1280x720/save_game.png";
        } else if (wWidth == 1920 && wHeight == 1080) {
            rutaF = "assets/menus/1920x1080/menu_screen.png";
            xIni = 100;
            yIni = 400;

            xRet = 100;
            yRet = 700;

            rutaG = "assets/menus/1920x1080/save_game.png";
        }else{
            rutaF = "assets/menus/1280x720/menu_screen.png";
            xIni = 100;
            yIni = 250;

            xRet = 100;
            yRet = 400;


            rutaG = "assets/menus/1280x720/save_game.png";
        }


        SM.myimgui.InitGui(*(Render->getMotor()->getWindow()));

        SM.myimgui.SetStyle("Dark");  
    }

    void deleteTextures() {
        glDeleteTextures(1, &mitex);

        glDeleteTextures(1, &(boton.img_texture));

        glDeleteTextures(1, &(bReturn.img_texture));

        glDeleteTextures(1, &(bHome.img_texture));
    }

    void FinishWindow() {
        SM.myimgui.EndWindow();

        // Rendering
        SM.myimgui.Render(*(Render->getMotor()->getWindow()));

        deleteTextures();
    }

    int run(){      
        // Main loop
        while (Render->getMotor()->run())
        {
            glfwPollEvents();

            // Start the Dear ImGui frame
            SM.myimgui.NewFrame();

            SM.myimgui.NewWindow(0, 0, wWidth, wHeight, "Menu Inicio", true);
            mitex = SM.myimgui.CreateImage(rutaF);
            SM.myimgui.EndWindow();


            SM.myimgui.NewWindow(xIni, yIni, wWidth, wHeight, "Prueba", false);
//            boton = SM.myimgui.CreateImageButton(rutaG, x, y);
//
//            if (SM.myimgui.IsClicked()) {
//                //SM.guardarPartida();
//
//                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
//                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
//                Sound->update(EntityMan);
//            }

            SM.myimgui.CreateText("Tomate un descansito...");
            SM.myimgui.CreateText("y cuando quieras vuelve.");

            SM.myimgui.EndWindow();

            SM.myimgui.NewWindow(xRet, yRet, 200, 200, "Prueba", false);
            bHome = SM.myimgui.CreateImageButton("assets/menus/homec.png", 100, 500);
            if (SM.myimgui.IsClicked()) {
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                
                Sound->stop("event:/Musica/Juego/MusicaJuego");
                Sound->stop("event:/Musica/Menus/MenuPausa/MenuPausa");
                Sound->iniciar("event:/Musica/Menus/MenuPrincipal/MenuPrincipal");
                Sound->update(EntityMan);
                FinishWindow();

                return 1;
            }

            SM.myimgui.InSameLine(400.0);

            bReturn = SM.myimgui.CreateImageButton("assets/menus/returnc.png", 100, 500);
            if (SM.myimgui.IsClicked()) {
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                
                Sound->stop("event:/Musica/Menus/MenuPausa/MenuPausa");
                Sound->InitEvent("event:/Musica/Juego/MusicaJuego", true);
                Sound->iniciar("event:/Musica/Juego/MusicaJuego");
                Sound->update(EntityMan);

                SM.volverSonidos = true;
                gof_->createHud();

                FinishWindow();

                return 5;
            }
            
            FinishWindow();

            if(Render->getMotor()->getReceiver()->IsKeyDown(keys::KEY_CODE_G::KEY_ESCAPE)){
                return 3;
            }

            Sound->update(EntityMan);
        }

        return 3;
    }

    void update() final {
        Render->getMotor()->beginScene();

        int valor = run();

        Render->getMotor()->run();        

        Render->getMotor()->endScene();

        switch (valor) {
            case 5:
                m_alive = false;
                break;
            case 3:
                m_alive = false;
                SM.setAlive();
                break;
            case 1:
                m_alive = false;
                SM.reset = true;
                SM.addState<MainMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
                break; 
        }
    }

    bool alive() final {
        return m_alive;
    }

    private:
        bool m_alive { true };
        StateManager_t& SM;
        
        ECS::EntityManager_t EntityMan;
        RenderSystem_t<ECS::EntityManager_t> *Render;
        SoundSystem_t<ECS::EntityManager_t> *Sound;

        GLuint mitex;
        ButImagen boton, bHome, bReturn;

        int wWidth, wHeight;
        std::string rutaF = "";
        std::string rutaG = "";
        int xIni {100}, yIni {250};
        int x {200}, y {200};
        int xRet {100}, yRet {400};
        StateBase_t * game_;
        GameObjectFactory_t*gof_;
};