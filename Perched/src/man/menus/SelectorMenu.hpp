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
#include "../game.hpp"
#include "../../util/MyKeycodes.h"

#include <iostream>
#include <stdio.h>
#include <string>

struct GameManager_t;
struct StoryMenuState_t;

struct SelectorMenuState_t : StateBase_t {
    explicit SelectorMenuState_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h, bool newP) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h), nueva(newP) {

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

            padding = 0.0;
        } else if (wWidth == 1920 && wHeight == 1080) {
            rutaF = "assets/menus/1920x1080/menu_screen.png";
            xIni = 100;
            yIni = 400;

            xRet = 100;
            yRet = 700;

            padding = 180.0;
        }else{
            rutaF = "assets/menus/1280x720/menu_screen.png";
            xIni = 100;
            yIni = 250;

            xRet = 100;
            yRet = 400;

            padding = 0.0;
        }

        rutauno = "assets/menus/numeros/uno.png";
        rutados = "assets/menus/numeros/dosbloqued.png";
        rutatres = "assets/menus/numeros/tresbloqued.png";
        rutacuatro = "assets/menus/numeros/cuatrobloqued.png";
        rutacinco = "assets/menus/numeros/cincobloqued.png";
        rutaseis = "assets/menus/numeros/seisbloqued.png";
        rutasiete = "assets/menus/numeros/sietebloqued.png";
        rutaocho = "assets/menus/numeros/ochobloqued.png";
        rutanueve = "assets/menus/numeros/nuevebloqued.png";
        rutacero = "assets/menus/numeros/cerobloqued.png";

        SM.levelSelected = 0;

        switch (SM.lastLevelUnlocked) {
            case 1:
                rutados = "assets/menus/numeros/dos.png";
                SM.levelSelected = 1;
                break;
            case 2:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                SM.levelSelected = 2;
                break;
            case 3:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                rutacuatro = "assets/menus/numeros/cuatro.png";
                SM.levelSelected = 3;
                break;
            case 4:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                rutacuatro = "assets/menus/numeros/cuatro.png";
                rutacinco = "assets/menus/numeros/cinco.png";
                SM.levelSelected = 4;
                break;
            case 5:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                rutacuatro = "assets/menus/numeros/cuatro.png";
                rutacinco = "assets/menus/numeros/cinco.png";
                rutaseis = "assets/menus/numeros/seis.png";
                SM.levelSelected = 5;
                break;
            case 6:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                rutacuatro = "assets/menus/numeros/cuatro.png";
                rutacinco = "assets/menus/numeros/cinco.png";
                rutaseis = "assets/menus/numeros/seis.png";
                rutasiete = "assets/menus/numeros/siete.png";
                SM.levelSelected = 6;
                break;
            case 7:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                rutacuatro = "assets/menus/numeros/cuatro.png";
                rutacinco = "assets/menus/numeros/cinco.png";
                rutaseis = "assets/menus/numeros/seis.png";
                rutasiete = "assets/menus/numeros/siete.png";
                rutaocho = "assets/menus/numeros/ocho.png";
                SM.levelSelected = 7;
                break;
            case 8:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                rutacuatro = "assets/menus/numeros/cuatro.png";
                rutacinco = "assets/menus/numeros/cinco.png";
                rutaseis = "assets/menus/numeros/seis.png";
                rutasiete = "assets/menus/numeros/siete.png";
                rutaocho = "assets/menus/numeros/ocho.png";
                rutanueve = "assets/menus/numeros/nueve.png";
                SM.levelSelected = 8;
                break;
            case 9:
                rutados = "assets/menus/numeros/dos.png";
                rutatres = "assets/menus/numeros/tres.png";
                rutacuatro = "assets/menus/numeros/cuatro.png";
                rutacinco = "assets/menus/numeros/cinco.png";
                rutaseis = "assets/menus/numeros/seis.png";
                rutasiete = "assets/menus/numeros/siete.png";
                rutaocho = "assets/menus/numeros/ocho.png";
                rutanueve = "assets/menus/numeros/nueve.png";
                rutacero = "assets/menus/numeros/cero.png";
                SM.levelSelected = 9;
                break;
        }

        if (SM.wasPassed.at(1) == true) {
            rutados = "assets/menus/numeros/dos.png";
        }
        if (SM.wasPassed.at(2) == true) {
            rutatres = "assets/menus/numeros/tres.png";
        }
        if (SM.wasPassed.at(3) == true) {
            rutacuatro = "assets/menus/numeros/cuatro.png";
        }
        if (SM.wasPassed.at(4) == true) {
            rutacinco = "assets/menus/numeros/cinco.png";
        }
        if (SM.wasPassed.at(5) == true) {
            rutaseis = "assets/menus/numeros/seis.png";
        }
        if (SM.wasPassed.at(6) == true) {
            rutasiete = "assets/menus/numeros/siete.png";
        }
        if (SM.wasPassed.at(7) == true) {
            rutaocho = "assets/menus/numeros/ocho.png";
        }
        if (SM.wasPassed.at(8) == true) {
            rutanueve = "assets/menus/numeros/nueve.png";
        }
        if (SM.wasPassed.at(9) == true) {
            rutacero = "assets/menus/numeros/cero.png";
        }

        SM.myimgui.InitGui(*(Render->getMotor()->getWindow()));

        SM.myimgui.SetStyle("Dark");  
    }

    void deleteTextures() {
        glDeleteTextures(1, &mitex);

        glDeleteTextures(1, &(bReturn.img_texture));

        glDeleteTextures(1, &(bUno.img_texture));
        glDeleteTextures(1, &(bDos.img_texture));
        glDeleteTextures(1, &(bTres.img_texture));
        glDeleteTextures(1, &(bCuatro.img_texture));
        glDeleteTextures(1, &(bCinco.img_texture));
        glDeleteTextures(1, &(bSeis.img_texture));
        glDeleteTextures(1, &(bSiete.img_texture));
        glDeleteTextures(1, &(bOcho.img_texture));
        glDeleteTextures(1, &(bNueve.img_texture));
        glDeleteTextures(1, &(bCero.img_texture));
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

            bUno = SM.myimgui.CreateImageButton(rutauno, xcero, y);

            if (SM.myimgui.IsClicked() && (rutauno.find("bloqued") == std::string::npos)) {
                //std::cout << "cero\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);
                
                SM.levelSelected = 0;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding);

            bDos = SM.myimgui.CreateImageButton(rutados, xuno, y);

            if (SM.myimgui.IsClicked() && (rutados.find("bloqued") == std::string::npos)) {
                //std::cout << "uno\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 1;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*2);

            bTres = SM.myimgui.CreateImageButton(rutatres, xdos, y);

            if (SM.myimgui.IsClicked() && (rutatres.find("bloqued") == std::string::npos)) {
                //std::cout << "dos\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 2;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*3);

            bCuatro = SM.myimgui.CreateImageButton(rutacuatro, xtres, y);

            if (SM.myimgui.IsClicked() && (rutacuatro.find("bloqued") == std::string::npos)) {
                //std::cout << "tres\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 3;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*4);

            bCinco = SM.myimgui.CreateImageButton(rutacinco, xcuatro, y);

            if (SM.myimgui.IsClicked() && (rutacinco.find("bloqued") == std::string::npos)) {
                //std::cout << "cuatro\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 4;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*5);

            bSeis = SM.myimgui.CreateImageButton(rutaseis, xcinco, y);

            if (SM.myimgui.IsClicked() && (rutaseis.find("bloqued") == std::string::npos)) {
                //std::cout << "cinco\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 5;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*6);

            bSiete = SM.myimgui.CreateImageButton(rutasiete, xseis, y);

            if (SM.myimgui.IsClicked() && (rutasiete.find("bloqued") == std::string::npos)) {
                //std::cout << "seis\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 6;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*7);

            bOcho = SM.myimgui.CreateImageButton(rutaocho, xsiete, y);

            if (SM.myimgui.IsClicked() && (rutaocho.find("bloqued") == std::string::npos)) {
                //std::cout << "siete\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 7;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*8);

            bNueve = SM.myimgui.CreateImageButton(rutanueve, xocho, y);

            if (SM.myimgui.IsClicked() && (rutanueve.find("bloqued") == std::string::npos)) {
                //std::cout << "ocho\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 8;

                FinishWindow();

                return 5;
            }

            SM.myimgui.InSameLine(padding*9);

            bCero = SM.myimgui.CreateImageButton(rutacero, xnueve, y);

            if (SM.myimgui.IsClicked() && (rutacero.find("bloqued") == std::string::npos)) {
                //std::cout << "nueve\n";
                Sound->InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                Sound->update(EntityMan);

                SM.levelSelected = 9;

                FinishWindow();

                return 5;
            }

            SM.myimgui.EndWindow();

            SM.myimgui.NewWindow(xRet, yRet, 200, 200, "Prueba", false);
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
                SM.addState<GameManager_t>(SM, *Render, *Sound, wWidth, wHeight);
                break;
            case 2:
                m_alive = false;
                break;
            case 1:
                m_alive = false;
                if (nueva == true) {
                    SM.addState<StoryMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
                } else {
                    SM.addState<MainMenuState_t>(SM, *Render, *Sound, wWidth, wHeight);
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
        ButImagen bReturn;
        ButImagen bUno, bDos, bTres, bCuatro, bCinco, bSeis, bSiete, bOcho, bNueve, bCero;
        
        int wWidth, wHeight;
        std::string rutaF = "";
        std::string rutauno = "", rutados = "", rutatres = "", rutacuatro = "", rutacinco = "";
        std::string rutaseis = "", rutasiete = "", rutaocho = "", rutanueve = "",  rutacero = "";

        int xcero {200}, xuno {300}, xdos {400}, xtres {500}, xcuatro {600};
        int xcinco {700}, xseis {800}, xsiete {900}, xocho {1000}, xnueve {1100};
        int y {200};
        int xIni {100}, yIni {250};

        int xRet {100}, yRet {400};

        float padding {0.0};

        bool nueva {false};
};