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
//# RenderSystem sirve para actualizar las entidades que tienen      #
//#   componente de render para mostrarlas en el juego.              #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include "../Motor3D/Motor3D.hpp"
#include "../Motor3D/Motor3DLUM/Motor3DLUM.hpp"
#include <cstdint>
#include <memory>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <chrono>

#include "../util/typealiases.hpp"
#include "../cmp/entity.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/camera.hpp"
#include "../cmp/render.hpp"
#include "../cmp/hud.hpp"
#include "../cmp/ia.hpp"

struct CameraWithPhysics_t {
    const CameraComponent_t* cam { nullptr };
    const PhysicsComponent_t* phy { nullptr };
};

template <typename GameCTX_t>
struct RenderSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit RenderSystem_t() = default; //Constructor por defecto
    explicit RenderSystem_t(uint32_t w, uint32_t h);   //Constructor
    ~RenderSystem_t();                                                      //Destructor

    //            Este const implica que las variables con las que va a trabajar el metodo son conts del ambito de RenderSystem
    bool update(GameCTX_t& g);
    void drawAllTexts(GameCTX_t& g) const;
    void drawAllEntities(GameCTX_t& g) const;

    void changeTextureIA(RenderComponent_t& ren, const char *path) const;
    void checkActionsIA(RenderComponent_t& ren, IAComponent_t& ia) const;
    
    Motor3DLUM* getMotor() const {return motor.get(); }

    constexpr void setDebugDraw(bool v) const noexcept { m_debugDraw = v; }
    constexpr void setDebugColor(uint32_t c) const noexcept { m_debugColor = c; }
    [[nodiscard]] constexpr bool debugDraw() const noexcept { return m_debugDraw; }
    [[nodiscard]] constexpr uint32_t debugColor() const noexcept { return m_debugColor; }

    private:
        constexpr void drawAllCameras(const GameCTX_t& g) const;

        void dia(GameCTX_t& g);
        void atardecer(GameCTX_t& g);
         void noche(GameCTX_t& g);
          void tunel(GameCTX_t& g);
        Vector3d luzLevel {0.0, 0.0, 0.0};
        LightLUM* li {nullptr};

        mutable bool m_debugDraw { true };
        mutable uint32_t m_debugColor { 0xFFFF0000 };

        mutable CameraWithPhysics_t m_currentCam {};

        //Const (solo lectura) QUITAR PARA HACER QUE LA RESOLUCION DE LA PANTALLA CAMBIE
        const uint32_t m_w { 0 }, m_h { 0 };

        //Unique Ptr a el motor
        std::unique_ptr<Motor3DLUM> motor {nullptr};
};