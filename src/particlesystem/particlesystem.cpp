#include <particlesystem/particlesystem.h>
#include <iostream>

// Returns a random value between "direction" and "width"
float randomValue(float direction, float width) {
    return direction + width * rand() / static_cast<float>(RAND_MAX);
}

// Updates the particle's position based on acceleration and time (dt)
void Particle::updatePosition(const double dt) {
    this->velocity += this->acceleration * (float)dt;
    this->position += this->velocity * (float)dt;
}

// Creates a particle with "uniform" distribution
Particle Uniform::createParticle() {
    Particle myParticle(this->position);
    return myParticle;
}

// Creates a particle with "directional" distribution
Particle Directional::createParticle() {
    Particle myParticle(this->position, this->direction, this->width);
    return myParticle;
}

Particle Spinner::createParticle() {
    Particle myParticle(this->position, this->direction);
    return myParticle;
}

// Manipulates particle positions and accelerations by attracting particles
void GravityWell::effectParticle(std::vector<Particle>& allParticles) {
    for (Particle& p : allParticles) {
        // Calculate the distance between the GravityWell object's position and the particle's
        // position
        float dx = position.x - p.position.x;
        float dy = position.y - p.position.y;
        float length = std::sqrt(std::pow(dx, 2.0f) + std::pow(dy, 2.0f));
        // Calculate the strength of gravitational force based on distance
        float strength = force / (length * 5);
        // Normalize the distance vector
        float nx = dx / length;
        float ny = dy / length;
        // Apply an acceleration to the particle in the direction of the GravityWell object
        p.acceleration.x += strength * nx;
        p.acceleration.y += strength * ny;
    }
}

// Manipulates particle positions and accelerations by repelling particles
void Wind::effectParticle(std::vector<Particle>& allParticles) {
    for (Particle& p : allParticles) {
        // Calculate the distance between the Wind object's position and the particle's
        // position
        float dx = position.x - p.position.x;
        float dy = position.y - p.position.y;
        float length = std::sqrt(std::pow(dx, 2.0f) + std::pow(dy, 2.0f));
        // Calculate the strength of the force based on distance
        float strength = force / (length * 5.0f);
        // Normalize the distance vector
        float nx = dx / length;
        float ny = dy / length;
        // Apply an acceleration to the particle in the direction away from the Wind object
        p.acceleration.x -= strength * nx;
        p.acceleration.y -= strength * ny;
    }
}
