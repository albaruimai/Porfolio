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

#include <thread>
#include <iostream>
#include <stdio.h>
#include <string>

static bool s_Finished { false };

struct MenuState_t : StateBase_t {

    explicit MenuState_t(StateManager_t& sm) : SM(sm) {
        SM.myimgui.InitGuiWithContext(*(render.getMotor()->getWindow()));
        SM.myimgui.SetStyle("Dark");     

        glfwGetWindowSize(render.getMotor()->getWindow(), &wWidth, &wHeight);

        if (wWidth == 0 && wHeight == 0) {
            wWidth = 1280;
            wHeight = 720;
        }  

        if (wWidth == 1280 && wHeight == 720) {
            rutaF = "assets/menus/1280x720/menu_screen_key_3dc.png";
        } else if (wWidth == 1920 && wHeight == 1080) {
            rutaF = "assets/menus/1920x1080/menu_screen_key_3dc.png";
        }else{
            rutaF = "assets/menus/1280x720/menu_screen_key_3dc.png";
        }


        std::vector<std::string> rutas { 
            "assets/animaciones/animacionesZacarias/escalar/",
            "assets/animaciones/animacionesZacarias/zarilado/",
            "assets/animaciones/animacionesZacarias/caminar/", 
            "assets/animaciones/animacionesZacarias/caminarizq/", 
            "assets/animaciones/animacionesZacarias/cavar/", 
            "assets/animaciones/animacionesZacarias/zarienganche/",
            /*"assets/animaciones/animacionesZacarias/muerte/",*/
            "assets/animaciones/animacionesZacarias/saltofinalbueno/",
            "assets/animaciones/animacionesZacarias/danyo/",
            "assets/animaciones/aguilibig/",
            "assets/animaciones/cabrabig/",
            "assets/animaciones/ganchoselec/",
            "assets/animaciones/ganchoselec/",
            "assets/animaciones/ganchoselec/",
            "assets/animaciones/ganchoselec/",
            "assets/animaciones/ganchoselec/",
            "assets/animaciones/aranya/",
            "assets/animaciones/aranya/",
            "assets/animaciones/aranya/"
        };

        render.getMotor()->setMapAnimatonSize(rutas.size());

        std::vector<std::string> nombres { 
            "escalada", "lateral", "caminarD", "caminarI", "cavar", "cuerda", 
            /*"muerte",*/ "saltoVictoria", "danyo", "aguila", "cabra", "gancho0", 
            "gancho1", "gancho2", "gancho3", "gancho4", "aranya0", "aranya1", "aranya2"
        };
                                //  Esc  Lat  caD  caI  cav  cu   muer    sV  dan  ag ca g0 g1 g2 g3 g4 a0 a1 a2
        std::vector<int> framesIni {251, 203, 113, 113, 100, 58, /*110,*/ 80, 110, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        std::vector<int> dist {4, 2, 4, 4, 2, 1, /*1,*/ 2, 2, 4, 4, 1, 1, 1, 1, 1, 2, 2, 2};

        sound.InitEvent("event:/Musica/Menus/MenuPrincipal/MenuPrincipal", true);
        sound.iniciar("event:/Musica/Menus/MenuPrincipal/MenuPrincipal");

        std::vector<std::string> rutasLoading { 
            "assets/menus/1920x1080/loading.png",
            "assets/menus/1920x1080/loading1.png",
            "assets/menus/1920x1080/loading2.png",
            "assets/menus/1920x1080/loading3.png"
        };

        int contAni {0};
        int aux {0};
        while(!s_Finished){
            if(aux>=rutasLoading.size()){aux = 0;}
            auto* sprite { render.getMotor()->create2dSprite(rutasLoading[aux],glm::vec2(0,0), render.getMotor()->getWindowSize()) };

            render.getMotor()->beginScene();
            render.getMotor()->drawAll();
            render.getMotor()->endScene();

            render.getMotor()->loadAnimation(rutas[contAni], nombres[contAni], framesIni[contAni], dist[contAni]);
            ++aux;
            ++contAni;
            if(contAni==rutas.size()){
                s_Finished = true;
            }
            render.getMotor()->removeSprite(sprite);
        }

    }

    void deleteTextures() {
        glDeleteTextures(1, &mitex);
    }

    int run(){
        // Main loop
        while (render.getMotor()->run())
        {
            glfwPollEvents();

            SM.myimgui.NewFrame();

            SM.myimgui.NewWindow(0, 0, wWidth, wHeight, "Menu Inicio", false);
            mitex = SM.myimgui.CreateImage(rutaF);
            
            if (SM.myimgui.IsClicked()) {
                sound.InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                sound.iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                sound.update(EntityMan);

                deleteTextures();

                SM.myimgui.EndWindow();

                SM.myimgui.Render(*(render.getMotor()->getWindow()));

                return 5;
            }

            SM.myimgui.EndWindow();

            SM.myimgui.Render(*(render.getMotor()->getWindow()));

            for (size_t i {0}; i<keys::KEY_CODE_G::KEY_LAST; ++i) {
                if(render.getMotor()->getReceiver()->IsKeyDown((keys::KEY_CODE_G) i)){
                    if (((keys::KEY_CODE_G) i) != keys::KEY_CODE_G::KEY_ESCAPE) {
                        sound.InitEvent("event:/Musica/Menus/Botones/Adelante/BotonAdelante", false);
                        sound.iniciar("event:/Musica/Menus/Botones/Adelante/BotonAdelante");
                        sound.update(EntityMan);

                        deleteTextures();

                        return 5;
                    } else {
                        return 3;
                    }                   
                }
            }

            deleteTextures();

            sound.update(EntityMan);
        }

        return 3;
    }

    void update() final {
        render.getMotor()->beginScene();

        int valor { run() };

        render.getMotor()->run();        

        render.getMotor()->endScene();

        switch (valor) {
            case 5:
                m_alive = false;
                //SM.addState<GameManager_t>(SM, render, sound, wWidth, wHeight);
                SM.addState<MainMenuState_t>(SM, render, sound, wWidth, wHeight);
                break;
            case 3:
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
        RenderSystem_t<ECS::EntityManager_t> render{1280,720};
        SoundSystem_t<ECS::EntityManager_t> sound {};

        GLuint mitex;

        int wWidth, wHeight;
        std::string rutaF {""};
};