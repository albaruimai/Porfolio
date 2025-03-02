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

#include "Motor3DLUM.hpp"
#include "../../stb/stb_image.h"

Motor3DLUM::Motor3DLUM(uint32_t w, uint32_t h) : width_{w}, height_{h}, p{nullptr}
{    
    //std::cout << "CREO UN MOTOR\n";
    glfwInit(); //marcar
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    window_ = glfwCreateWindow (
        width_,
        height_,
        "Perched!",
        glfwGetPrimaryMonitor(),
        NULL
    );
    
    if (window_ == NULL)
    {
        //std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window_);
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    glfwSetCursorPosCallback(window_, GLFWcursorposfun(mouse_callback));
    glfwSetScrollCallback(window_, GLFWscrollfun(scroll_callback));
    // tell GLFW to capture our mouse
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    GLFWimage images[1]; 
    images[0].pixels = stbi_load("assets/logo.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(window_, 1, images); 
    stbi_image_free(images[0].pixels);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD :: Motor3DLUM.cpp:33" << std::endl;
    }

    setFramebuffer();
    setSkybox();

    render_.createShader(
        "src/Motor3D/Motor3DLUM/Shaders/sombras/render.vert",
        "src/Motor3D/Motor3DLUM/Shaders/sombras/render.frag"
    );
    plane_.createShader(
        "src/Motor3D/Motor3DLUM/Shaders/sombras/plane.vert",
        "src/Motor3D/Motor3DLUM/Shaders/sombras/plane.frag"
    );
    txShader_.createShader
    (
        "src/Motor3D/Motor3DLUM/Shaders/text.vs",
        "src/Motor3D/Motor3DLUM/Shaders/text.fs"
    );
    skyshad_.createShader(
          "src/Motor3D/Motor3DLUM/Shaders/skybox/sky.vert",
        "src/Motor3D/Motor3DLUM/Shaders/skybox/sky.frag"
    );
    nubes_.createShader(
          "src/Motor3D/Motor3DLUM/Shaders/Nubes/nubes.vert",
        "src/Motor3D/Motor3DLUM/Shaders/Nubes/nubes.frag"
    );

    creatortexts_ = TextLUM(txShader_, width_, height_);
    volume_.createShader(
        "src/Motor3D/Motor3DLUM/Shaders/sombras/volume.vert",
        "src/Motor3D/Motor3DLUM/Shaders/sombras/volume.frag",
        "src/Motor3D/Motor3DLUM/Shaders/sombras/volume.geom"
    );
    comp_.createShader(
        "src/Motor3D/Motor3DLUM/Shaders/sombras/comp.vert",
        "src/Motor3D/Motor3DLUM/Shaders/sombras/comp.frag"
    );

    hudShader_.createShader(
        "src/Motor3D/Motor3DLUM/Shaders/Shader.vs",
        "src/Motor3D/Motor3DLUM/Shaders/Shader.fs"
    );
    noche_.createShader(
        "src/Motor3D/Motor3DLUM/Shaders/noche/noche.vert",
        "src/Motor3D/Motor3DLUM/Shaders/noche/noche.frag"

    );
        
    eventR_ = EventReceiver(window_);
    camera_ = createCamera(Vector3d(210,50,95),Vector3d(0,0,0));
    light = createLight(Vector3d(1000.0f,1000.0f,200.0f),Vector3d(0.990f, 0.948f, 0.851f));
        // build and compile shaders
    
    box = createskybox(0);
    box2 = createskybox(1);
    box3 = createskybox(2);
}

void Motor3DLUM::setMapAnimatonSize(int size) {
    mapAnimation.reserve(size);
}

Motor3DLUM::~Motor3DLUM()
{
    camera_ = nullptr;
    window_ = nullptr;
    glDeleteProgram(render_.ID);
    glDeleteProgram(plane_.ID);
    glDeleteProgram(volume_.ID);
    glDeleteProgram(comp_.ID);
    

    glDeleteProgram(txShader_.ID);
    glDeleteProgram(hudShader_.ID);
    glDeleteProgram(skyshad_.ID);
    glDeleteProgram(noche_.ID);
    glDeleteProgram(nubes_.ID);

    //std::cout << "Deleting Engine\n";
    
    glfwTerminate();
}
/* Bucle */

void Motor3DLUM::beginScene ()
{
 	// CLEAR COLOR, DEPTH E STENCIL
}
void Motor3DLUM::endScene ()
{
    if (window_!=nullptr)
    {
        glfwSwapBuffers(window_); //NO TOCAR JAMAS DE LOS JAMASES
        glfwPollEvents();
    }
    else
    {
        //std::cout << "For any reason, the window pointer is being set to nullptr\n";
    }
    
}

bool Motor3DLUM::run ()
{
    if (!glfwWindowShouldClose(window_))
    {
        
        return true;
    }
    return false;
}

int lastfps {0};
uint32_t conti {0};

void Motor3DLUM::drawAll ()
{
    renderer3D   ();
    renderer2D   ();
    showFPS  (true);
}

void Motor3DLUM::winClean()
{
    processInput(window_);
    glClearColor(0.475f, 0.836f, 0.990f, 1.0f);
    if (cambiociclo!=0) glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Motor3DLUM::showFPS(bool b)
{
    ++fps_;
    if (s_ < getTime() || getTime() == 0 && s_ > 0)
    {
        if (b)
        {
            //std::cout << "FPS = " << fps_ << "\n";
        }
        fps_ = 0;
    }
    s_ = getTime();
}



void Motor3DLUM::renderer3D ()
{
    camNode = static_cast<NodeLUM*>(camera_);
    currentFrame = static_cast<float>(glfwGetTime());
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;
    winClean();
    
    /* set uniforms */
    li = static_cast<LightLUM*>(light->getEntity());
    camNode->calculateMat();
    camEntity = static_cast<CameraLUM*>(camera_->getEntity());
    
    /* set perspective */
    glm::mat4 projection {
        glm::perspective
        (
            glm::radians(90.0f),
            static_cast<float>(width_) / static_cast<float>(height_),
            0.1f,
            1000.0f
        )
    };
    camEntity->setPerspective(projection);
    glm::mat4 view {
        glm::inverse(camNode->getMTrans())
    };
      
    glm::vec3 luzpos {
        light->getPosition().getVectorX(),
        light->getPosition().getVectorY(),
        light->getPosition().getVectorZ()
    };

  


    /* day-night pre-modifications */
    glDepthMask(GL_TRUE);
	if (cambiociclo!=0 && cambiociclo!=2)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);   
    }

  

    if (cambiociclo!=0 && cambiociclo!=2)
    {
        noche_.use();
        noche_.setVec3("light.position",glm::vec3(camera_->getX(),camera_->getY(),40));
        noche_.setVec3("viewPos",glm::vec3(camEntity->Position.x,camEntity->Position.y,20));
        // light properties
        noche_.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        // we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
        // each environment and lighting type requires some tweaking to get the best out of your environment.
        noche_.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        noche_.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        noche_.setFloat("light.constant", 1.0f);
        noche_.setFloat("light.linear", 0.09f);
        noche_.setFloat("light.quadratic", 0.032f);
        // material properties
        noche_.setFloat("material.shininess", 10.0f);
        // view/projection transformations
        noche_.setMat4("projection", projection);
        noche_.setMat4("view", view);
	    noche_.setMat3("NormalMatrix", glm::mat3(glm::vec3(view[0]), glm::vec3(view[1]), glm::vec3(view[2])));
	    noche_.setFloat("LightIntensity",li->intensity);
        // world transformation
        model = glm::mat4(1.0f);
        noche_.setMat4("model", model);
    }
    else
    {
        render_.use();
        render_.setMat4("projection", projection);
        render_.setMat4("view",view);
	    render_.setMat3("NormalMatrix", glm::mat3(glm::vec3(view[0]), glm::vec3(view[1]), glm::vec3(view[2])));
	    render_.setVec3("LightPosition",luzpos);
	    render_.setFloat("LightIntensity",li->intensity);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, colorDepthFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    /* node rendering */

    std::vector<int> opqNodes;
    if (cambiociclo!=0 && cambiociclo!=2)
    {
        for(size_t i {0}; i < static_cast<size_t>(nodes_.size()); ++i){
            nodes_[i]->camNode_ = static_cast<NodeLUM*>(camera_);
            if(nodes_[i]->getAlpha()==1 && nodes_[i]->ShaderNode!=4)
            {    
                nodes_[i].get()->loopThrough(model,noche_);
            }   
            else
            {
                opqNodes.push_back(i);
            }
        }  
    }
    else
    {
        for(size_t i {0}; i < static_cast<size_t>(nodes_.size()); ++i){
            nodes_[i]->camNode_ = static_cast<NodeLUM*>(camera_);
            if(nodes_[i]->ShaderNode!=2 && nodes_[i]->ShaderNode!=3 && nodes_[i]->ShaderNode!=4 && nodes_[i]->getAlpha()==1)
            {    
                nodes_[i]->loopThrough(model,render_);
            }   
            else
            {
                opqNodes.push_back(i);
            }
        }
        plane_.use();
	    plane_.setMat4("projection", projection);
        plane_.setMat4("view",view);
	    plane_.setMat3("NormalMatrix", glm::mat3(glm::vec3(view[0]), glm::vec3(view[1]), glm::vec3(view[2])));
	    plane_.setVec3("u_color", 1.0f, 1.0f, 1.0f);
	    plane_.setVec3("LightPosition", luzpos);
	    plane_.setFloat("LightIntensity",li->intensity);
        for (size_t i {0}; i < static_cast<size_t>(opqNodes.size()); ++i)
        {
             if(nodes_[opqNodes[i]]->ShaderNode!=4)
            {   
            nodes_[opqNodes[i]]->loopThrough(model,plane_);
            }
        }
    }
       
    glDisable(GL_CULL_FACE);
    glBindVertexArray(0);        
    glBindFramebuffer(GL_READ_FRAMEBUFFER, colorDepthFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, width_,height_, 0, 0,width_,height_, GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT, GL_NEAREST);
       
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	
	glEnable(GL_DEPTH_CLAMP);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, 0xff);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);

    if (cambiociclo==0 || cambiociclo==2)
   
        {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        volume_.use();   
        volume_.setMat4("view", view);
        volume_.setVec3("LightPosition",luzpos);
        volume_.setMat4("ProjMatrix",projection);
    
    if(Menusombras == true){ //esto se modifica desde settings menu

            for(size_t i {0}; i < static_cast<size_t>(nodes_.size()); ++i){
                if(nodes_[i]->ShaderNode==1 && nodes_[i]->ShaderNode!=4 && nodes_[i]->getAlpha()==1)
                {    
                    nodes_[i].get()->loopThrough(model,volume_);
                }   
                else
                {
                    opqNodes.push_back(i);
                } 
            }
        }
    }

    glDisable(GL_DEPTH_CLAMP);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    
    // TERZO PASSO
    // DISEGNO LA COMPONENTE DIFFUSA SECONDO LO STENCIL BUFFER
    
    glDisable(GL_DEPTH_TEST);
    glStencilFunc(GL_EQUAL, 0, 0xffff);
    if (cambiociclo==0 || cambiociclo==2)
    {
        comp_.use();
        comp_.setVec3("LightColor",li->lightColor);
    }
    
    glBindVertexArray(1);
    glBindTexture(GL_TEXTURE_2D, diffSpecTex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glDisable(GL_DEPTH_TEST);
    
     glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(Menunubes == true && nubes == true){
        nubes_.use();
        nubes_.setMat3("NormalMatrix", glm::mat3(glm::vec3(view[0]), glm::vec3(view[1]), glm::vec3(view[2])));
		nubes_.setVec3("LightPos",luzpos);
	    nubes_.setFloat("LightIntensity",li->intensity);
        nubes_.setMat4("projection", projection);
        nubes_.setMat4("view", view);
        nubes_.setInt("TIME_FROM_INIT",conti); 
		++conti;
        if(conti==1000){
            conti=0;
        }
         
        for(size_t i {0}; i < static_cast<size_t>(nodes_.size()); ++i){
            if(nodes_[i]->ShaderNode==4)
            {    
               nodes_[i].get()->loopThrough(model,nubes_);
              
            }   
           
        }
    }
    glDisable(GL_BLEND);
    
      glEnable(GL_DEPTH_TEST);
     glDepthFunc(GL_LESS);



    glDepthFunc(GL_LEQUAL);
    skyshad_.use();
    // change depth function so depth test passes when values are equal to depth buffer's content

    glm::mat4 view2 { glm::mat4(glm::mat3(camEntity->GetViewMatrix()))}; // remove translation from the view matrix
    skyshad_.setMat4("view", view2);
    skyshad_.setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(texturesky);
   
    skyshad_.setInt("skybox", 0);
    glActiveTexture(GL_TEXTURE0);

    switch (cambiociclo) {
        case 0:
            glBindTexture(GL_TEXTURE_CUBE_MAP,box);
            break;
        case 1:
            glBindTexture(GL_TEXTURE_CUBE_MAP,box3);
            break;
        case 2:
            glBindTexture(GL_TEXTURE_CUBE_MAP,box2);
            break;
    }
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default   
    
    
   

    glm::mat4 projViewMod {projection*view};
    camEntity->calculateFrustrum(projViewMod);
}

void Motor3DLUM::renderer2D ()
{
 
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    hudShader_.use();
    
    glm::mat4 gui { glm::ortho(0.0f, static_cast<float>(width_), static_cast<float>(height_), 0.0f, -1.0f, 1.0f) };
    if(p!=nullptr){
        p->update();
    }
    hudShader_.setMat4("projection", gui);
    for ( size_t i{}; i < static_cast<size_t>(rm_.sprites_.size()); ++i )
    {
        if ( rm_.sprites_[i]->getPosition().x>=0.f
          && rm_.sprites_[i]->getPosition().x<=static_cast<float>(width_)
          && rm_.sprites_[i]->getPosition().y>=0.f
          && rm_.sprites_[i]->getPosition().y<=static_cast<float>(height_))
        {
            hudShader_.setFloat("alpha", rm_.sprites_[i]->getAlpha());
            rm_.sprites_[i]->DrawSprite(hudShader_);
        }
    }
   
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);   

  
}

void Motor3DLUM::dropDevice ()
{

}
/* Nodos, camaras y texto */
NodeLUM* Motor3DLUM::createCamera (Vector3d pos,Vector3d up)
{
    glm::vec3 a {pos.getVectorX(), pos.getVectorY(), pos.getVectorZ()};
    glm::vec3 b {up.getVectorX(), up.getVectorY(), up.getVectorZ()};

    rm_.cameras_.push_back(std::make_unique<CameraLUM>(a,b));
    nodes_.push_back(std::make_unique<NodeLUM>(1.0f));
    nodes_[nodes_.size()-1]->setEntity(rm_.cameras_[rm_.cameras_.size()-1].get());
    nodes_[nodes_.size()-1]->setTranslation(pos);
    camera_ = nodes_[nodes_.size()-1].get();
    return nodes_[nodes_.size()-1].get();
}

NodeLUM* Motor3DLUM::createLight (Vector3d pos,Vector3d color){
    glm::vec3 a {pos.getVectorX(), pos.getVectorY(), pos.getVectorZ()};
    glm::vec3 b {color.getVectorX(), color.getVectorY(), color.getVectorZ()};

    rm_.lights_.push_back(std::make_unique<LightLUM>(a,b));
    nodes_.push_back(std::make_unique<NodeLUM>(1.0f));
    nodes_[nodes_.size()-1]->setEntity(rm_.lights_[rm_.lights_.size()-1].get());
    nodes_[nodes_.size()-1]->setTranslation(pos);
    light = nodes_[nodes_.size()-1].get();
    return nodes_[nodes_.size()-1].get();
}

void  Motor3DLUM::addStaticText (const wchar_t*, int, int, int, int)
{

}
void  Motor3DLUM::addText (const std::string&, int, int, int, int)
{

}

TextLUM* Motor3DLUM::getCreatorText() {
    return &creatortexts_;
}

NodeLUM* Motor3DLUM::createCubeNode (float size)
{
    auto aux { rm_.modelLoaded("assets/pruebi2.obj") };
    if (aux!=nullptr)
    {
        nodes_.push_back(std::make_unique<NodeLUM>());
        nodes_[nodes_.size()-1]->setEntity(aux);
        nodes_[nodes_.size()-1]->setTMan(&tManager_);
    }
    else
    {
        rm_.models_.push_back(std::make_unique<ModelLUM>("assets/pruebi2.obj",false, &tManager_));
        nodes_.push_back(std::make_unique<NodeLUM>());
        nodes_[nodes_.size()-1]->setEntity(rm_.models_[rm_.models_.size()-1].get());
        nodes_[nodes_.size()-1]->setTMan(&tManager_);
    }
    return nodes_[nodes_.size()-1].get(); 
}
NodeLUM* Motor3DLUM::createMeshNode (const std::string& path, bool gamma)
{
    auto aux { rm_.modelLoaded(path) };
    if (aux!=nullptr)
    {
        auto& node_i  {nodes_.emplace_back(std::make_unique<NodeLUM>())};
        node_i->setEntity(aux);
        node_i->setTMan(&tManager_);
        return node_i.get();
    }
    else
    {
        auto& model_i {rm_.models_.emplace_back(std::make_unique<ModelLUM>(path,gamma, &tManager_))};
        auto& node_i  {nodes_.emplace_back(std::make_unique<NodeLUM>())};
        node_i->setEntity(model_i.get());
        node_i->setTMan(&tManager_);
        return node_i.get();
    }
}

SpriteRenderer* Motor3DLUM::create2dSprite(const std::string & path, const glm::vec2 & position, const glm::vec2 & size)
{
    if (rm_.texs2D_.find(path) == rm_.texs2D_.end())
    {
        Texture2D texture {};
        texture.loadTexture(path);
        rm_.texs2D_.insert({path,texture});
        auto& tex {rm_.texs2D_[path]};
        auto& sp {rm_.sprites_.emplace_back(std::make_unique<SpriteRenderer>(&tex,position,size))};
        sp->setWindowSize(glm::vec2{width_,height_});
        return sp.get();
    }
    else
    {
        auto& tex {rm_.texs2D_[path]};
        auto& sp {rm_.sprites_.emplace_back(std::make_unique<SpriteRenderer>(&tex,position,size))};
        sp->setWindowSize(glm::vec2{width_,height_});
        return sp.get();
    }
}

ParticleSys* Motor3DLUM::createParticlSys (const glm::vec2 & pos, const glm::vec2 & size, uint32_t amount, ParticleType p)
{
    std::vector<SpriteRenderer * > particles;
    particles.reserve(amount);

    switch (p) {
        case ParticleType::SNOW:
            for (size_t i {0}; i < amount; ++i)
            {
                auto sprite {create2dSprite("assets/snowflake2.png",pos,size)};
                particles.push_back(sprite);
            }
            break;

        case ParticleType::RAIN:
            for (size_t i {0}; i < amount; ++i)
            {
                auto sprite {create2dSprite("assets/snowflake2.png",pos,glm::vec2(4.f, size.y))};
                particles.push_back(sprite);
            }
            break;

        default:
            //std::cout << "WARNING, PARTICLE SYSTEM NOT VALID. SNOW SYSTEM WAS CREATED INSTEAD.\n";
            for (size_t i {0}; i < amount; ++i)
            {
                auto sprite {create2dSprite("assets/snowflake2.png",pos,size)};
                particles.push_back(sprite);
            }
            break;
    }
    
    auto& partSystem {rm_.partSys_.emplace_back(std::make_unique<ParticleSys>(particles, amount, p))};
    return partSystem.get();
}
void Motor3DLUM::enableParticleSys()
{
    if (p==nullptr)
    {
        p = createParticlSys(glm::vec2(width_,height_),glm::vec2(15.f),1000, ParticleType::SNOW);        
    }
}
void Motor3DLUM::disableParticleSys()
{
    if (p!=nullptr)
    {
        for (size_t i = 0; i < rm_.sprites_.size(); i++)
        {
            for (size_t j = 0; j < p->sprite_.size(); j++)
            {
                if (rm_.sprites_[i].get() == p->sprite_[j])
                {
                    rm_.sprites_.erase(rm_.sprites_.begin()+i);
                    if (i>0)
                    {
                        i--;
                    }
                }
            }
        }
    }
    p=nullptr;
}
bool Motor3DLUM::removeNode (NodeLUM* n)
{
    for (size_t i {0}; i < static_cast<size_t>(nodes_.size()); ++i)
    {
        if(nodes_[i].get()==n){
            for (size_t j {0}; j < static_cast<size_t>(nodes_[i].get()->animations_.size()); ++j)
            {
                mapAnimation.at(nodes_[i].get()->nomsAnimation_[j]) = std::move(nodes_[i].get()->animations_[j]);
            }
            nodes_.erase(nodes_.begin()+i);
        }
    }
    
    return false;
}

bool Motor3DLUM::clearNodes () {
    for (size_t i { nodes_.size()-1 }; i > 0 ; --i)
    {
        if ((nodes_[i].get() != camera_) && (nodes_[i].get() != light)) {
            for (size_t j {}; j < static_cast<size_t>(nodes_[i]->animations_.size()); ++j)
            {
                mapAnimation.at(nodes_[i]->nomsAnimation_[j]) = std::move(nodes_[i]->animations_[j]);
            }
            nodes_.erase(nodes_.begin()+i);
        }
    }
    return false;
}

bool Motor3DLUM::removeCamera (NodeLUM*)
{
    return false;
}

bool Motor3DLUM::removeSprite (SpriteRenderer* s)
{
    bool b{false};

    for (size_t i{0}; i < rm_.sprites_.size(); ++i)
    {
        if (s==rm_.sprites_[i].get())
        {
            //std::cout << "He borrado un sprite con la textura: " << rm_.sprites_[i]->getTexture()->path_ << " " << i << " \n";
            rm_.sprites_.erase(rm_.sprites_.begin() + i);
            return true;
        }
        
    }
    return b;
}

bool Motor3DLUM::clearSprites ()
{
    rm_.sprites_.clear();
    return true;
}

EventReceiver* Motor3DLUM::getReceiver()
{
    return &eventR_;
}

bool Motor3DLUM::removeSpriteByTexture (const std::string & first)
{
    auto tex {rm_.textureLoaded(first)};
    bool b{false};
    if (tex!=nullptr)
    {
        for (size_t i {0}; i < rm_.sprites_.size(); ++i)
        {
            SpriteRenderer * sp {rm_.sprites_[i].get()};
            if (sp->getTexture() == tex)
            {
                b = removeSprite(sp);
            }
        }
    }
    return b;
}

/* Tiempo */
int Motor3DLUM::getTime()
{
    time_t lhs { time (NULL) };
    time_t rhs {10*(lhs/10)};
    int s {static_cast<int>(lhs-rhs)};
    return s;
}
int & Motor3DLUM::getFPS()
{
    return fps_;
}
NodeLUM* Motor3DLUM::getCamera()
{
    return camera_;
}

GLFWwindow* Motor3DLUM::getWindow()
{
    return window_;
}

glm::vec2 Motor3DLUM::getWindowSize()
{
    return glm::vec2(width_,height_);
}

/* OpenGL Functions */
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Motor3DLUM::setFramebuffer()
{
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

   // DEPTH BUFFER
	GLuint depthBuf;
	glGenRenderbuffers(1, &depthBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,width_,height_);

	// AMBIENT BUFFER
	GLuint ambBuf;
	glGenRenderbuffers(1, &ambBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, ambBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA,width_,height_);

	// DIFFUSE COMPONENT

	glGenTextures(1, &diffSpecTex);
	glBindTexture(GL_TEXTURE_2D, diffSpecTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8,width_, height_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	colorDepthFBO = 0;

	// FBO
	glGenFramebuffers(1, &colorDepthFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, colorDepthFBO);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, ambBuf);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, diffSpecTex, 0);

	GLenum drawBuffers[] { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, drawBuffers);

	GLenum result { glCheckFramebufferStatus(GL_FRAMEBUFFER) };
	if (result == GL_FRAMEBUFFER_COMPLETE) {
		//printf("Framebuffer is complete.\n");
	}
	else {
		//printf("Framebuffer is not complete.\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Motor3DLUM::setSkybox()
{
	GLuint bufHandle;
	glGenBuffers(1, &bufHandle);
	glBindBuffer(GL_ARRAY_BUFFER, bufHandle);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	GLuint fsQuad { 1 };
	glGenVertexArrays(1, &fsQuad);
	glBindVertexArray(fsQuad);

	glBindBuffer(GL_ARRAY_BUFFER, bufHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

    uint32_t skyboxVAO, skyboxVBO;
  
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    texturesky = skyboxVAO;
}

void Motor3DLUM::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    Motor3DLUM* m { static_cast<Motor3DLUM*>(glfwGetWindowUserPointer(window)) };
    m->width_=width;
    m->height_=height;
}
 
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------

void Motor3DLUM::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if(window){
        Motor3DLUM* m { static_cast<Motor3DLUM*>(glfwGetWindowUserPointer(window)) };

        if(m){
            float xpos { static_cast<float>(xposIn) };
            float ypos { static_cast<float>(yposIn) };
            if (m->firstMouse)
            {
                m->lastX_ = xpos;
                m->lastY_ = ypos;
                m->firstMouse = false;
            }
            
            float xoffset { xpos - m->lastX_ };
            float yoffset { m->lastY_ - ypos }; // reversed since y-coordinates go from bottom to top
            
            m->lastX_ = xpos;
            m->lastY_ = ypos;
            EntityLUM* ent {m->camera_->getEntity()};
            if(ent){
                CameraLUM* cam {static_cast<CameraLUM*>(ent)};
                if(cam){
                   // cam->ProcessMouseMovement(xoffset, yoffset,true);
                }
            }
        }
    }
}
 
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Motor3DLUM::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Motor3DLUM* m  {static_cast<Motor3DLUM*>(glfwGetWindowUserPointer(window))};
    EntityLUM* ent {m->camera_->getEntity()};
    CameraLUM* cam {static_cast<CameraLUM*>(ent)};
    cam->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Motor3DLUM::processInput(GLFWwindow* window)
{   if(window){
        Motor3DLUM* m  {static_cast<Motor3DLUM*>(glfwGetWindowUserPointer(window))};
        if(m){
            EntityLUM* ent {m->camera_->getEntity()};
            if(ent){
                CameraLUM* cam {static_cast<CameraLUM*>(ent)};
                if(cam){
                    if (m->eventR_.IsKeyDown(keys::KEY_CODE_G::KEY_ESCAPE))
                    {
                        glfwSetWindowShouldClose(window, true);
                    }
                    if (glfwGetKey(window, keys::KEY_CODE_G::KEY_W) == GLFW_PRESS)
                    {
                        cam->ProcessKeyboard(FORWARD, m->deltaTime_);
                    }
                    if (glfwGetKey(window, keys::KEY_CODE_G::KEY_S) == GLFW_PRESS)
                    {
                        cam->ProcessKeyboard(BACKWARD, m->deltaTime_);
                    }
                    if (glfwGetKey(window, keys::KEY_CODE_G::KEY_A) == GLFW_PRESS)
                    {
                        cam->ProcessKeyboard(LEFT, m->deltaTime_);
                    }
                    if (glfwGetKey(window, keys::KEY_CODE_G::KEY_D) == GLFW_PRESS)
                    {
                        cam->ProcessKeyboard(RIGHT, m->deltaTime_);
                    }
                }
            }
        }
    }
}

std::vector<Vector3d> Motor3DLUM::getNodeVertices(NodeLUM * node){

    std::vector<Vector3d> nodeVertices;
    ModelLUM* model { static_cast<ModelLUM*>(node->getEntity()) };
    if(model == nullptr){ return nodeVertices; }

    for (size_t i {0}; i < static_cast<size_t>(model->meshes.size()); ++i)
    {
        for (size_t j {0}; j < static_cast<size_t>(model->meshes[i].vertices.size()); ++j)
        {   
            Vector3d vertex {
                model->meshes[i].vertices[j].Position.x,
                model->meshes[i].vertices[j].Position.y,
                model->meshes[i].vertices[j].Position.z};
            nodeVertices.push_back(vertex);
        }
    }

    return nodeVertices;
}

std::vector<uint32_t> Motor3DLUM::getNodeIndexes(NodeLUM* node){

    std::vector<uint32_t> nodeIndexes;
    ModelLUM* model {static_cast<ModelLUM*>(node->getEntity())};

    if (model == nullptr)
    {
        return nodeIndexes;
    }
    
    for (size_t i {}; i < static_cast<size_t>(model->meshes.size()); ++i)
    {
        for (size_t j {}; j < static_cast<size_t>(model->meshes[i].vertices.size()); ++j)
        {   
            nodeIndexes.push_back(model->meshes[i].indices[j]);
        }
    }

    return nodeIndexes;
}

void Motor3DLUM::setMaterialToNode(NodeLUM* node, float ambiental, float diffuse){
    node->setMaterial(ambiental, diffuse);
}

void Motor3DLUM::loadAnimations(std::vector<std::string> const & rutas, std::vector<std::string> const & nombres, std::vector<int> const & framesIni, std::vector<int> const & dist){
    if(rutas.size()==nombres.size()){
        mapAnimation.reserve(nombres.size());
        for (size_t i {}; i < static_cast<size_t>(rutas.size()); ++i)
        {
            mapAnimation.insert({nombres[i], std::make_unique<AnimationLUM>(rutas[i], framesIni[i], dist[i], &tManager_)});
        }
    }
}

void Motor3DLUM::loadAnimation(const std::string& ruta, const std::string& nombre, int const & framesIni, int const & dist){
    mapAnimation.insert({nombre, std::make_unique<AnimationLUM>(ruta, framesIni, dist, &tManager_)});
}

ECS::Hash_t<std::string, std::unique_ptr<AnimationLUM>>* Motor3DLUM::getAnimationMap(){
    return &mapAnimation;
}
void Motor3DLUM::setAnimationToNode(NodeLUM* node, const std::string& nombre, bool copiar){
    node->nomsAnimation_.push_back(nombre);

    if (copiar == false) {
        node->animations_.push_back(std::move(mapAnimation.at(nombre)));
    } else {
        node->animations_.push_back(std::make_unique<AnimationLUM>(
            mapAnimation.at(nombre)->path, mapAnimation.at(nombre)->frameIni, mapAnimation.at(nombre)->distFrames, &tManager_));
    }

    node->animCopiada = copiar;
}


uint32_t Motor3DLUM::loadCubeMap(std::vector<std::string> faces){
    uint32_t textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (uint32_t i {0}; i < static_cast<uint32_t>(faces.size()); ++i)
    {
        unsigned char *data { stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0) };
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            //std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


uint32_t Motor3DLUM::createskybox(int i){
    std::vector<std::string> faces{};

    switch (i) {
        case 0:
            faces = { "assets/textures/skybox/right.jpg",
                    "assets/textures/skybox/left.jpg",
                    "assets/textures/skybox/top.jpg",
                    "assets/textures/skybox/bottom.jpg",
                    "assets/textures/skybox/front.jpg",
                    "assets/textures/skybox/back.jpg"};
            break;

        case 1:
            faces = { "assets/textures/skyboxtarde/right.jpg",
                    "assets/textures/skyboxtarde/left.jpg",
                    "assets/textures/skyboxtarde/top.jpg",
                    "assets/textures/skyboxtarde/bottom.jpg",
                    "assets/textures/skyboxtarde/front.jpg",
                    "assets/textures/skyboxtarde/back.jpg"};
            break;

        default:
            faces = { "assets/textures/skyboxnoche/right.jpg",
                    "assets/textures/skyboxnoche/left.jpg",
                    "assets/textures/skyboxnoche/top.jpg",
                    "assets/textures/skyboxnoche/bottom.jpg",
                    "assets/textures/skyboxnoche/front.jpg",
                    "assets/textures/skyboxnoche/back.jpg"};
            break;
    }

    return loadCubeMap(faces);
}
