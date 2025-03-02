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

#include "ParticleSys.hpp"

ParticleSys::ParticleSys(std::vector<SpriteRenderer*> sp, uint32_t amount, ParticleType p)
    : sprite_{sp}, amount_{amount}, partType{p}
{
    srand((unsigned) time(0));
    for (size_t i {0}; i < static_cast<size_t>(sprite_.size()); ++i)
    {
        Particle& p {particles_.emplace_back(Particle{sprite_[i]})};
        p.sp_->setPosition
        (
            glm::vec2
            (
                rand() % static_cast<int>( p.sp_->getPosition().x - (+ static_cast<float>(rand()%20 * .2)) ),
                -(rand()%10000)-20
            )
        );
        p.origin = p.sp_->getPosition();
    }    
}

void ParticleSys::update()
{
    srand((unsigned) time(0));
    switch (partType)
    {
    case ParticleType::SNOW:
        for (uint32_t i {}; i < amount_; ++i)
        {
            if (particles_[i].life_ > 0.0f)
            {
                particles_[i].sp_->setPosition
                (
                    glm::vec2(particles_[i].sp_->getPosition().x + static_cast<float>(rand()%20)*.2,
                    particles_[i].sp_->getPosition().y+(1-particles_[i].life_)*GRAVITY)
                );
                particles_[i].sp_->setRotate(particles_[i].sp_->getRotate()+.01*static_cast<float>(rand()%10));
                auto dt {static_cast<float>(rand()%10)*.0025};
                particles_[i].alpha_ -= dt;
                particles_[i].life_  -= dt;
                particles_[i].sp_->setAlpha(particles_[i].alpha_);
            }
            if (particles_[i].life_ <= 0.0f)
            {
                particles_[i].alpha_ = 1;
                particles_[i].life_  = 1;
                particles_[i].sp_->setAlpha(particles_[i].alpha_);
                particles_[i].sp_->setPosition(glm::vec2(particles_[i].origin.x,-(rand()%10000)-20));
            }
        }
        break;
    
    case ParticleType::RAIN:
        for (uint32_t i {}; i < amount_; ++i)
        {
            if (particles_[i].life_ > 0.0f)
            {
                particles_[i].sp_->setPosition
                (
                    glm::vec2(particles_[i].sp_->getPosition().x + static_cast<float>(rand()%20)*.2,
                    particles_[i].sp_->getPosition().y+20+(1-particles_[i].life_)*GRAVITY)
                );
                //particles_[i].sp_->setRotate(particles_[i].sp_->getRotate()+.001*static_cast<float>(rand()%10));
                auto dt {static_cast<float>(rand()%10)*.001};
                particles_[i].alpha_ -= dt;
                particles_[i].life_  -= dt;
                particles_[i].sp_->setAlpha(particles_[i].alpha_);
            }
            if (particles_[i].life_ <= 0.0f)
            {
                particles_[i].alpha_ = 1;
                particles_[i].life_  = 1;
                particles_[i].sp_->setAlpha(particles_[i].alpha_);
                particles_[i].sp_->setPosition(glm::vec2(particles_[i].origin.x,-(rand()%10000)-20));
            }
        }
        break;
    default:
        for (uint32_t i {}; i < amount_; ++i)
        {
            if (particles_[i].life_ > 0.0f)
            {
                particles_[i].sp_->setPosition
                (
                    glm::vec2(particles_[i].sp_->getPosition().x + static_cast<float>(rand()%20)*.2,
                    particles_[i].sp_->getPosition().y+5+(1-particles_[i].life_)*GRAVITY)
                );
                particles_[i].sp_->setRotate(particles_[i].sp_->getRotate()+.001*static_cast<float>(rand()%10));
                particles_[i].alpha_ -= static_cast<float>(rand()%10)*.05;
                particles_[i].life_  -= static_cast<float>(rand()%10)*.05;
                particles_[i].sp_->setAlpha(particles_[i].alpha_);
            }
            if (particles_[i].life_ <= 0.0f)
            {
                particles_[i].alpha_ = 1;
                particles_[i].life_  = 1;
                particles_[i].sp_->setAlpha(particles_[i].alpha_);
                particles_[i].sp_->setPosition(glm::vec2(particles_[i].origin.x,-(rand()%10000)-20));
            }
        }
    }
}