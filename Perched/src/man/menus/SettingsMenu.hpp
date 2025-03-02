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

struct SettingsMenuState_t : StateBase_t {
    explicit SettingsMenuState_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h) {

        if (wWidth == 0 && wHeight == 0) {
            wWidth = 1280;
            wHeight = 720;
        }

        SM.myimgui.InitGui(*(Render->getMotor()->getWindow()));

        SM.myimgui.SetStyle("Dark");

        Checkactivo = SM.volActivo;
        mitadMusic = SM.mitadMusic;
        mitadEffects = SM.mitadEffects;
        item_current_combo = SM.posReso; 

        changeParameters();
        
        if(Render->getMotor()->Menusombras==true){
            Sombactivo=true;
        }else{
            Sombactivo=false;
        }
        if(Render->getMotor()->Menunubes==true){
            Nubesactivo=true;
        }else{
            Nubesactivo=false;
        }
        if(Render->getMotor()->Menuparticulas==true){
            Particulasactivo=true;
        }else{
            Particulasactivo=false;
        }
    }

    void changeParameters() {
        if (wWidth == 1280 && wHeight == 720) {
            rutaF = "assets/menus/1280x720/menu_screen.png";
            xIni = 100;
            yIni = 200;

            xRet = 700;
            yRet = 400;
        } else if (wWidth == 1920 && wHeight == 1080) {
            rutaF = "assets/menus/1920x1080/menu_screen.png";
            xIni = 100;
            yIni = 350;

            xRet = 700;
            yRet = 700;
        }else{
            rutaF = "assets/menus/1280x720/menu_screen.png";
            xIni = 100;
            yIni = 200;

            xRet = 700;
            yRet = 400;
        }
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


            SM.myimgui.NewWindow(xIni, yIni, (wWidth/2)+60, wHeight-200, "Prueba", false);
            SM.myimgui.CreateText("");

            if(SM.myimgui.CollapsingHeader("Opciones Sonido")){
                Checkactivo = SM.myimgui.CreateCheckbox("Sonido activo", Checkactivo);

                if (Checkactivo) {
                    if (Vactivado == false) {
                        Sound->activarVolumen();

                        Vactivado = true;
                        Vdesactivado = false;
                    }

                    mitadMusic = SM.myimgui.CreateSliderInt("Volumen Musica", mitadMusic, 0, 100);
                    
                    Sound->changeVolumen(mitadMusic / 100.0, true);

                    mitadEffects = SM.myimgui.CreateSliderInt("Volumen Efectos", mitadEffects, 0, 100);

                    Sound->changeVolumen(mitadEffects / 100.0, false);
                } else {
                    if (Vdesactivado == false) {
                        Sound->desactivarVolumen();

                        Vactivado = false;
                        Vdesactivado = true;
                    }                
                }

            }
            
            if(SM.myimgui.CollapsingHeader("Opciones Graficas")){
                Sombactivo = SM.myimgui.CreateCheckbox("Sombras", Sombactivo);

                if (Sombactivo) {
                    Render->getMotor()->Menusombras=true;
                } else {
                    Render->getMotor()->Menusombras=false;               
                }

                Nubesactivo = SM.myimgui.CreateCheckbox("Nubes", Nubesactivo);

                if (Nubesactivo) {
                    Render->getMotor()->Menunubes=true;
                } else {
                    Render->getMotor()->Menunubes=false;               
                }

                Particulasactivo = SM.myimgui.CreateCheckbox("Particulas", Particulasactivo);

                if (Particulasactivo) {
                    Render->getMotor()->Menuparticulas=true;
                    Render->getMotor()->enableParticleSys();
                } else {
                    Render->getMotor()->Menuparticulas=false;
                    Render->getMotor()->disableParticleSys();              
                }

                std::vector<std::string> items {"Full Screen", "1280x720", "1920x1080"};
                
                item_current_combo = SM.myimgui.CreateCombo("Elige resolucion", item_current_combo, items);

                if (item_current_combo == 0) {
                    auto* monitor {glfwGetPrimaryMonitor()};
                    const auto* mode {glfwGetVideoMode(monitor)};
                    if(mode!=nullptr){
                        wWidth = mode->width;
                        wHeight = mode->height; 
                        changeParameters();
                        glfwSetWindowMonitor(Render->getMotor()->getWindow(), monitor,  0, 0, wWidth, wHeight, mode->refreshRate );
                        glfwSetWindowSize(Render->getMotor()->getWindow(), wWidth, wHeight);
                        Render->getMotor()->framebuffer_size_callback(Render->getMotor()->getWindow(), wWidth, wHeight);
                        Render->getMotor()->setFramebuffer();
                    }
                }

                if (item_current_combo == 1) {
                    wWidth = 1280;
                    wHeight = 720; 
                    changeParameters();
                    glfwSetWindowMonitor(Render->getMotor()->getWindow(), NULL,  0, 0, wWidth, wHeight, 0 );
                    glfwSetWindowSize(Render->getMotor()->getWindow(), wWidth, wHeight);
                    Render->getMotor()->framebuffer_size_callback(Render->getMotor()->getWindow(), wWidth, wHeight);
                    Render->getMotor()->setFramebuffer();
                }

                if (item_current_combo == 2) {
                    wWidth = 1920;
                    wHeight = 1080; 
                    changeParameters();
                    glfwSetWindowMonitor(Render->getMotor()->getWindow(), NULL,  0, 0, wWidth, wHeight, 0 );
                    glfwSetWindowSize(Render->getMotor()->getWindow(), wWidth, wHeight);
                    Render->getMotor()->framebuffer_size_callback(Render->getMotor()->getWindow(), wWidth, wHeight);
                    Render->getMotor()->setFramebuffer();
                }
            }

            bReturn = SM.myimgui.CreateImageButton("assets/menus/returnc.png", 0, 0);

            if (SM.myimgui.IsClicked()) {
                Sound->InitEvent("event:/Musica/Menus/Botones/Atras/BotonAtras", false);
                Sound->iniciar("event:/Musica/Menus/Botones/Atras/BotonAtras");
                Sound->update(EntityMan);

                SM.volActivo = Checkactivo;
                SM.mitadMusic = mitadMusic;
                SM.mitadEffects = mitadEffects;
                SM.posReso = item_current_combo;

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

        ButImagen bReturn;
        GLuint mitex;
        
        int wWidth, wHeight;
        std::string rutaF = "";
        int xIni {100}, yIni {250};
        int xRet {700}, yRet {400};

        bool Vactivado { true }, Vdesactivado { false };

        bool Checkactivo {true};       
        bool Sombactivo {false};
        bool Nubesactivo {false};
        bool Particulasactivo {false};
        int mitadMusic {100}, mitadEffects {100};
        int item_current_combo = 0;
        int e = 0;
};