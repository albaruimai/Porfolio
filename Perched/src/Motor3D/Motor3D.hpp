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

//#pragma once
//
//#include "Node.hpp"
//#include "EventReceiver.hpp"
//#include <iostream>
//#include <memory>
//#include <vector>
//
//#include "Motor3DLUM/AnimationLUM.hpp"
//#include "../util/typealiases.hpp"
//
//struct Motor3D
//{
//    /* Bucle de renderizado */
//    ~Motor3D(){};
//    virtual bool run()        = 0;
//    virtual void beginScene() = 0;
//    virtual void endScene()   = 0;
//    virtual void drawAll()    = 0;
//    virtual void dropDevice() = 0;
//
//    /* Camaras */
//    virtual Node* createCamera(Vector3d,Vector3d)  = 0;
//    virtual bool  removeCamera(Node*)              = 0;
//    
//    /* Nodos (Cajas y meshes) */    
//    virtual Node* createCubeNode(float size)           = 0;
//    virtual Node* createMeshNode(std::string const &path, bool gamma) = 0;
//    virtual bool  removeNode(Node*)                    = 0;
//    virtual bool  clearNodes   ()                      = 0;
//      
//    /* Texturas*/     
//    //virtual Texture* getTexture(const char* path)  = 0;
//    //virtual bool  setTexture (const wchar_t*, int) = 0;
//
//    /* Texto */
//    virtual void addStaticText(const wchar_t*, int, int, int, int) = 0;
//    virtual void addText(std::string, int, int, int, int)          = 0;
//
//
//    /* Tiempo */
//    virtual int getTime()                = 0;
//    virtual int getFPS ()                = 0;
//    /*Event Receiver*/ 
//    virtual EventReceiver* getReceiver() = 0;
//    virtual Node* getCamera() = 0;
//
//    //Vertices e Indices
//    virtual std::vector<Vector3d> getNodeVertices(Node*) = 0;
//    virtual std::vector<unsigned int> getNodeIndexes(Node *) = 0;
//
//    //Materiales
//    virtual void setMaterialToNode(Node*, float, float) = 0;
//    virtual GLFWwindow* getWindow() = 0;
//
//    //Set Animations
//    virtual void loadAnimations(std::vector<std::string>, std::vector<std::string>, std::vector<int>) = 0;
//
//    virtual ECS::Hash_t<std::string, std::unique_ptr<AnimationLUM>>* getAnimationMap() = 0;
//
//    virtual void setAnimationToNode(Node* nodo, std::string nombre) = 0;
//};
//


