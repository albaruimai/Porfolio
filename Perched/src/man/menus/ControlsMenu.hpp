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
#include "MainMenu.hpp"
#include "../../util/MyKeycodes.h"

#include <iostream>
#include <stdio.h>
#include <string>

struct MainMenuState_t;

struct ControlsMenuState_t : StateBase_t {
    explicit ControlsMenuState_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h) {

        if (wWidth == 0 && wHeight == 0) {
            wWidth = 1280;
            wHeight = 720;
        }

        if (wWidth == 1280 && wHeight == 720) {
            rutaF = "assets/menus/1280x720/menu_screen_controls.png";
            xIni = 100;
            yIni = 250;

            xRet = 100;
            yRet = 550;
        } else if (wWidth == 1920 && wHeight == 1080) {
            rutaF = "assets/menus/1920x1080/menu_screen_controls.png";
            xIni = 100;
            yIni = 400;

            xRet = 100;
            yRet = 800;
        }else{
            rutaF = "assets/menus/1280x720/menu_screen_controls.png";
            xIni = 100;
            yIni = 250;

            xRet = 100;
            yRet = 550;
        }

        SM.myimgui.InitGui(*(Render->getMotor()->getWindow()));

        SM.myimgui.SetStyle("Dark"); 
    }

    void deleteTextures() {
        glDeleteTextures(1, &mitex);

        glDeleteTextures(1, &(bReturn.img_texture));
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

            SM.myimgui.NewWindow(xRet, yRet, 200, 200, "Prueba", false);
            bReturn = SM.myimgui.CreateImageButton("assets/menus/returnc.png", 0, 0);

            if (SM.myimgui.IsClicked()) {
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                Sound->update(EntityMan);

                FinishWindow();

                return 5;
            }

            FinishWindow();

            if (Render->getMotor()->getReceiver()->IsKeyDown(keys::KEY_CODE_G::KEY_ESCAPE)) {
                return 2;
            }

            Sound->update(EntityMan);
        }

        return 2;
    }

    void update() final {
        Render->getMotor()->beginScene();

        int valor = run();

        Render->getMotor()->run();        

        Render->getMotor()->endScene();

        switch (valor) {
            case 5:
                m_alive = false;
                SM.addState<MainMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
                break;
            case 2:
                m_alive = false;
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
        ButImagen bReturn;

        int wWidth, wHeight;
        std::string rutaF = "";
        int xIni {100}, yIni {250};
        int xRet {100}, yRet {400};
};