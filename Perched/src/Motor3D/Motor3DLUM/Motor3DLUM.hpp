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

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include "../../util/MyKeycodes.h"
 
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
    #include <GLFW/glfw3native.h>    
}
#include "Shaders/Shader.hpp"
#include "Resources/ResourceManager.hpp"
#include "../Motor3D.hpp"
#include "NodeLUM.hpp"
#include "CameraLUM.hpp"
#include "ModelLUM.hpp"
#include "LightLUM.hpp"
#include <exception>
#include <iostream>
#include <chrono>
#include "AnimationLUM.hpp"
#include "TextLUM.hpp"
#include "Sprite2D/SpriteRenderer.hpp"
#include "ParticleSystem/ParticleSys.hpp"
#include "../../util/typealiases.hpp"
#include "../EventReceiver.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
struct Motor3DLUM
{   
    Motor3DLUM  (uint32_t, uint32_t);
    ~Motor3DLUM ();
    uint32_t skyVAO{};

    /* Bucle */
    
    void beginScene ();
    void endScene   ();
    bool run        (); 
    void drawAll    ();
    void dropDevice ();

    void winClean    ();
    void preRenderer ();
    void renderer3D  ();
    void renderer2D  ();

    void showFPS(bool);

    /* Nodos, camaras y texto */
   
    NodeLUM*         createCamera     (Vector3d,Vector3d);
    NodeLUM*         createLight      (Vector3d,Vector3d);
    void             addStaticText    (const wchar_t*, int, int, int, int);
    void             addText          (const std::string&, int, int, int, int);
    NodeLUM*         createCubeNode   (float);
    NodeLUM*         createMeshNode   (const std::string& path, bool gamma);
    NodeLUM*         createSphereNode (float);
    NodeLUM*         drawA3DLine      (float,float,float,float);
    SpriteRenderer*  create2dSprite   (const std::string&, const glm::vec2 &, const glm::vec2 &);
    ParticleSys*     createParticlSys (const glm::vec2 &, const glm::vec2 &, uint32_t amount, ParticleType);

    //Texture* getTexture       (const char*);
    //bool     setTexture       (const char*, int);
    uint32_t loadCubeMap(std::vector<std::string> faces);
    uint32_t createskybox(int i);
    std::vector<std::unique_ptr<NodeLUM>> nodes_;
    bool removeNode   (NodeLUM*);
    bool clearNodes   ();
    bool removeCamera (NodeLUM*);
    bool removeSprite (SpriteRenderer*);
    bool clearSprites ();
    bool removeSpriteByTexture (const std::string&);
    EventReceiver* getReceiver();
    void enableParticleSys();
    void disableParticleSys();
    /* Tiempo */
    int getTime();
    int & getFPS ();

    NodeLUM* getCamera();
    void processInput(GLFWwindow *window);
    GLFWwindow* getWindow();
    glm::vec2   getWindowSize();

    TextLUM* getCreatorText();

    // Vertecies e Indices
    std::vector<Vector3d> getNodeVertices (NodeLUM*);
    std::vector<uint32_t> getNodeIndexes  (NodeLUM*);

    //Set Animations
    void loadAnimations(std::vector<std::string> const &, std::vector<std::string> const &, std::vector<int> const &, std::vector<int> const &);
    void loadAnimation(const std::string&, const std::string&, int const &, int const &);
    void setMapAnimatonSize(int size);

    ECS::Hash_t<std::string, std::unique_ptr<AnimationLUM>>* getAnimationMap();

    void setAnimationToNode(NodeLUM* node, const std::string& nombre, bool copiar = false);
    NodeLUM* light;
    int cambiociclo{0};
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void setFramebuffer();
    void setSkybox();
    TextureManager * getTMan(){return &tManager_;}

    bool Menusombras{false};
    bool sombras{false};
    bool Menunubes{false};
    bool nubes{false};
    bool Menuparticulas{false};
    bool particulas{false};

    private:
        uint32_t width_{}, height_{};
        GLFWwindow* window_;
        EventReceiver eventR_;
    
        ResourceManager rm_;
        NodeLUM* camera_;
        int fps_ {0};
        int s_   {0};
        TextLUM creatortexts_{};

        /* Camera and movement callback functions (OpenGL) */
        Shader txShader_{};
        Shader render_{};
        Shader plane_{};
        Shader volume_{};
        Shader comp_{};
        Shader hudShader_{};
        Shader skyshad_{};
        Shader noche_{};
        Shader nubes_{};
        void daytime();
        void nighttime();
        
        
        
        ParticleSys* p;
        uint32_t box{};
        uint32_t box2{};
        uint32_t box3{};

        uint32_t texturesky{};
        
        glm::mat4 projection{};
        glm::mat4 view{};
        glm::vec4 lipos{};
        GLuint diffSpecTex{};
        GLuint colorDepthFBO{};
        
        TextureManager  tManager_{};
        bool firstMouse {true};
        float lastX_ {width_/2.0f};
        float lastY_ {height_/2.0f};
        float deltaTime_ {0.0f};
        float lastFrame_ {0.0f};
        
        /* Camera and movement callback functions (OpenGL) */
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        /* Set Material*/
        void setMaterialToNode(NodeLUM*, float, float);
        ECS::Hash_t<std::string, std::unique_ptr<AnimationLUM>> mapAnimation;

        glm::mat4 model {1.0f};

        NodeLUM* camNode {nullptr};
        float currentFrame;
        LightLUM* li {nullptr};
        CameraLUM* camEntity {nullptr};

        // VAO SCHERMO
	    GLfloat verts[12] { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f };

        float skyboxVertices[108] {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };

};