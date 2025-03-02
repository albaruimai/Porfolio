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

#include "input.hpp"
  
//template <typename GameCTX_t>
//InputSystem_t<GameCTX_t>::InputSystem_t() {
//    ptc_set_on_keypress( onkeypress );
//    ptc_set_on_keyrelease( onkeyrelease );
//
//    ms_Keyboard.reset();
//}

template <typename GameCTX_t>
InputSystem_t<GameCTX_t>::InputSystem_t(Motor3DLUM* motor) {
    eventReceiver = motor->getReceiver();

    ms_Keyboard.reset();

    characterTimer.init(4);

    presentJoy = 0;
    /*
    int presentJoy = glfwJoystickPresent(GLFW_JOYSTICK_1);
    int axesCount {0};
    axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

    std::cout << "Present: " << axes << "\n";

    int butonCount {0};
    butons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &butonCount);*/
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::onkeypress(keys::KEY_CODE_G k) {
    ms_Keyboard.keyPressed(k);
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::onkeyrelease(keys::KEY_CODE_G k) {
    ms_Keyboard.keyReleased(k);
}

template <typename GameCTX_t>
bool InputSystem_t<GameCTX_t>::isKeyPressed (keys::KEY_CODE_G k) {
    if (ms_Keyboard.isKeyPressed(k, eventReceiver)) {
        return true;
    } else {
        return false;
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::setDirectionMoving(PhysicsComponent_t* phy){
    if( phy->vx != 0 || phy->vy != 0){
        phy->v_linear = 1;
    } else return;
    

    auto torient{ std::atan2(phy->vy, phy->vx) };
    if ( torient < 0 ) torient += 2*PI;
    auto vang { torient - phy->orientation };
    if ( vang > PI ) vang -= 2*PI;
    else if ( vang < -PI ) vang += 2*PI;
    phy->v_angular = std::clamp( vang, -phy->KmaxVang, phy->KmaxVang );
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::checkMusgoHielo(GameCTX_t& g, int lf, int du, bool avoid, PhysicsComponent_t& phy) {
    auto* sta { g.template getRequiredComponent<PhysicsComponent_t, StaminaComponent_t>(phy) };

    float mult {1.0};

    if (avoid == true) {
        mult = 1.5;

        if (sta != nullptr && sta->cantStamina > 5) {
            sta->cantStamina = sta->cantStamina - 5;
        }
    }

    if (phy.pasomusgo == true) {
        if (lf == -1) {
            phy.vx = -2.0 * mult;
        }    
        if (lf == 1) {
            phy.vx = 2.0 * mult;
        }
        if (du == -1) {
            phy.vy = -2.0 * mult;
        } 
        if (du == 1) {
            phy.vy = 2.0 * mult;
        }

        phy.pasomusgo = false;
    } else {
        if (phy.pasohielo == true) {
            if (lf == -1) {
                phy.vx = -0.5 * mult;
            }
            if (lf == 1) {
                phy.vx = 0.5 * mult;
            }
            if (du == -1) {
                phy.vy = -0.5 * mult;
            }
            if (du == 1) {
                phy.vy = 0.5 * mult;
            }

            phy.pasohielo = false;
        } else {
            if (lf == -1) {
                phy.vx = -0.55 * mult;
            }
            if (lf == 1) {
                phy.vx = 0.6 * mult;
            }
            if (du == -1) {
                phy.vy = -0.8 * mult;
            }
            if (du == 1) {
                phy.vy = 0.6 * mult;
            }
        }
    } 
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::sumarDistancia (PhysicsComponent_t& phy, RenderComponent_t& ren, size_t pos, float x, float y) {
    ren.entityNodes.childs.at(pos).x = phy.x + x;
    ren.entityNodes.childs.at(pos).y = phy.y + y;
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moverExtremidadesLeftRight (int lf, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    for (size_t i {0}; i < static_cast<size_t>(ren.entityNodes.childs.size()); ++i) {
        switch (i) {
            case 4:
                //movimiento a derecha
                if (lf == 1) {
                    sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDR, inp.distsCabeza.disyCab); 
                }
                
                //movimiento a izquierda
                if (lf == -1) {
                    sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDL, inp.distsCabeza.disyCab);
                }
                break;

            case 0:
                //SUPERIOR DERECHO
                if(characterTimer.getEllapsed()==3){   
                    sumarDistancia(phy, ren, i, inp.distsBrazoD.disx1, inp.distsBrazoD.disy1); 
                }else{
                    sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy1); 
                }
                break;

            case 1:
                //SUPERIOR IZQUIERDO
                if(characterTimer.getEllapsed()==1 || characterTimer.getEllapsed()==2){
                    sumarDistancia(phy, ren, i, inp.distsBrazoI.disx1, inp.distsBrazoI.disy1); 
                }else{
                    sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy1); 
                }
                break;

            case 2:
                //INFERIOR DERECHO
                if(characterTimer.getEllapsed()==3 || characterTimer.getEllapsed()==4){
                    sumarDistancia(phy, ren, i, inp.distsPiernaD.disx1, inp.distsPiernaD.disy1); 
                }else{
                    sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy1); 
                } 
                break;

            case 3:
                //INFERIOR IZQUIERDO
                if(characterTimer.getEllapsed()==2){
                    sumarDistancia(phy, ren, i, inp.distsPiernaI.disx1, inp.distsPiernaI.disy1); 
                }else{
                    sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy1);
                }
                break;
        }
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moverExtremidadesDownUp (int du, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    for (size_t i {0}; i < static_cast<size_t>(ren.entityNodes.childs.size()); ++i) {
        switch (i) {
            case 4:
                sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabU, inp.distsCabeza.disyCab);

                if(ms_Keyboard.isKeyPressed( inp.key_LEFT, eventReceiver )){
                    if (du == -1) {
                        sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDL, inp.distsCabeza.disyCab);
                    }

                    if (du == 1) {
                        sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabUL, inp.distsCabeza.disyCab);
                    }
                }else if(ms_Keyboard.isKeyPressed( inp.key_RIGHT, eventReceiver )){
                    if (du == -1) {
                        sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDR, inp.distsCabeza.disyCab);
                    }
                    
                    if (du == 1) {
                        sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabUR, inp.distsCabeza.disyCab);
                    }
                }
                break;
            
            case 0:
                //SUPERIOR DERECHO
                if(characterTimer.getEllapsed()==3){    
                    leg_Front_D = true;
                    leg_Front_I = false;
                }else{
                    leg_Front_D = false;
                }

                if(leg_Front_D){
                    sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy2);
                }else{
                    sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy1);
                }

                if(characterTimer.getEllapsed()==2){
                    sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy3);
                }

                if(characterTimer.getEllapsed()==1){
                    sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy4);
                }

                break;
            
            case 1:
                //SUPERIOR IZQUIERDO
                if(characterTimer.getEllapsed()==1){
                    leg_Front_I = true;
                    leg_Front_D = false;
                }else{
                    leg_Front_I = false;
                }

                if(leg_Front_I){
                    sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy2);
                }else{
                    sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy1);
                }

                if(characterTimer.getEllapsed()==4){
                    sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy3);
                }

                if(characterTimer.getEllapsed()==3){
                    sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy4);
                }
                break;

            case 2:
                //INFERIOR DERECHO
                if(characterTimer.getEllapsed()==4){
                    leg_Back_D = true;
                }else{
                    leg_Back_D = false;
                }

                if(leg_Back_D){
                    sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy2);
                }else{
                    sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy1);
                }

                if(characterTimer.getEllapsed()==2){
                    sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy3);
                }
                break;

            case 3:
                //INFERIOR IZQUIERDO
                if(characterTimer.getEllapsed()==2){
                    leg_Back_I = true;
                }else{
                    leg_Back_I = false;
                }

                if(leg_Back_I){
                    sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy2);
                }else{
                    sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy1);
                }
                
                if(characterTimer.getEllapsed()==4){
                    sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy3);
                }
                break;
        }
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moveDiagonal(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    characterTimer.count(true);

    int lr {0};
    int du {0};

    if (ms_Keyboard.isKeyPressed( inp.key_LEFT, eventReceiver )) {
        lr = -1;
    }

    if (ms_Keyboard.isKeyPressed( inp.key_RIGHT, eventReceiver )) {
        lr = 1;
    }

    if (ms_Keyboard.isKeyPressed( inp.key_UP, eventReceiver )) {
        du = 1;
    }

    if (ms_Keyboard.isKeyPressed( inp.key_DOWN, eventReceiver )) {
        du = -1;
    }

    if(presentJoy==1){
        if (axes[0] < -0.5) {
            lr = -1;
        }

        if (axes[0] > 0.5) {
            lr = 1;
        }

        if (axes[1] < -0.5) {
            du = 1;
        }

        if (axes[1] > -0.5) {
            du = -1;
        }
    }

    checkMusgoHielo(g, lr, du, false, phy);
    
    if (ren.entityNodes.node.node != nullptr) {
        auto& bb { g.template getBlackBoard() };

        if (bb.danyoplayer == true) {
            if(ren.entityNodes.node.node->getAnimation() != "danyo"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("danyo");
            }
        } else {
            if(ren.entityNodes.node.node->getAnimation() != "escalada"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("escalada");
            }
        }

        ren.entityNodes.node.node->ActualizarFrame(2);                        
    } 
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moveAvoid(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    characterTimer.count(true);

    int lr {0};
    int du {0};

    if (ms_Keyboard.isKeyPressed( inp.key_LEFT, eventReceiver )) {
        lr = -1;
    }

    if (ms_Keyboard.isKeyPressed( inp.key_RIGHT, eventReceiver )) {
        lr = 1;
    }

    if (ms_Keyboard.isKeyPressed( inp.key_UP, eventReceiver )) {
        du = 1;
    }

    if (ms_Keyboard.isKeyPressed( inp.key_DOWN, eventReceiver )) {
        du = -1;
    }

    if(presentJoy==1){
        if (axes[0] < -0.5) {
            lr = -1;
        }

        if (axes[0] > 0.5) {
            lr = 1;
        }

        if (axes[1] < -0.5) {
            du = 1;
        }

        if (axes[1] > -0.5) {
            du = -1;
        }
    }

    checkMusgoHielo(g, lr, du, true, phy);
    
    if (ren.entityNodes.node.node != nullptr) {
        auto& bb { g.template getBlackBoard() };

        if (bb.danyoplayer == true) {
            if(ren.entityNodes.node.node->getAnimation() != "danyo"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("danyo");
            }
        } else {
            if(ren.entityNodes.node.node->getAnimation() != "escalada"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("escalada");
            }
        }

        ren.entityNodes.node.node->ActualizarFrame(2);                      
    } 
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moveLeft(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    auto& bb { g.template getBlackBoard() };

    characterTimer.count(true);

//    if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
        checkMusgoHielo(g, -1, 0, false, phy);                  
//    }else{
//        phy->vx = 0;
//    }

    if (!ren.entityNodes.childs.empty()) {
        moverExtremidadesLeftRight(-1, inp, phy, ren);       
    }

    if (ren.entityNodes.node.node != nullptr) {
        auto& bb { g.template getBlackBoard() };

        if (bb.danyoplayer == true) {
            if(ren.entityNodes.node.node->getAnimation() != "danyo"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("danyo");
            }
        } else {
            if (bb.andandoplayer == true && (phy.x < inp.xMinAndar || inp.xMaxAndar < phy.x)) {
                bb.andandoplayer = false;
            }

            if (bb.andandoplayer == true) {
                if(ren.entityNodes.node.node->getAnimation() != "caminarI"){
                    ren.entityNodes.node.node->setFrame(0); 
                    ren.entityNodes.node.node->ActualizarAnimation("caminarI");
                }
            } else {
                if(ren.entityNodes.node.node->getAnimation() != "lateral"){
                    ren.entityNodes.node.node->setFrame(0); 
                    ren.entityNodes.node.node->ActualizarAnimation("lateral");
                }
            }
        }
        
        ren.entityNodes.node.node->ActualizarFrame(2);
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moveRight(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    auto& bb { g.template getBlackBoard() };

    characterTimer.count(true);

//    if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
        checkMusgoHielo(g, 1, 0, false, phy);   
//    }else{
//        phy->vx = 0;
//    }

    if (!ren.entityNodes.childs.empty()) {
        moverExtremidadesLeftRight(1, inp, phy, ren);       
    }

    if (ren.entityNodes.node.node != nullptr) {
        auto& bb { g.template getBlackBoard() };

        if (bb.danyoplayer == true) {
            if(ren.entityNodes.node.node->getAnimation() != "danyo"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("danyo");
            }
        } else {
            if (bb.andandoplayer == true && (phy.x < inp.xMinAndar || inp.xMaxAndar < phy.x)) {
                bb.andandoplayer = false;
            }

            if (bb.andandoplayer == true) {
                if(ren.entityNodes.node.node->getAnimation() != "caminarD"){
                    ren.entityNodes.node.node->setFrame(0); 
                    ren.entityNodes.node.node->ActualizarAnimation("caminarD");
                }
            } else {
                if(ren.entityNodes.node.node->getAnimation() != "lateral"){
                    ren.entityNodes.node.node->setFrame(0); 
                    ren.entityNodes.node.node->ActualizarAnimation("lateral");
                }
            }
        }

        ren.entityNodes.node.node->ActualizarFrame(2);
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moveUp(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    characterTimer.count(true);

//    if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
        checkMusgoHielo(g, 0, 1, false, phy);   
//    }else{
//        phy->vy = 0;
//    }

    if (!ren.entityNodes.childs.empty()) {
        moverExtremidadesDownUp(1, inp, phy, ren);        
    }

    if (ren.entityNodes.node.node != nullptr) {
        auto& bb { g.template getBlackBoard() };

        if (bb.danyoplayer == true) {
            if(ren.entityNodes.node.node->getAnimation() != "danyo"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("danyo");
            }
        } else {
            if(ren.entityNodes.node.node->getAnimation() != "escalada"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("escalada");
            }
        }

        ren.entityNodes.node.node->ActualizarFrame(2);
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moveDown(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    characterTimer.count(true);

//    if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
        checkMusgoHielo(g, 0, -1, false, phy); 
//    }else{
//        phy->vy = 0;
//    }

    if (!ren.entityNodes.childs.empty()) {
        moverExtremidadesDownUp(-1, inp, phy, ren);       
    }

    if (ren.entityNodes.node.node != nullptr) {
        auto& bb { g.template getBlackBoard() };

        if (bb.danyoplayer == true) {
            if(ren.entityNodes.node.node->getAnimation() != "danyo"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("danyo");
            }
        } else {
            if(ren.entityNodes.node.node->getAnimation() != "escalada"){
                //phy->roty = 0;
                ren.entityNodes.node.node->setFrame(0); 
                ren.entityNodes.node.node->ActualizarAnimation("escalada");
            }
        }

        ren.entityNodes.node.node->ActualizarFrame(2);
    } 
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::animCuerda(GameCTX_t& g, RenderComponent_t& ren) {
    auto& bb { g.template getBlackBoard() };

    if (bb.contCuerda < 63) {
        if (bb.contCuerda == 1) {
            auto* cuer { g.template getEntityByID(bb.cuerdaID) };

            if (cuer != nullptr) {
                auto* sou { cuer->template getComponent<SoundComponent_t>() };
                
                if(sou != nullptr){
                    sou->marked_for_play = 1;       
                }
            }

            for (auto& fol : g.template getComponents<FollowComponent_t>()) {
                if (fol.followEntityID == ren.getEntityID()) {
                    fol.y -= 10;
                }
            }
        }

        if(ren.entityNodes.node.node->getAnimation() != "cuerda"){
            ren.entityNodes.node.node->setFrame(0); 
            ren.entityNodes.node.node->ActualizarAnimation("cuerda");
        }

        ren.entityNodes.node.node->ActualizarFrame(2);

        ++(bb.contCuerda);
        bb.enCuerda = true;
    } else {
        bb.contCuerda = 0;
        bb.enCuerda = false;

        for (auto& fol : g.template getComponents<FollowComponent_t>()) {
            if (fol.followEntityID == ren.getEntityID()) {
                fol.y += 10;
            }
        }
    }
}

template <typename GameCTX_t>
bool InputSystem_t<GameCTX_t>::update(GameCTX_t& g, Motor3DLUM* motor){
    auto& bb { g.template getBlackBoard() };
    
    presentJoy = glfwJoystickPresent(GLFW_JOYSTICK_1);

    if(presentJoy == 1){
        int axesCount {0};
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

        int butonCount {0};
        butons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &butonCount);

        //std::cout << "X: " << axes[0] << "\n";
        //std::cout << "Y: " << axes[1] << "\n";
        //std::cout << "\n";

        /*if (GLFW_PRESS == butons[0]) {
            std::cout << "pulso A\n";
        }*/

        if (GLFW_PRESS == butons[1]) {
            bb.pulsoInteractMando = true;
        } else {
            bb.pulsoInteractMando = false;
        }

        /*if (GLFW_PRESS == butons[2]) {
            std::cout << "pulso Y\n";
        }*/
        
        if (GLFW_PRESS == butons[3]) {
            bb.pulsoPauseMando = true;
        } else {
            bb.pulsoPauseMando = false;
        }
    }
    

    if(prubi!= motor->getFPS()){
        prubi = motor->getFPS();

        for (auto& inp : g.template getComponents<InputComponent_t>()) {
            auto* phy { g.template getRequiredComponent<InputComponent_t, PhysicsComponent_t>(inp) };
            auto* ren { g.template getRequiredComponent<InputComponent_t, RenderComponent_t>(inp) };    
        
            if (phy != nullptr) {
                phy->v_angular = phy->v_linear = 0;
                phy->vx = 0;
                phy->vy = 0;

                //auto* sou = g.template getRequiredComponent<PhysicsComponent_t, SoundComponent_t>(*phy);

                if (bb.enCuerda == true || bb.sigoCuerda == true) {
                    if (ren != nullptr) {
                        animCuerda(g, *ren);
                    }
                } else {
                    bool diagonal { false };
                    if(presentJoy==1){
                        if((axes[0] < -0.5 ||
                            axes[0] > 0.5) && 
                            (axes[1] > 0.5 || 
                            axes[1] < -0.5)){

                            diagonal = true;    
                            //std::cout<<"DIAGONAL"<<"\n";

                        }
                    }
                    

                    if (((ms_Keyboard.isKeyPressed( inp.key_LEFT, eventReceiver ) ||
                        ms_Keyboard.isKeyPressed( inp.key_RIGHT, eventReceiver )) && 
                        (ms_Keyboard.isKeyPressed( inp.key_DOWN, eventReceiver ) || 
                        ms_Keyboard.isKeyPressed( inp.key_UP, eventReceiver ))) || diagonal) {

                        bb.andandoplayer = false;

                        if (bb.muriendoplayer == false) {
                            moveDiagonal(g, inp, *phy, *ren);
                        }
                    } else {
                        if ( ((ms_Keyboard.isKeyPressed(inp.key_LEFT, eventReceiver) ||
                            ms_Keyboard.isKeyPressed(inp.key_RIGHT, eventReceiver) ||
                            ms_Keyboard.isKeyPressed(inp.key_UP, eventReceiver) ||
                            ms_Keyboard.isKeyPressed(inp.key_DOWN, eventReceiver) ) && 
                            (ms_Keyboard.isKeyPressed(inp.key_AVOID, eventReceiver)))
                            
                            || (presentJoy == 1 && axes != nullptr &&  (GLFW_PRESS == butons[0])
                                && (diagonal || (axes[0] < -0.5) || (axes[0] > 0.5) || (axes[0] < -0.5) || (axes[0] > 0.5)))) {

                            bb.andandoplayer = false;

                            if (bb.muriendoplayer == false) {
                                moveAvoid(g, inp, *phy, *ren);
                            }
                        } else {
                            if (ms_Keyboard.isKeyPressed( inp.key_LEFT, eventReceiver ) ||
                                (presentJoy == 1 && axes != nullptr && (axes[0] < -0.5))) {

                                if (bb.muriendoplayer == false) {
                                    moveLeft(g, inp, *phy, *ren);
                                    //std::cout<<"IZQUIERDA"<<"\n";
                                }
                            } 

                            if (ms_Keyboard.isKeyPressed( inp.key_RIGHT, eventReceiver ) ||
                                (presentJoy == 1 && axes != nullptr && (axes[0] > 0.5))) {

                                if (bb.muriendoplayer == false) {
                                    //std::cout<<"DERECHA"<<"\n";
                                    moveRight(g, inp, *phy, *ren);  
                                }
                            } 

                            if (ms_Keyboard.isKeyPressed( inp.key_UP, eventReceiver ) ||
                                (presentJoy == 1 && axes != nullptr && (axes[1] < -0.5))) {
                                
                                bb.andandoplayer = false;

                                if (bb.muriendoplayer == false) {
                                    //std::cout<<"ARRIBA"<<"\n";
                                    moveUp(g, inp, *phy, *ren);  
                                }
                            } 

                            if (ms_Keyboard.isKeyPressed( inp.key_DOWN, eventReceiver ) ||
                                (presentJoy == 1 && axes != nullptr && (axes[1] > 0.5))) {
                                
                                bb.andandoplayer = false;

                                if (bb.muriendoplayer == false) {
                                    //std::cout<<"ABAJO"<<"\n";
                                    moveDown(g, inp, *phy, *ren);
                                }
                            }
                        }
                    }
                }
            }  
        }
    
    }

    if (g.template getComponents<InputComponent_t>().size() == 0) {
        return false;
    }

    return true;
} 