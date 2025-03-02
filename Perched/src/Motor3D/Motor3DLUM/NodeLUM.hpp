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

#include "../Node.hpp"
#include "MaterialLUM.hpp"
#include "../Vector3d.hpp"
#include "EntityLUM.hpp"
#include <vector>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include <memory>
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}
#include "Shape.hpp"
#include "AnimationLUM.hpp"
#include "Resources/TextureManager.hpp"

struct AnimationLUM;

struct NodeLUM
{
    NodeLUM (const char*);
    NodeLUM (float);
    NodeLUM (){};
    ~NodeLUM() = default;
    void     remove      ();
    float    getX        ();
    float    getY        ();
    float    getZ        ();
    int      getNodeID   ();
    void     setID       (int);
    int      getSize     ();
    void     setPosition (Vector3d);
    void     setTarget   (Vector3d);
    Vector3d getPosition ();

    std::vector<std::unique_ptr<AnimationLUM>> animations_;
    std::vector<std::string> nomsAnimation_;
    void setAnimation(const std::string& path, int inicial);
    bool animCopiada {false};

    /* New Motor Implementations */
    int numanimation {0};
    int numframe {0};
    bool segundoshader {true};
    void setsegundoshader(bool a){ segundoshader = a;};
    bool getsegundoshader(){return segundoshader;};
    void ActualizarAnimation(const std::string& nomAnim);
    void ActualizarFrame(int dura);
    int getActualFrame();
    int getFinalFrame();
    void ResetFrame();
    void setFrame(int frame);

    std::string getAnimation(){ return nomsAnimation_.at(numanimation);};
    
    // Parent and Children nodes
    int      addChild       (NodeLUM*);
    int      removeChild    (NodeLUM*);
    void     removeChildren ();
    NodeLUM* getParent      ();
    bool     setParent      (NodeLUM*);
    NodeLUM* camNode_;
    
    // Entity related to node
    bool        setEntity (EntityLUM*);
    EntityLUM*  getEntity ();
    //LookFor
    void      loopThrough   (glm::mat4 const &, Shader&);
    glm::mat4 calculateMat  ();

    // Setters for initial traslation, rotation and scale
    void setTranslation (Vector3d);
    void setRotation    (Vector3d);
    void setScale       (Vector3d);
    
    // Traslate, rotate and sclae modifiers
    void translate   (Vector3d);
    void scale       (Vector3d);
    void rotate      (Vector3d);
    void setMaterial (float, float);

    // Getters
    Vector3d    getTranslation ();
    Vector3d    getRotation    ();
    Vector3d    getScale       ();
    Vector3d    getTarget      ();
    MaterialLUM  & getMaterial    ();

    void setMatrixTrans         (glm::mat4 const &);
    glm::mat4 const & getMTrans ();
    float     getAlpha          ();
    void      setAlpha          (float);
    void      setNodeShader     (int);
    /*frustum issues*/
    bool isNodeOnFrustum(NodeLUM*, glm::mat4 const & mat);
    NodeLUM* getCamera(){return camNode_;}
    int                        ShaderNode{};
    void setTMan(TextureManager * tm){tm_=tm;}

private:
    
    float                      X,
    /*float*/                  Y,
    /*float*/                  Z;
    float                      size;
    float                      alpha_{1.f};
    EntityLUM*                 entity;
    std::vector<NodeLUM*>      children;
    NodeLUM*                   parent {nullptr}; 
    int                        id;
    bool                       updateMat{true};
    glm::vec3                  target;
    glm::vec3                  translation  {0.0f,0.0f,0.0f};
    glm::vec3                  rotation     {0.0f,0.0f,0.0f};
    glm::vec3                  scalation    {1.0f,1.0f,1.0f};
    glm::mat4                  matTrans     {1.0f};
    MaterialLUM                material     {0.9,0.7}; //Provisional

    TextureManager * tm_;

    int duracion {0};
};
