/*****************************************************************//**
 * \file   ParticleSystem_Snows.cpp
 * \brief  ParticleSystem Snows source code
 * 
 * \author Kevin Pruvost (pruvostkevin0@gmail.com)
 * \date   April, 26 2022
 *********************************************************************/
#include "ParticleSystem_Snow.hpp"

// Project includes
#include "OGL_Implementation\Window.hpp"

// GLM includes
#include <glm/gtx/string_cast.hpp>

ParticleSystem_Snow::ParticleSystem_Snow(const Shader & shaderPoint_, const Shader & shaderWireframe_, const Shader & shaderPS_)
    : ParticleSystem_Base(shaderPoint_, shaderWireframe_, shaderPS_, 5.0f, 10.0f, 50)
    , polarSpeed{ 1.0f }
    , particleSpeed{ 1.0f }
    , __theta{ 0.0f }
{
    __particles.reserve(maxParticles);
}

ParticleSystem_Snow::~ParticleSystem_Snow()
{
}

void ParticleSystem_Snow::OnUpdate()
{
}

void ParticleSystem_Snow::UpdateParticle(Particle_Base * particle_)
{
    Particle_Snow & particle = *particle_->Cast<Particle_Snow>();

    if (glm::length(particle.acceleration) > FLT_EPSILON)
    {
        particle.speed += _deltaTime * particle.acceleration;
        particle.acceleration += _deltaTime * particle.acceleration * 0.2f;
    }
    particle.pos += particle.speed * _deltaTime;
}

std::vector<Particle_Base *> ParticleSystem_Snow::SpawnParticle()
{
    std::vector<Particle_Base *> newParticles;    


    return newParticles;
}

void ParticleSystem_Snow::OnStart()
{
}

void ParticleSystem_Snow::OnStop()
{
}

void ParticleSystem_Snow::OnReset()
{
    __theta = 0.0f;
}

Particle_Base::ParticlePropertiesStyle ParticleSystem_Snow::GetParticlePropertiesStyle() const
{
    return Particle_Base::ParticlePropertiesStyle::Color;
}