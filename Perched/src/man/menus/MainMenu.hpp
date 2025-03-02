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
#include "ControlsMenu.hpp"
#include "SettingsMenu.hpp"
#include "PartidaMenu.hpp"

#include "../../util/MyKeycodes.h"

#include <iostream>
#include <stdio.h>
#include <string>

struct MainMenuState_t : StateBase_t {
    explicit MainMenuState_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h) {

        if (wWidth == 0 && wHeight == 0) {
            wWidth = 1280;
            wHeight = 720;
        }

        if (wWidth == 1280 && wHeight == 720) {
            rutaF = "assets/menus/1280x720/menu_screen_wallpaper.png";
            rutaP = "assets/menus/1280x720/playc.png";
            rutaC = "assets/menus/1280x720/controlsc.png";
            yC = 220;
            rutaS = "assets/menus/1280x720/settingsc.png";
            yS = 330;
            rutaL = "assets/menus/1280x720/logoutc.png";
            yL = 440;
        } else if (wWidth == 1920 && wHeight == 1080) {
            rutaF = "assets/menus/1920x1080/menu_screen_wallpaper.png";
            rutaP = "assets/menus/1920x1080/playc.png";
            rutaC = "assets/menus/1920x1080/controlsc.png";
            yC = 270;
            rutaS = "assets/menus/1920x1080/settingsc.png";
            yS = 430;
            rutaL = "assets/menus/1920x1080/logoutc.png";
            yL = 590;
        }else{
            rutaF = "assets/menus/1280x720/menu_screen_wallpaper.png";
            rutaP = "assets/menus/1280x720/playc.png";
            rutaC = "assets/menus/1280x720/controlsc.png";
            yC = 220;
            rutaS = "assets/menus/1280x720/settingsc.png";
            yS = 330;
            rutaL = "assets/menus/1280x720/logoutc.png";
            yL = 440;
        }

        SM.myimgui.InitGui(*(Render->getMotor()->getWindow()));

        SM.myimgui.SetStyle("Dark");  
    }

    void deleteTextures() {
        glDeleteTextures(1, &mitex);

        glDeleteTextures(1, &(bPlay.img_texture));
        glDeleteTextures(1, &(bControls.img_texture));
        glDeleteTextures(1, &(bSettings.img_texture));
        glDeleteTextures(1, &(bLogout.img_texture));
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

            SM.myimgui.NewWindow(0, 0, wWidth, wHeight, "Menu Inicio", true);
            mitex = SM.myimgui.CreateImage(rutaF);
            SM.myimgui.EndWindow(); 

            SM.myimgui.NewWindow(50, 50, wWidth/2, wHeight, "Prueba", false);

            bPlay = SM.myimgui.CreateImageButton(rutaP, x, yP);

            if (SM.myimgui.IsClicked()) {
                //std::cout << "play\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                FinishWindow();

                return 5;
            }

            bControls = SM.myimgui.CreateImageButton(rutaC, x, yC);

            if (SM.myimgui.IsClicked()) {
                //std::cout << "controls\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                Sound->update(EntityMan);

                FinishWindow();

                return 4;
            }

            bSettings = SM.myimgui.CreateImageButton(rutaS, x, yS);

            if (SM.myimgui.IsClicked()) {
                //std::cout << "settings\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                Sound->update(EntityMan);

                FinishWindow();

                return 3;
            }

            bLogout = SM.myimgui.CreateImageButton(rutaL, x, yL);

            if (SM.myimgui.IsClicked()) {
                //std::cout << "logout\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                Sound->update(EntityMan);

                FinishWindow();

                return 2;
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
                SM.addState<PartidaMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
                break;
            case 4:
                m_alive = false;
                SM.addState<ControlsMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
                break;
            case 3:
                m_alive = false;
                SM.addState<SettingsMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
                break;
            case 2:
                m_alive = false;
                SM.setAlive();
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
        ButImagen bPlay;
        ButImagen bControls;
        ButImagen bSettings;
        ButImagen bLogout;

        int wWidth, wHeight;
        std::string rutaF = "", rutaP = "", rutaC = "", rutaS = "", rutaL = "";
        int x {60}, yP {60}, yC {220}, yS {330}, yL {440};
};