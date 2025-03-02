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

#include "gameobjectfactory.hpp"


ECS::Entity_t& GameObjectFactory_t::createEntity(int32_t x, int32_t y, const std::string_view filename) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    m_EntMan.addComponent<HealthComponent_t>(e);

    //re.loadFromFile(filename);

    ph.x = x;
    ph.y = y;
    ph.z = 15;

    return e;
}

/****************************************************************************************************/
/*******************************************PLAYER***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createPlayer(const picojson::array &player) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { player.at(0).get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    //ph.roty = 180;

    auto& he { m_EntMan.addComponent<HealthComponent_t>(e) };
    const picojson::value health { player.at(0).get("health") };
    he.health = std::stoi(health.get("health").to_str());
    he.maxHealth = std::stoi(health.get("maxHealth").to_str());


    auto& est { m_EntMan.addComponent<StaminaComponent_t>(e) };
    const picojson::value stamina { player.at(0).get("stamina") };
    est.maxStamina = std::stoi(stamina.get("maxStamina").to_str());
    est.cantStamina = std::stoi(stamina.get("cantStamina").to_str());

    
    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { player.at(0).get("render") };

    std::string modelo { render.get("malla").to_str() };
    re.entityNodes.node.node = motor->createMeshNode("assets/animaciones/animacionesZacarias/caminar/caminar_000113.obj", false);
    re.w = re.h = re.d = std::stof(render.get("size").to_str());

    motor->setAnimationToNode(re.entityNodes.node.node, "escalada");
    motor->setAnimationToNode(re.entityNodes.node.node, "lateral");
    motor->setAnimationToNode(re.entityNodes.node.node, "caminarD");
    motor->setAnimationToNode(re.entityNodes.node.node, "caminarI");
    motor->setAnimationToNode(re.entityNodes.node.node, "cavar");
    motor->setAnimationToNode(re.entityNodes.node.node, "cuerda");
    motor->setAnimationToNode(re.entityNodes.node.node, "saltoVictoria");
    motor->setAnimationToNode(re.entityNodes.node.node, "danyo");
    
    re.entityNodes.node.node->ShaderNode = 1;


    auto& in { m_EntMan.addComponent<InputComponent_t>(e) };
    const picojson::value input { player.at(0).get("input") };

    float disx1BraD { std::stof(input.get("disx1BraD").to_str()) };
    float disx2BraD { std::stof(input.get("disx2BraD").to_str()) };
    float disy1BraD { std::stof(input.get("disy1BraD").to_str()) };
    float disy2BraD { std::stof(input.get("disy2BraD").to_str()) };
    float disy3BraD { std::stof(input.get("disy3BraD").to_str()) };
    float disy4BraD { std::stof(input.get("disy4BraD").to_str()) };

    in.distsBrazoD = { disx1BraD, disx2BraD, disy1BraD, disy2BraD, disy3BraD, disy4BraD };

    float disx1BraI { std::stof(input.get("disx1BraI").to_str()) };
    float disx2BraI { std::stof(input.get("disx2BraI").to_str()) };
    float disy1BraI { std::stof(input.get("disy1BraI").to_str()) };
    float disy2BraI { std::stof(input.get("disy2BraI").to_str()) };
    float disy3BraI { std::stof(input.get("disy3BraI").to_str()) };
    float disy4BraI { std::stof(input.get("disy4BraI").to_str()) };

    in.distsBrazoI = { disx1BraI, disx2BraI, disy1BraI, disy2BraI, disy3BraI, disy4BraI };

    float disx1PieD { std::stof(input.get("disx1PieD").to_str()) };
    float disx2PieD { std::stof(input.get("disx2PieD").to_str()) };
    float disy1PieD { std::stof(input.get("disy1PieD").to_str()) };
    float disy2PieD { std::stof(input.get("disy2PieD").to_str()) };
    float disy3PieD { std::stof(input.get("disy3PieD").to_str()) };

    in.distsPiernaD = { disx1PieD, disx2PieD, disy1PieD, disy2PieD, disy3PieD };

    float disx1PieI { std::stof(input.get("disx1PieI").to_str()) };
    float disx2PieI { std::stof(input.get("disx2PieI").to_str()) };
    float disy1PieI { std::stof(input.get("disy1PieI").to_str()) };
    float disy2PieI { std::stof(input.get("disy2PieI").to_str()) };
    float disy3PieI { std::stof(input.get("disy3PieI").to_str()) };

    in.distsPiernaI = { disx1PieI, disx2PieI, disy1PieI, disy2PieI, disy3PieI};

    float disyCab   { std::stof(input.get("disyCab").to_str()) };
    float disxCabDL { std::stof(input.get("disxCabDL").to_str()) };
    float disxCabDR { std::stof(input.get("disxCabDR").to_str()) };
    float disxCabU  { std::stof(input.get("disxCabU").to_str()) };
    float disxCabUL { std::stof(input.get("disxCabUL").to_str()) };
    float disxCabUR { std::stof(input.get("disxCabUR").to_str()) };

    in.distsCabeza = { disyCab, disxCabDL, disxCabDR, disxCabU, disxCabUL, disxCabUR};


    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    co.properties = ColliderComponent_t::P_IsPlayer;

    co.boxes = {
        { -re.w/2,  re.w/2,  -re.h/2,  re.h/2,  -re.d/2,  re.d/2, false, 0, 0, false} //cuerpo
    };

    
    m_EntMan.addComponent<ControlComponent_t>(e);
    m_EntMan.addComponent<PuntosComponent_t>(e);

    auto& so { m_EntMan.addComponent<SoundComponent_t>(e) };
    so.my_events.push_back("event:/Personajes/Zacarias/AlegriaFinal");
    so.my_events.push_back("event:/Personajes/Zacarias/Cansancio");
    so.my_events.push_back("event:/Personajes/Zacarias/Daño");
    so.my_events.push_back("event:/Personajes/Zacarias/MuerteCaida");
    so.my_events.push_back("event:/Personajes/Zacarias/MuerteDaño");

    so.my_events.push_back("event:/Personajes/Zacarias Cueva/AlegriaFinal");
    so.my_events.push_back("event:/Personajes/Zacarias Cueva/Cansancio");
    so.my_events.push_back("event:/Personajes/Zacarias Cueva/Daño");
    so.my_events.push_back("event:/Personajes/Zacarias Cueva/MuerteCaida");
    so.my_events.push_back("event:/Personajes/Zacarias Cueva/MuerteDaño");

    m_EntMan.getBlackBoard().playerID = e.getEntityID();

    return e;
}

void setComponenteVision(auto* co, float negw, float posw, float negh, float posh, float negd, float posd){
    if (co) {
        co->boxes = {{-negw, posw, -negh, posh, -negd, posd}};
        co->properties = ColliderComponent_t::P_EnemyVisual;
    }  
}

ECS::Entity_t& GameObjectFactory_t::createEnemy(const picojson::value &enemy, BehaviourTree_t * tree) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { enemy.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& he { m_EntMan.addComponent<HealthComponent_t>(e) };
    const picojson::value health { enemy.get("health") };
    he.health = std::stoi(health.get("health").to_str());
    he.maxHealth = std::stoi(health.get("maxHealth").to_str());
    he.damageInflicted = std::stoi(health.get("damageInflicted").to_str());
    he.selfDamageOnInfliction = std::stoi(health.get("selfDamageOnInfliction").to_str());

    auto& coVisual { m_EntMan.addComponentVisual<ColliderComponent_t>(e) };
    const picojson::value vision { enemy.get("vision") };
    float xneg { std::stof(vision.get("xneg").to_str()) };
    float xpos { std::stof(vision.get("xpos").to_str()) };
    float yneg { std::stof(vision.get("yneg").to_str()) };
    float ypos { std::stof(vision.get("ypos").to_str()) };
    float zneg { std::stof(vision.get("zneg").to_str()) };
    float zpos { std::stof(vision.get("zpos").to_str()) };
    setComponenteVision(&coVisual, xneg, xpos, yneg, ypos, zneg, zpos);


    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { enemy.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 1;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { enemy.get("collider") };

    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Enemy;

    auto& ia { m_EntMan.addComponent<IAComponent_t>(e) };
    const picojson::value ias { enemy.get("ia") };
    ia.arrivalRadius = 2;

    auto& so { m_EntMan.addComponent<SoundComponent_t>(e) };

    if (ias.get("type").to_str() == "cabra") {
        motor->setAnimationToNode(re.entityNodes.node.node, "cabra");

        ia.enemy = type_enemy::Cabra;
        ph.KmaxVLin = 0.5;

        ph.soyDeTunel = false;

        so.event_id = "event:/Personajes/Cabra/PastarCabra";
    } else if (ias.get("type").to_str() == "aranya") {
        std::string anim {""};
        int numAranya {std::stoi(collider.get("numaranya").to_str())};

        switch (numAranya) {
            case 0:
                anim = "aranya0";
                break;
            case 1:
                anim = "aranya1";
                break;
            case 2:
                anim = "aranya2";
                break;
        }
        motor->setAnimationToNode(re.entityNodes.node.node, anim);
        
        ia.enemy = type_enemy::Aranya;
        ia.apply_gravity = false;
        ph.KmaxVLin = 0.4;
        ia.arrivalRadius = 0.5;

        ph.soyDeTunel = true;

        so.event_id = "event:/Personajes/Araña/SonidoAranya";
    } else if (ias.get("type").to_str() == "aguila") {
        motor->setAnimationToNode(re.entityNodes.node.node, "aguila");

        ia.enemy = type_enemy::Aguila;
        ph.KmaxVLin = 0.7;

        ph.soyDeTunel = false;

        so.event_id = "event:/Personajes/Aguila/Graznido";
    }

    so.isEvent3D = true;
    so.marked_for_init = 1;
    so.marked_for_play = 1;
    so.alwaysPlay = true;
    
    ia.enemy_timer.init(30);


    ia.ix = ph.x;
    ia.iy = ph.y;
    ia.tree = tree;

    return e;
}

void GameObjectFactory_t::crearEnemigos (BehaviourTree_t* tree1, const picojson::array &enemies) const {
    for (size_t i {0}; i < static_cast<size_t>(enemies.size()); ++i) {
        createEnemy(enemies.at(i), tree1);
    }   
    //createEnemy(420, 300,type_enemy::Cabra, tree1);
    //createEnemy(220, 230 ,type_enemy::Aranya, tree1);
    //createEnemy(740, 580,type_enemy::Cabra, tree1);
    //createEnemy(220, 820,type_enemy::Aguila, tree1);
}

ECS::Entity_t& GameObjectFactory_t::createPalosPlace(const picojson::value &palo) const {  
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { palo.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = 0;
    ph.zvuelta = 0;

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { palo.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { palo.get("collider") };
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_spPalos;

    //Agregar al Blackboard
    m_EntMan.getBlackBoard().palos_bb.push_back(&e);

    return e;
}

void GameObjectFactory_t::createPalosPlaces(const picojson::array &palos) const {
    //createPalosPlace(495, 780);

    for (size_t i {0}; i < static_cast<size_t>(palos.size()); ++i) {
        createPalosPlace(palos.at(i));
    } 
}

ECS::Entity_t& GameObjectFactory_t::createTelaranya(int32_t x, int32_t y, int32_t vel) const {
    auto& e { createEntity(x, y, "assets/telaranya.png") };
    auto* phy { e.getComponent<PhysicsComponent_t>() };
    auto* co { e.getComponent<ColliderComponent_t>() };
    auto* he { e.getComponent<HealthComponent_t>() };
    auto* re { e.getComponent<RenderComponent_t>() };
    if (!phy && !co && !he && !re) { return e; }

    re->entityNodes.node.node = motor->createMeshNode("assets/modelados/telaranya/telarana.obj", false);
    re->entityNodes.node.node->setScale(Vector3d(2.0,2.0,2.0));

    re->w = re->h = re->d = 12;

    re->entityNodes.node.node->ShaderNode = 0;

    if (phy) {
        phy->rotx = 90;
        phy->vy = 0;
        phy->z = 0;
        phy->vx = vel;
        phy->zida = 580;
        phy->zvuelta = 0;
        //phy->gravity = 0;
    }
    
    if (co) {
    //    co->boxRoot.collided = false;
        co->boxes = {{-re->w/2, re->w/2, -re->h/2, re->h/2, -re->d/2, re->d/2}};
        co->properties = ColliderComponent_t::P_Telaranya;
    }    
    if (he) {
        he->damageInflicted = 1;
        he->selfDamageOnInfliction = 1;
        he->health = 1;
    }
    return e;
}

void GameObjectFactory_t::unfollowPalo(ECS::EntityID_t Entounfollow) const{
    for(auto follow : m_EntMan.template getComponents<FollowComponent_t>()){
        if(follow.followEntityID == Entounfollow){
            auto* phy { m_EntMan.getRequiredComponent<FollowComponent_t,PhysicsComponent_t>(follow) };
            phy->vy = -2;
            m_EntMan.getStorageComponents().deleteComponentByTypeIDAndEntityID(follow.getComponentTypeID(),follow.getEntityID());
        }
    }
}

ECS::Entity_t& GameObjectFactory_t::createPalo(int32_t x, int32_t y, int32_t vel, ECS::EntityID_t Entfollow) const {
    auto& e { createEntity(x, y, "assets/palo.png") };
    auto* phy { e.getComponent<PhysicsComponent_t>() };
    auto* co { e.getComponent<ColliderComponent_t>() };
    auto* he { e.getComponent<HealthComponent_t>() };
    auto* re { e.getComponent<RenderComponent_t>() };
    auto& fo { m_EntMan.addComponent<FollowComponent_t>(e) };
    fo.x = 0;
    fo.y = -10;
    fo.z = 0;
    fo.followEntityID = Entfollow;

    if (!phy && !co && !he && !re) { return e; }

    re->entityNodes.node.node = motor->createMeshNode("assets/modelados/palo/palo.obj", false);
    re->entityNodes.node.node->setScale(Vector3d(2.0,2.0,2.0));

    re->w = re->h = 12;
    re->d = 200;

    re->entityNodes.node.node->ShaderNode = 0;

    if (phy) {
        phy->vx = 0;
        phy->vy = 0;
        phy->z = 0;
        phy->zida = 0;
        phy->zvuelta = 0;
        //phy->vy = -vel;
        //phy->gravity = 0;
    }
    
    if (he) {
        he->damageInflicted = 1;
        he->selfDamageOnInfliction = 1;
        he->health = 1;
    } 

    if (co) {
        co->boxes = {{-re->w/2, re->w/2, -re->h/2, re->h/2, -re->d/2, re->d/2}}; //cambiar
        co->properties = ColliderComponent_t::P_Palo;
    }   
    //Agregar al Blackboard
    //m_EntMan.getSingletonComponent<BlackboardComponent_t>().palos_bb.emplace_back(e);

    return e;
}

/****************************************************************************************************/
/********************************************META****************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createMeta(const picojson::array &meta) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { meta.at(0).get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());
    ph.roty = 270;

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { meta.at(0).get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);
    re.entityNodes.node.node->setScale(Vector3d(1.5,1.5,1.5));

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { meta.at(0).get("collider") };

    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Meta;

    return e;
}

/****************************************************************************************************/
/********************************************ARROW****************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createArrow(const picojson::array &arrow) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { arrow.at(0).get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { arrow.at(0).get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);
    re.entityNodes.node.node->setScale(Vector3d(3.0,3.0,3.0));

    re.w = std::stof(render.get("w").to_str()) * 3.0;
    re.h = std::stof(render.get("h").to_str()) * 3.0;
    re.d = std::stof(render.get("d").to_str()) * 3.0;

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { arrow.at(0).get("collider") };
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/4, re.w/4, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Arrow;

    return e;
}

/****************************************************************************************************/
/********************************************CAMARA**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createCamera(int32_t x, int32_t y, uint32_t w, uint32_t h) const {
    auto& e { m_EntMan.createEntity() };

    auto& cam { m_EntMan.addComponent<CameraComponent_t>(e) };
    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };

    cam.camNode = motor->getCamera();

    //ph.gravity = 0;

    cam.srcx = x;
    cam.srcy = y;
    cam.w = w;
    cam.h = h;

    return e;
}

/****************************************************************************************************/
/*********************************************ROCA***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createRoca(int32_t x, int32_t y, int32_t z, float vel, bool mover, ECS::EntityID_t my_sal) const {
    auto& e { createEntity(x, y, "assets/pajaro.png") };
    //std::cout << "Roca: " << e.getEntityID() << "\n";

    auto* phy { e.getComponent<PhysicsComponent_t>() };
    auto* co { e.getComponent<ColliderComponent_t>() };
    auto* he { e.getComponent<HealthComponent_t>() };
    auto* re { e.getComponent<RenderComponent_t>() };

    if (!phy && !co && !he && !re) { return e; }


    re->entityNodes.node.node = motor->createMeshNode("assets/modelados/roqui/roqui.obj", false);
    
    re->w = re->h = re->d = 6;

    re->entityNodes.node.node->ShaderNode = 0;

    if (phy) {
        phy->vx = 0;
        phy->vy = -vel;
        phy->z = z;

        phy->zida = 0;
        phy->zvuelta = 250;
    }
    
    if (co) {
        co->boxes = {{-6, 6, -6, 6, -6, 6}};
        co->properties = ColliderComponent_t::P_Damages;
        co->nomover = mover;
        co->subirbajar= 0;
        co->destroyable = false;
        co->mySal=my_sal;
    }    

    if (he) {
        he->damageInflicted = 1;
        he->selfDamageOnInfliction = 1;
        he->health = 1;
    }

    auto& so { m_EntMan.addComponent<SoundComponent_t>(e) };
    so.event_id = "event:/Efectos/Rocas/CaidaRocas";
    so.isEvent3D = false;
    so.marked_for_init = 1;
    so.marked_for_play = 0;

    return e;
}

void GameObjectFactory_t::crearRocas (uint32_t cant) const {
    float x { static_cast<float>(rand() % 800 + 1) };
    float y { 0 };
    int velo {1};

    int xx {20};
           
    for(size_t j {0}; j<cant; ++j){
        //x = rand() % 800 + 1;
        //y = 800+rand()%(5000-800);
        x = (((j*2)+14)*xx)+420;
        y = 440;
        velo = 2+rand()%(7-2);
//        auto& enti =  createRoca(x, y, 12, velo, true);

        //auto linerock = motor->drawA3DLine(x, y, 15, 180); //x,y,z,rotation
    }
}

/****************************************************************************************************/
/*****************************************SALIENTES**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createSaliente(const picojson::value &saliente) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { saliente.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = std::stoi(fisica.get("roty").to_str());
    ph.friction = 0.85f;
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { saliente.get("render") };

    std::string modelo { render.get("malla").to_str() };
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);
    
    re.entityNodes.node.node->ShaderNode = 1;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { saliente.get("collider") };
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());

    int numboxes {0};

    if (saliente.get("partes").to_str() != "null") {
        while (saliente.get("partes").get(numboxes).to_str() != "null") {
            ++numboxes;
        }
    }

    co.boxes.reserve(numboxes);

    //std::cout << "NumboxesI:" << numboxes << "\n";

    if (numboxes > 0 && saliente.get("partes").to_str() != "null") {
        int i {0};

        while (saliente.get("partes").get(i).to_str() != "null") {
            float w { std::stof(saliente.get("partes").get(i).get("w").to_str()) };
            float h { std::stof(saliente.get("partes").get(i).get("h").to_str()) };
            float d { std::stof(saliente.get("partes").get(i).get("d").to_str()) };

            float disX { std::stof(saliente.get("partes").get(i).get("disX").to_str()) };
            float disY { std::stof(saliente.get("partes").get(i).get("disY").to_str()) };

            bool lanza {false};

            if (saliente.get("partes").get(i).get("lanzadorrocas").to_str() == "true") {
                lanza = true;
            }

            //std::cout << "Numboxes:" << numboxes << "\n";

            //co.boxes.at(i) = BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, lanza};

            if (numboxes > 0) {
                //std::cout << "i: " << i << "\n";
                co.boxes.insert(co.boxes.begin()+i, BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, lanza});
            }

            //std::cout << "Size:" << co.boxes.size() << "\n";

            ++i;
            --numboxes;
        }
    }
 
    co.properties = ColliderComponent_t::P_Saliente;   

    //Agregar al Blackboard
    m_EntMan.getBlackBoard().salientes_bb.emplace_back(&e);

    return e;
}

void GameObjectFactory_t::crearSalientes(const picojson::array &salientes) const {
    for (size_t i {0}; i < static_cast<size_t>(salientes.size()); ++i) {
        createSaliente(salientes.at(i));
    }   
}

/****************************************************************************************************/
/****************************************NIDOS Y CRIAS***********************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createNido(const picojson::value &nido) const{
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { nido.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { nido.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { nido.get("collider") };
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Nido;

    return e;
}

void GameObjectFactory_t::crearNidos(const picojson::array &nidos, const picojson::array &crias) const{
    if (nidos.size() == crias.size()) {
        for (size_t i {0}; i < static_cast<size_t>(nidos.size()); ++i) {
            auto& n { createNido(nidos.at(i)) };
            createCria(crias.at(i), n);

            m_EntMan.getBlackBoard().criasrescatadas.push_back(false);
        } 

        m_EntMan.getBlackBoard().criasennivel = nidos.size() + 1;
    } /*else {
        std::cout << "Falta un nido o una cria\n";
    }*/  
}

ECS::Entity_t& GameObjectFactory_t::createCria(const picojson::value &cria, ECS::Entity_t& follow) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { cria.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { cria.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& fo { m_EntMan.addComponent<FollowComponent_t>(e) };
    const picojson::value seguir { cria.get("follow") };
    fo.x = std::stoi(seguir.get("x").to_str());
    fo.y = std::stoi(seguir.get("y").to_str());
    fo.z = std::stoi(seguir.get("z").to_str());
    fo.numcria = std::stoi(seguir.get("numcria").to_str());

    fo.followEntityID = follow.getEntityID();

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { cria.get("collider") };
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.properties = ColliderComponent_t::P_Cria;

    auto& so { m_EntMan.addComponent<SoundComponent_t>(e) };
    if (ph.zida == 0) {
        so.event_id = "event:/Personajes/Crias/CriaAyuda";
    } else {
        so.event_id = "event:/Personajes/Crias Cueva/CriaAyuda";
    }
    
    so.isEvent3D = true;
    so.marked_for_init = 1;
    so.marked_for_play = 1;
    so.alwaysPlay = true;

    return e;
}

/****************************************************************************************************/
/*******************************************ARBUSTOS*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createArbusto(const picojson::value &arbusto) const{
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { arbusto.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { arbusto.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { arbusto.get("collider") };
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Arbusto;

    //Agregar al Blackboard
    m_EntMan.getBlackBoard().arbustos_bb.emplace_back(&e);

    return e;
}

void GameObjectFactory_t::crearArbustos(const picojson::array &arbustos) const{
    for (size_t i {0}; i < static_cast<size_t>(arbustos.size()); ++i) {
        createArbusto(arbustos.at(i));
    }       
}

/****************************************************************************************************/
/*******************************************CASCADAS*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createCascada(const picojson::value &cascada) const{
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { cascada.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = 90;
    ph.zida = 0;
    ph.zvuelta = 0;

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { cascada.get("render") };
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    std::string modelo { render.get("malla").to_str() };
    re.entityNodes.node.node = motor->createMeshNode(modelo, false);

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Cascada;

    return e;
}

void GameObjectFactory_t::crearCascadas(const picojson::array &cascadas) const{
    for (size_t i {0}; i < static_cast<size_t>(cascadas.size()); ++i) {
        createCascada(cascadas.at(i));
    }       
}

/****************************************************************************************************/
/*******************************************SEMILLAS*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createSemilla(const picojson::value &semilla) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { semilla.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& he { m_EntMan.addComponent<HealthComponent_t>(e) };

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { semilla.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { semilla.get("collider") };
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Semilla;

    auto& so { m_EntMan.addComponent<SoundComponent_t>(e) };
    so.event_id = "event:/Efectos/Avellana/RecogerFruto";
    so.isEvent3D = false;
    so.marked_for_init = 1;
    so.marked_for_play = 0;

    return e;
}

void GameObjectFactory_t::crearSemillas(const picojson::array &semillas) const {
    for (size_t i {0}; i < static_cast<size_t>(semillas.size()); ++i) {
        createSemilla(semillas.at(i));
    }  
}

/****************************************************************************************************/
/******************************************ENGANCHES*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createEnganche(const picojson::value &enganche, int pos) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { enganche.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { enganche.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    std::string anim {""};
    switch (pos) {
        case 0:
            anim = "gancho0";
            break;
        case 1:
            anim = "gancho1";
            break;
        case 2:
            anim = "gancho2";
            break;
        case 3:
            anim = "gancho3";
            break;
        case 4:
            anim = "gancho4";
            break;
    }
    motor->setAnimationToNode(re.entityNodes.node.node, anim);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { enganche.get("collider") };
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());

    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}}; 
    co.properties = ColliderComponent_t::P_Control;

    auto& so { m_EntMan.addComponent<SoundComponent_t>(e) };
    so.event_id = "event:/Efectos/Enganche/Enganche";
    so.isEvent3D = false;
    so.marked_for_init = 1;
    so.marked_for_play = 0;

    return e;
}

void GameObjectFactory_t::crearEnganches(const picojson::array &enganches) const {
    for (size_t i {0}; i < static_cast<size_t>(enganches.size()); ++i) {
        createEnganche(enganches.at(i), i);
    } 
}

/****************************************************************************************************/
/******************************************AGUJEROS**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createAgujero(const picojson::value &agujero) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { agujero.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { agujero.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { agujero.get("collider") };
    co.quesubirbajar = std::stoi(collider.get("quesubirbajar").to_str()); 

    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Agujero;
  
    return e;
}

void GameObjectFactory_t::crearAgujeros(const picojson::array &agujeros) const {
    for (size_t i {0}; i < static_cast<size_t>(agujeros.size()); ++i) {
        createAgujero(agujeros.at(i));
    } 
}

/****************************************************************************************************/
/***************************************TRAMPOLINES**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createTrampolin(const picojson::value &trampolin) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { trampolin.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { trampolin.get("render") };

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { trampolin.get("collider") };
    co.quesubirbajar = std::stoi(collider.get("quesubirbajar").to_str()); 

    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Trampolin;
  
    return e;
}

void GameObjectFactory_t::crearTrampolines(const picojson::array &trampolines) const {
    for (size_t i {0}; i < static_cast<size_t>(trampolines.size()); ++i) {
        createTrampolin(trampolines.at(i));
    } 
}

/****************************************************************************************************/
/********************************************MUSGO***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createMusgo(const picojson::value &musgo) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { musgo.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = 0;
    ph.zvuelta = 0;

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { musgo.get("render") };
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    std::string modelo { render.get("malla").to_str() };
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Accelerate;

    return e;
}

void GameObjectFactory_t::crearMusgos(const picojson::array &musgos) const {
    for (size_t i {0}; i < static_cast<size_t>(musgos.size()); ++i) {
        createMusgo(musgos.at(i));
    } 
}

/****************************************************************************************************/
/********************************************HIELO***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createHielo(const picojson::value &hielo) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { hielo.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = 90;
    ph.zida = 0;
    ph.zvuelta = 0;

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { hielo.get("render") };
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    re.entityNodes.node.node->ShaderNode = 0;

    std::string modelo { render.get("malla").to_str() };
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Deccelerate;

    return e;
}

void GameObjectFactory_t::crearHielos(const picojson::array &hielos) const {
    for (size_t i {0}; i < static_cast<size_t>(hielos.size()); ++i) {
        createHielo(hielos.at(i));
    } 
}

/****************************************************************************************************/
/**********************************TUNELES Y FLOTANTES***********************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createPlanosEspeciales(const picojson::value &planoespecial) const{
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { planoespecial.get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { planoespecial.get("render") };

    std::string modelo { render.get("malla").to_str() };
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    re.entityNodes.node.node->ShaderNode = 0;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    const picojson::value collider { planoespecial.get("collider") };

    if (planoespecial.get("partes").to_str() != "null") {
        int i {0};

        while (planoespecial.get("partes").get(i).to_str() != "null") {
            float w { std::stof(planoespecial.get("partes").get(i).get("w").to_str()) };
            float h { std::stof(planoespecial.get("partes").get(i).get("h").to_str()) };
            float d { std::stof(planoespecial.get("partes").get(i).get("d").to_str()) };

            float disX { std::stof(planoespecial.get("partes").get(i).get("disX").to_str()) };
            float disY { std::stof(planoespecial.get("partes").get(i).get("disY").to_str()) };

            co.boxes.emplace_back(BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, true});

            ++i;
        }
    }

    co.properties = ColliderComponent_t::P_PlanoS;
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());    

    auto& so { m_EntMan.addComponent<SoundComponent_t>(e) };
    so.event_id = "event:/Efectos/Cueva/Agua";
    so.isEvent3D = false;
    so.marked_for_init = 1;
    so.marked_for_play = 0;
    so.alwaysPlay = true;

    m_EntMan.getBlackBoard().tunel_bb = &e;

    return e;
}

void  GameObjectFactory_t::crearPlanosEspeciales(const picojson::array &planosespeciales) const{
    for (size_t i {0}; i < static_cast<size_t>(planosespeciales.size()); ++i) {
        createPlanosEspeciales(planosespeciales.at(i));
    } 
}

/****************************************************************************************************/
/********************************************PLANO***************************************************/
/****************************************************************************************************/

void GameObjectFactory_t::crearPlano(const picojson::array &plano) const {
    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    const picojson::value fisica { plano.at(0).get("physics") };
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = std::stoi(fisica.get("roty").to_str());
    ph.zida = std::stof(fisica.get("zini").to_str());
    ph.zvuelta = std::stof(fisica.get("zvuelta").to_str());

    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    const picojson::value render { plano.at(0).get("render") };
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());

    std::string modelo { render.get("malla").to_str() };
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);
    re.entityNodes.node.node->setsegundoshader(false);

    re.entityNodes.node.node->ShaderNode = 2;

    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    co.properties = ColliderComponent_t::P_IsSolid;

    if (plano.at(0).get("partes").to_str() != "null") {
        int i {0};

        while (plano.at(0).get("partes").get(i).to_str() != "null") {
            float w { std::stof(plano.at(0).get("partes").get(i).get("w").to_str()) };
            float h { std::stof(plano.at(0).get("partes").get(i).get("h").to_str()) };
            float d { std::stof(plano.at(0).get("partes").get(i).get("d").to_str()) };

            float disX { std::stof(plano.at(0).get("partes").get(i).get("disX").to_str()) };
            float disY { std::stof(plano.at(0).get("partes").get(i).get("disY").to_str()) };            

            co.boxes.insert(co.boxes.begin()+i, BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, false});

            ++i;
        }
    }

    m_EntMan.getBlackBoard().xminM = (ph.x - (re.w/2)) - 100;
    m_EntMan.getBlackBoard().xmaxM = (ph.x + (re.w/2)) + 100;
    m_EntMan.getBlackBoard().yminM = (ph.y - (re.h/2)) - 100;
    m_EntMan.getBlackBoard().ymaxM = (ph.y + (re.h/2)) + 100;
    m_EntMan.getBlackBoard().wM = re.w;
    m_EntMan.getBlackBoard().hM = re.h;
}

/****************************************************************************************************/
/********************************************HUD*****************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createHud() const {
    auto wSize {motor->getWindowSize()};
    auto& e { m_EntMan.createEntity() };
    auto& bb { m_EntMan.getBlackBoard() };
    int crias {bb.criasennivel};
    auto& hud { m_EntMan.addComponent<HudComponent_t>(e) };

    if (wSize.y == 720)
    {
        hud.icon_stamina_  = motor->create2dSprite("assets/hud/stamina1.png", glm::vec2(1280*.4,1280*.4), glm::vec2(1280*.05,1280*.05));
        hud.phdr_stamina_  = motor->create2dSprite("assets/hud/stamina2.png",             glm::vec2(1280*.4,720*.4), glm::vec2(1280*.05,1280*.05));
        hud.icon_stamina_->setAlpha(1.0f);
        hud.phdr_stamina_->setAlpha(.5f);
        hud.icon_stamina_->setWindowSize(glm::vec2(1280,720));
        hud.phdr_stamina_->setWindowSize(glm::vec2(1280,720));

        for (size_t i {0}; i < hud.hearts_.size(); ++i)
        {
            hud.hearts_[i] = motor->create2dSprite("assets/hud/heart.png", glm::vec2(1280-(1280/10+i*80),720/100), glm::vec2(1280/10,1280/10));
            hud.hearts_[i]->setAlpha(1.f);
        }
        hud.zaris_.clear();
        for (size_t i {0}; i < static_cast<size_t>(crias-1); ++i)
        {
            hud.zaris_.push_back(motor->create2dSprite("assets/hud/zari.png",glm::vec2(1280+20-(1280/10+i*60),720/100+100), glm::vec2(1280/20,1280/20)));
            hud.zaris_[i]->setAlpha(1.f);
        }

        //hud.textosHUD_.at(0) = {"Puntos:", 1120.0, 500.0, 1.0, Vector3d{0.5f, 0.8f, 0.2f}};
        //hud.textosHUD_.at(1) = {"0", 1200.0, 500.0, 2.0, Vector3d{0.3f, 0.7f, 0.9f}};
        hud.textosHUD_.at(0) = {"Puntos:", 1090.0, 500.0, 1.0, Vector3d{1.0f, 0.039f, 0.125f}};
        hud.textosHUD_.at(1) = {"0", 1220.0, 500.0, 1.0, Vector3d{1.0f, 0.039f, 0.125f}};
    }

    else
    {
        hud.icon_stamina_  = motor->create2dSprite("assets/hud/stamina1.png", glm::vec2(1920*.4,1080*.4), glm::vec2(1920*.05,1920*.05));
        hud.phdr_stamina_  = motor->create2dSprite("assets/hud/stamina2.png", glm::vec2(1920*.4,1080*.4), glm::vec2(1920*.05,1920*.05));
        hud.icon_stamina_->setAlpha(1.0f);
        hud.phdr_stamina_->setAlpha(.5f);
        hud.icon_stamina_->setWindowSize(glm::vec2(1920,1080));
        hud.phdr_stamina_->setWindowSize(glm::vec2(1920,1080));

        for (size_t i {0}; i < static_cast<size_t>(hud.hearts_.size()); ++i)
        {
            hud.hearts_[i] = motor->create2dSprite("assets/hud/heart.png", glm::vec2(1760 - i*100, 0), glm::vec2(1920/10,1920/10));
            hud.hearts_[i]->setAlpha(1.f);
        }
        for (size_t i {0}; i < static_cast<size_t>(crias-1); ++i)
        {
            hud.zaris_.push_back(motor->create2dSprite("assets/hud/zari.png",glm::vec2(1920+40-(1920/10+i*80),1080/100+140), glm::vec2(1920/25,1920/25)));
            hud.zaris_[i]->setAlpha(1.f);
        }

        //hud.textosHUD_.at(0) = {"Puntos:", 1120.0, 500.0, 1.0, Vector3d{0.5f, 0.8f, 0.2f}};
        //hud.textosHUD_.at(1) = {"0", 1200.0, 500.0, 2.0, Vector3d{0.3f, 0.7f, 0.9f}};
        hud.textosHUD_.at(0) = {"Puntos:", 1090.0, 500.0, 1.0, Vector3d{1.0f, 0.039f, 0.125f}};
        hud.textosHUD_.at(1) = {"0", 1220.0, 500.0, 2.0, Vector3d{1.0f, 0.039f, 0.125f}};
    }
    return e;
}

void GameObjectFactory_t::createTerremoto(){

    terremoto_timer.count(true);
    if(terremoto_timer.getEllapsed()==8){
        auto& bb { m_EntMan.getBlackBoard() };
        if(!bb.salientes_bb.empty()){
            for(auto* saliente:  bb.salientes_bb){
                if(saliente){  
                    auto* sal_col { saliente->template getComponent<ColliderComponent_t>() };
                    if(sal_col){
                        for(auto &box_sal: sal_col->boxes){
                            if(box_sal.lanzadorrocas){
                                int tirar { rand() % 4 };
                                if(!tirar){
                                    auto* sal_phy { saliente->template getComponent<PhysicsComponent_t>() };
                                    //calculamos las casillas que caben en el saliente
                                    int cachos { static_cast<int>((box_sal.box.xRight - box_sal.box.xLeft)/24) };
                                    // elegimos un cacho aleatorio para poner la roca
                                    int cacho_ele { rand() % cachos };
                                    float suma_sal { (cacho_ele*24) + 6 + box_sal.box.xLeft };
                                    auto& nueva_roca { this->createRoca(sal_phy->x+box_sal.disX+suma_sal, sal_phy->y+box_sal.disY, sal_phy->z+5, 1, true, saliente->getEntityID()) };
                                    
                                    //std::cout<<"Numero de entidades en EM: "<<ectx.EM->getEntities().size()<<"\n";
                                }
                                break;
                            }
                        }
                    }
                }

            }
        }
    terremoto_timer.reset();
    }


}

/****************************************************************************************************/
/****************************************LECTURA DE JSON*********************************************/
/****************************************************************************************************/

void GameObjectFactory_t::loadLevelJSON(std::string_view filename, BehaviourTree_t* tree) const {

    //Mostrar Pantalla de carga
    auto sprite { motor->create2dSprite("assets/menus/1920x1080/loading.png",glm::vec2(0,0), motor->getWindowSize()) };

    motor->beginScene();
    motor->drawAll();
    motor->endScene();

    //abrir JSON
    std::ifstream file(filename.data());

    if (!file) { throw std::runtime_error("Imposible abrir JSON file\n"); }

    //leer JSON
    picojson::value json;
    file >> json;

    std::string err { picojson::get_last_error() };

    if (!err.empty()) { throw std::runtime_error(err); }

    const auto& root { json.get<picojson::object>() };

    const auto& player { root.at("player").get<picojson::array>() };
    const auto& enemies { root.at("enemies").get<picojson::array>() };
    const auto& meta { root.at("meta").get<picojson::array>() };
    const auto& arrow { root.at("arrow").get<picojson::array>() };

    const auto& salientes { root.at("salientes").get<picojson::array>() };
    const auto& nidos { root.at("nidos").get<picojson::array>() };
    const auto& crias { root.at("crias").get<picojson::array>() };
    const auto& arbustos { root.at("arbustos").get<picojson::array>() };
    const auto& cascadas { root.at("cascadas").get<picojson::array>() };
    const auto& semillas { root.at("semillas").get<picojson::array>() };
    const auto& enganches { root.at("enganches").get<picojson::array>() };
    const auto& agujeros { root.at("agujeros").get<picojson::array>() };
    const auto& trampolines { root.at("trampolines").get<picojson::array>() };
    const auto& palos { root.at("palos").get<picojson::array>() };

    const auto& plano { root.at("plano").get<picojson::array>() };

    const auto& musgos { root.at("musgos").get<picojson::array>() };
    const auto& hielos { root.at("hielos").get<picojson::array>() };

    const auto& planosespeciales { root.at("planosespeciales").get<picojson::array>() };

    //const auto& navMesh { root.at("navMesh").get<picojson::array>() };
    crearPlano(plano);
    auto& pl { createPlayer(player) };
    crearEnemigos(tree, enemies);
    createMeta(meta);
    createArrow(arrow);
    
    crearSalientes(salientes);
    crearNidos(nidos, crias);
    crearArbustos(arbustos);
    crearCascadas(cascadas);
    crearSemillas(semillas);
    crearEnganches(enganches);
    crearAgujeros(agujeros);
    crearTrampolines(trampolines);
    createPalosPlaces(palos);
    
    

    crearMusgos(musgos);
    crearHielos(hielos);

    crearPlanosEspeciales(planosespeciales);


    //Remover Sprite de carga
    motor->removeSprite(sprite);
}

ECS::Entity_t& GameObjectFactory_t::createNubes(int32_t x, int32_t y, int32_t z,ECS::EntityID_t player) const{

    auto& e { m_EntMan.createEntity() };

    auto& ph { m_EntMan.addComponent<PhysicsComponent_t>(e) };
    ph.x = x;
    ph.y = y;
    ph.z = z;
    auto& fo { m_EntMan.addComponent<FollowComponent_t>(e) };
    fo.x = 0;
    fo.z = z;
    fo.y = -300;
    fo.followEntityID = player;
    
    auto& re { m_EntMan.addComponent<RenderComponent_t>(e) };
    std::string modelo { "assets/modelados/nubes/nubes.obj" };
    auto& co { m_EntMan.addComponent<ColliderComponent_t>(e) };
    co.properties = ColliderComponent_t::P_IsSolid;

    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    re.entityNodes.node.node->ShaderNode = 4;
    return e;

}