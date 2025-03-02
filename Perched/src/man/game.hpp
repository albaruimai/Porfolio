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
//# Game contiene todos los sistemas y se encarga de hacer los       #
//#   updates y de crear el nivel.                                   #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include <iostream>
#include <cstdint>
#include <memory>
#include <thread> 
#include <chrono>
#include <string_view>
#include <vector>

#include "menus/CreditsMenu.hpp"
#include "menus/PauseMenu.hpp"

#include "../sys/input.cpp"
#include "../sys/physics.cpp"
#include "../sys/colission.cpp"
#include "../sys/ia.cpp"
#include "../sys/health.cpp"
#include "../sys/camera.cpp"
#include "../sys/hud.cpp"
#include "../sys/follow.cpp"
#include "../sys/stamina.cpp"
#include "../sys/blackboard.cpp"
//#include "../sys/sound.cpp"

#include "../cmp/hud.hpp"
#include "../cmp/ia.hpp"

//#include "../man/state.hpp"
#include "../man/entitymanager.hpp"

#include "../util/gameobjectfactory.hpp"

#include "../util/bt/node.hpp"
#include "../util/bt/ACTarrive.hpp"
#include "../util/bt/ACTseek.hpp"
#include "../util/bt/nodesequence.hpp"
#include "../util/bt/nodeselector.hpp"
#include "../util/bt/checktype.hpp"
#include "../util/bt/behaviourtree.hpp"
#include "../util/bt/change_target_from_init.hpp"
#include "../util/bt/throw_object.hpp"
#include "../util/bt/choose_action.hpp"
#include "../util/bt/check_action.hpp"
#include "../util/bt/apply_goal_value.hpp"
#include "../util/bt/seek_one_axis.hpp"
#include "../util/bt/search_target.hpp"
#include "../util/bt/do_action.hpp"
#include "../util/bt/reset_wait.hpp"
#include "../util/bt/check_see_player.hpp"
#include "../util/bt/drop_object.hpp"
#include "../util/bt/create_terremoto.hpp"
#include "../util/bt/stop.hpp"
#include "../util/bt/negateNode.hpp"
#include "../util/bt/change_init_from_pos.hpp"
#include "../util/bt/change_target_relative.hpp"
#include "../util/bt/change_target_to_player.hpp"

#include "../util/gob/goal.hpp"

#include "../util/timer.hpp"

struct GameManager_t : StateBase_t {
    explicit GameManager_t(StateManager_t& sm, RenderSystem_t<ECS::EntityManager_t>& render, SoundSystem_t<ECS::EntityManager_t>& sound, int w, int h) 
        : SM(sm), Render(&render), Sound(&sound), wWidth(w), wHeight(h) {
        Render->setDebugDraw(true);

        SM.volverSonidos = true;
        Sound->stop("event:/Musica/Menus/MenuPrincipal/MenuPrincipal");

        levelAct = SM.levelSelected;

        if (wWidth == 1280 && wHeight == 720) {
            cartelGrande = false;
            xCartel = 517;
            yCartel = 571;
            wCartel = 245;
            hCartel = 149;
        } else if (wWidth == 1920 && wHeight == 1080) {
            cartelGrande = true;
            xCartel = 715;
            yCartel = 782;
            wCartel = 490;
            hCartel = 298;
        }else{
            cartelGrande = false;
            xCartel = 517;
            yCartel = 571;
            wCartel = 245;
            hCartel = 149;
        }

        auto& ca = GOFact.createCamera(0, 30, 640, 360);
        createBT(&tree1);
        
        createNextLevel();     
    }

    void createActionsIA();

    void update() final { 
        GameTimer_t timer;

        if (SM.volverSonidos == true) {
            Sound->noreproducir = false;
            
            for (auto& sou: EntityMan.getComponents<SoundComponent_t>()) {
                //-1 no init, 0 init, 1 play, 2 stop

                switch (sou.antes_pausa) {
                    case -1:
                        break;
                    case 0:
                        sou.marked_for_init = 1;
                        break;
                    case 1:
                        sou.marked_for_play = 1;
                        break;
                    case 2:
                        sou.marked_for_stop = 1;
                        break;
                }
            }

            SM.volverSonidos = false;
        }

        //bucle del juego
        //timedCall( "CAM", [&]() { Camera.update( EntityMan ); } );

        if (SM.reset == true) {
            resetAll();
            levelAct = SM.levelSelected;
            createNextLevel(); 
            SM.reset = false;
        }

        if (contCartel > 0 && contCartel < 120) {
            ++contCartel;
        } else {
            if(cartelnivel!=nullptr){
                Render->getMotor()->removeSprite(cartelnivel);
                cartelnivel = nullptr;
                contCartel = 0; 
            }
        }
        
        bool renderi = Render->update(EntityMan);
        GOFact.createTerremoto();
        bool inputi = Input.update(EntityMan, Render->getMotor());
        BlackBoard.update(EntityMan);
        Physics.update(EntityMan);
        bool iai = IA.update(EntityMan, Render->getMotor());
        Collision.update(EntityMan, Render->getMotor());

        ponerTeclaE();
        ponerTuto();

        Camera.update(EntityMan);
        
        Follow.update(EntityMan);        
        Health.update(EntityMan, Render->getMotor());        
        Stamina.update(EntityMan);
        Hud.setCrias(Collision.getCrias(EntityMan));
        Hud.update(EntityMan);

        timer.waitX_ns(MSPF);

        if (Render->getMotor()->run() == false || Input.isKeyPressed(keys::KEY_CODE_G::KEY_ESCAPE)) {
            resetAll();

            m_playing = false;

            return; 
        }

        if (Input.isKeyPressed(keys::KEY_CODE_G::KEY_P) || EntityMan.getBlackBoard().pulsoPauseMando == true) {
            ponerPause();
        }

        if (Collision.getMeta(EntityMan) == true) {
            auto& bb = EntityMan.getBlackBoard();

            if (Collision.getCrias(EntityMan) == bb.criasennivel-1) {
                //std::cout << "You win\n";
                //std::cout << "Crias rescatadas: " << Collision.getCrias(EntityMan) << "\n";

                Collision.setMeta(EntityMan, false);
                Collision.resetCrias(EntityMan);

                animWin();

                resetAll();

                createNextLevel();
            } else {
                //std::cout << "You lost\n";
                //std::cout << "Crias rescatadas: " << Collision.getCrias(EntityMan) << "\n";

                resetAll();
                
                m_playing = false;

                finishSoundGame();

                SM.addState<CreditsMenuState_t>(SM, *Render, *Sound, wWidth, wHeight, false);   
            }            
        }

        if (renderi==false || inputi==false /*|| Input.isKeyPressed(keys::KEY_CODE::KEY_ESCAPE)*/) {
            //std::cout << "You lost\n";
            //std::cout << "Crias rescatadas: " << Collision.getCrias(EntityMan) << "\n";

            resetAll();
            
            m_playing = false;

            finishSoundGame();

            SM.addState<CreditsMenuState_t>(SM, *Render, *Sound, wWidth, wHeight, false);        
        }

        if(Input.isKeyPressed(keys::KEY_CODE_G::KEY_E) || EntityMan.getBlackBoard().pulsoInteractMando == true){
            int quesubirbajar = Collision.checkAgujeros(EntityMan, 0);

            if (quesubirbajar != 0) {
                animCavar();

                Physics.addTunel(EntityMan);
                int subobajo = Physics.comprobarTunel(quesubirbajar, EntityMan);

                switch (subobajo) {
                    case 1:
                        Sound->stop("event:/Musica/Juego/MusicaJuego");
                        break;
                    case 2:
                        Sound->iniciar("event:/Musica/Juego/MusicaJuego");
                        break;
                }
            }
        }else{
            Physics.resetTunel(EntityMan);
        }


        Sound->update(EntityMan);
    }

    bool alive() final {
        return m_playing;
    }
    
    void createBT(BehaviourTree_t* tree);

    void clearHud();

    private:
        void ponerTeclaE();
        void ponerTuto();
        void ponerPause();

        void animWin();
        void animCavar();

        void resetAll();
        

        void finishSoundGame();

        void createThings();
        void createCartel(int level);

        void createNextLevel();
        void createLevelX(int level);

        static constexpr uint32_t ScreenWidth {1280};
        static constexpr uint32_t ScreenHeight {720};
        static constexpr uint64_t FPS { 60 };
        static constexpr uint64_t MSPF { 1000000000/FPS };

        ECS::EntityManager_t EntityMan;


        BehaviourTree_t tree1;

        std::vector<Action_t> action_container;

        //Creacion de sistemas
        RenderSystem_t<ECS::EntityManager_t> *Render;
        InputSystem_t<ECS::EntityManager_t> Input {Render->getMotor()};
        BlackBoardSystem_t<ECS::EntityManager_t> BlackBoard {};
        PhysicsSystem_t<ECS::EntityManager_t> Physics {};
        ColissionSystem_t<ECS::EntityManager_t> Collision{0, 0, 0, 0};
        CameraSystem_t<ECS::EntityManager_t> Camera {};
        HealthSystem_t<ECS::EntityManager_t> Health {};
        HudSystem_t<ECS::EntityManager_t> Hud {};
        FollowSystem_t<ECS::EntityManager_t> Follow {};
        StaminaSystem_t<ECS::EntityManager_t> Stamina{};
        GameObjectFactory_t GOFact { EntityMan , Render->getMotor()};
        IASystem_t<ECS::EntityManager_t> IA {&GOFact};
        SoundSystem_t<ECS::EntityManager_t> *Sound;
        
        bool m_playing { true };
        StateManager_t& SM;

        int wWidth, wHeight;

        uint8_t levelAct {0}, numlevels {10};
        std::string rutaLevel {""};

        int fpsSalto {0}, fpsCavar {0};

        SpriteRenderer* teclaE { nullptr };
        bool borradaE { true };
        int cercaAgujero { 0 };


        SpriteRenderer* tuto { nullptr };
        bool borradaTuto {true};

        SpriteRenderer* cartelnivel { nullptr };
        bool cartelGrande { false };
        std::string rutaCartel {""};
        int contCartel {0};
        int xCartel {0}, yCartel {0}, wCartel {0}, hCartel {0};
};