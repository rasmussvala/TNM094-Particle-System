#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <cmath>
#include <iostream>

// random value (direction - width)
float randomValue(float direction, float width);

class Particle {
public:
    float twoPi = (float)(2 * 3.14159265358979323846);
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 velocity = {0.0f, 0.0f};
    glm::vec2 acceleration;
    float lifetime = 0.0f;
    float radius = 5.0f;
    glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    float force = 1.0f;

    // F�r uniform
    Particle(glm::vec2 pos) {
        position = pos;
        float theta = randomValue(0, twoPi);
        acceleration = {force * cos(theta), force * sin(theta)};
    }

    // F�r directional
    Particle(glm::vec2 pos, float direction, float width) {
        position = pos;
        float theta = randomValue(direction, width);
        acceleration = {force * cos(theta), force * sin(theta)};
    }

    // F�r spinner
    Particle(glm::vec2 pos, float direction) {
        position = pos;
        float theta = 0.0f;  // ska uppdateras
        acceleration = {force * cos(theta), force * sin(theta)};
    }

    void updatePosition(const double dt);
};

class Emitter {
public:
    float radius = 10.0f;
    glm::vec4 color = {1.0f, 0.0f, 0.0f, 1.0f};
    glm::vec2 position = {0.0f, 0.0f};

    virtual Particle createParticle() = 0;
    virtual ~Emitter() {}
};

class Uniform : public Emitter {
public:
    float twoPi = (float)(2 * 3.14159265358979323846);
    float theta = randomValue(0, twoPi);

    Particle createParticle() override;
};

class Directional : public Emitter {
public:
    float width;
    float direction;
    float theta = randomValue(direction, width);

    float getDirection() const& { return direction; }
    float getWidth() const& { return width; }
    void changeDirValues(glm::vec2 values) {
        direction = values[0];
        width = values[1];
    }

    Directional() {
        this->direction = 1.0f;
        this->width = 0.0f;
    }

    Particle createParticle() override;
};

class Spinner : public Emitter {
public:
    float direction;
    float theta = randomValue(0, 3.14);

    Particle createParticle() override;
};

class Effect {
public:
    float radius = 10.0f;
    glm::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f};
    glm::vec2 position = {0.2f, 0.0f};

    virtual void effectParticle(std::vector<Particle>& allParticles) = 0;
};

class GravityWell : public Effect {
public:
    float force = 0.05f;

    void effectParticle(std::vector<Particle>& allParticles) override;
};

class Wind : public Effect {
public:
    float force = 0.05f;

    void effectParticle(std::vector<Particle>& allParticles) override;
};
