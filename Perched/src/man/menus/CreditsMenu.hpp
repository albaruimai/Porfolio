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

struct CreditsMenuState_t : StateBase_t {
    explicit CreditsMenuState_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h, bool gane) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h), ganar(gane) {

        Sound->InitEvent("event:/Musica/Menus/MenuSecundario/MenuSecundario", true);
        Sound->iniciar("event:/Musica/Menus/MenuSecundario/MenuSecundario");

        //glfwGetWindowSize(Render->getMotor()->getWindow(), &wWidth, &wHeight);

        if (wWidth == 0 && wHeight == 0) {
            wWidth = 1280;
            wHeight = 720;
        }

        if (wWidth == 1280 && wHeight == 720) {
            if (ganar == true) {
                rutaF = "assets/menus/1280x720/CreditosWin.png";
            } else {
                rutaF = "assets/menus/1280x720/CreditosLost.png";
            }

            xIni = 100;
            yIni = 250;

            xHome =  50;
            yHome = 600;
        } else if (wWidth == 1920 && wHeight == 1080) {
            if (ganar == true) {
                rutaF = "assets/menus/1920x1080/CreditosWin.png";
            } else {
                rutaF = "assets/menus/1920x1080/CreditosLost.png";
            }

            xIni =  50;
            yIni = 400;

            xHome = 100;
            yHome = 900;
        }else{
            if (ganar == true) {
                rutaF = "assets/menus/1280x720/CreditosWin.png";
            } else {
                rutaF = "assets/menus/1280x720/CreditosLost.png";
            }

            xIni = 100;
            yIni = 250;

            xHome =  50;
            yHome = 600;
        }

        SM.myimgui.InitGui(*(Render->getMotor()->getWindow()));

        SM.myimgui.SetStyle("Dark");   
    }

    void deleteTextures() {
        glDeleteTextures(1, &mitex);

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

            SM.myimgui.NewFrame();

            SM.myimgui.NewWindow(-5, -5, wWidth+10, wHeight+10, "Menu Inicio", true);
            mitex = SM.myimgui.CreateImage(rutaF);
            SM.myimgui.EndWindow();

            SM.myimgui.NewWindow(xHome, yHome, 200, 200, "Prueba", false);

            bHome = SM.myimgui.CreateImageButton("assets/menus/homec.png", 0, 0);
            if (SM.myimgui.IsClicked()) {
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");

                Sound->stop("event:/Musica/Menus/MenuSecundario/MenuSecundario");
                Sound->iniciar("event:/Musica/Menus/MenuPrincipal/MenuPrincipal");
                Sound->update(EntityMan);

                FinishWindow();

                return 3;
            }
            
            FinishWindow();

            if(Render->getMotor()->getReceiver()->IsKeyDown(keys::KEY_CODE_G::KEY_ESCAPE)){
                return 5;
            }

            Sound->update(EntityMan);
        }

        return 5;
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

                if (ganar == true) {
                    SM.addState<MainMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
                } else {
                    SM.addState<SelectorMenuState_t>(SM, *Render, *Sound, wWidth, wHeight, false);
                }
                
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
        ButImagen bHome;

        int wWidth, wHeight;
        std::string rutaF = "";
        int xIni {100}, yIni {250};
        int xHome {100}, yHome {400};

        bool ganar {false};
};