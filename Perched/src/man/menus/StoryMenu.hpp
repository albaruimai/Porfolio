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
#include "SelectorMenu.hpp"
#include "../../util/MyKeycodes.h"

#include <iostream>
#include <stdio.h>
#include <string>

struct PartidaMenuState_t;

struct StoryMenuState_t : StateBase_t {
    explicit StoryMenuState_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h) {

        if (wWidth == 0 && wHeight == 0) {
            wWidth = 1280;
            wHeight = 720;
        }

        if (wWidth == 1280 && wHeight == 720) {
            rutaF = "assets/menus/1280x720/menu_screen.png";
            xIni = 100;
            yIni = 250;

            xRet = 100;
            yRet = 300;

            start = "assets/menus/1280x720/start.png"; 

        } else if (wWidth == 1920 && wHeight == 1080) {
            rutaF = "assets/menus/1920x1080/menu_screen.png";
            xIni = 100;
            yIni = 400;

            xRet = 100;
            yRet = 500;

            start = "assets/menus/1920x1080/start.png"; 
        }else{
            rutaF = "assets/menus/1280x720/menu_screen.png";
            xIni = 100;
            yIni = 250;

            xRet = 100;
            yRet = 300;

            start = "assets/menus/1280x720/start.png"; 
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


            SM.myimgui.NewWindow(xIni, yIni, wWidth, wHeight, "Prueba", false);
            SM.myimgui.CreateText("¡Oh no! Mis crías han sido raptadas.");
            SM.myimgui.CreateText("Esa gran águila se las ha llevado a la cima.");
            SM.myimgui.CreateText("¡Debo rescatarlas!");
            SM.myimgui.CreateText("Me tocará escalar esta gran montaña...");
            //SM.myimgui.CreateText("Un domingo como cualquier otro...");
            //SM.myimgui.CreateText("Zacarias junto con sus crias se fue a la montaña");
            //SM.myimgui.CreateText("y mientras hacían un picnic, Zacarias se despistó,");
            //SM.myimgui.CreateText("vinieron las águilas y se llevaron a sus crías.");
            //SM.myimgui.CreateText("Zacarías dejó la mochila y se aventuró a subir");
            //SM.myimgui.CreateText("la montaña para rescatarlas.");
            //myimgui.CreateText("Esta es la historia de Zacarias...");

            SM.myimgui.EndWindow();

            SM.myimgui.NewWindow(xRet, yRet, 200, 200, "Prueba", false);

            bJugar = SM.myimgui.CreateImageButton(start, 0, 0);
            if (SM.myimgui.IsClicked()) {
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(800.0);

            bReturn = SM.myimgui.CreateImageButton("assets/menus/returnc.png", 0, 0);
            if (SM.myimgui.IsClicked()) {
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                Sound->update(EntityMan);

                FinishWindow();

                return 1;
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
                SM.addState<SelectorMenuState_t>(SM, *Render, *Sound, wWidth, wHeight, true);
                break;
            case 2:
                m_alive = false;
                break;
            case 1:
                m_alive = false;
                SM.addState<PartidaMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
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
        ButImagen bJugar;
        
        int wWidth, wHeight;
        std::string rutaF = "";
        std::string start = "";
        int xIni {100}, yIni {250};
        int xRet {100}, yRet {400};
};