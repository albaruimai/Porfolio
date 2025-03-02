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


struct PhysicsComponent_t;


struct Point2D_t{
    double x { 0.0 }, y { 0.0 };
};

namespace STBEH{

    struct Steer_t {
        double linear       { 0.0 };
        double angular      { 0.0 };
        constexpr bool operator==(Steer_t const&) const noexcept = default;
    };

    Steer_t arrive(PhysicsComponent_t *, Point2D_t * target, double & time2arrive, double & arrivalRadius);
    Steer_t seek(PhysicsComponent_t *, Point2D_t * target, double & time2arrive, double & arrivalRadius);
}