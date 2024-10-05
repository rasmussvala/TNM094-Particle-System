// #include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>

#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>
#include <iostream>

int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);

    double prevTime = 0.0;
    bool running = true;
    std::vector<Particle> allParticles;
    std::vector<Emitter*> allEmitters;
    std::vector<Effect*> allEffects;
    int currentEmitter = 0;
    int currentEffect = 0;
    int particleLifetime = 4;

    while (running) {
        // Start frame
        window.beginFrame();
        window.setTitle("Particle system");

        // Time
        const double t = window.time();
        const double dt = t - prevTime;
        prevTime = t;

        // Clear screen with color
        window.clear({0, 0, 0, 1});

        // Check if there are any Emitters
        if (allEmitters.size() > 0) {
            // If there are: Let them all emit (iterate through) new particles
            for (Emitter* ptr : allEmitters) {
                allParticles.push_back(ptr->createParticle());
            }
        }
        // Check if there are any Effects
        if (allEffects.size() > 0) {
            // If there are: Let them all affect (iterate through) existing particles
            for (Effect* ptr : allEffects) {
                ptr->effectParticle(allParticles);
            }
        }

        // Step through all particles
        if (allParticles.size() > 0) {
            for (size_t i = 0; i < allParticles.size(); i++) {
                allParticles[i].lifetime += (float)dt;
                // Remove particles that are too old
                if (allParticles[i].lifetime > particleLifetime) {
                    allParticles.erase(allParticles.begin() + i);
                }
                if (allParticles.size() > 0) {
                    // Move existing particles
                    allParticles[i].updatePosition(dt);
                    // Draw all particles
                    window.drawPoint(allParticles[i].position, allParticles[i].radius,
                                     allParticles[i].color);
                }
            }
        }

        // Draw all emitters
        if (allEmitters.size() > 0) {
            for (Emitter* ptr : allEmitters) {
                window.drawPoint(ptr->position, ptr->radius, ptr->color);
            }
        }
        // Draw all effects
        if (allEffects.size() > 0) {
            for (Effect* ptr : allEffects) {
                window.drawPoint(ptr->position, ptr->radius, ptr->color);
            }
        }

        // UI - Emitter
        {
            window.beginGuiWindow("Emitters");
            // Mark current emitter, if there are any emitters
            if (allEmitters.size() > 0) {
                window.sliderInt("Current Emitter", currentEmitter, 0, (int)allEmitters.size() - 1);
            }

            if (window.button("Add Uniform")) {
                std::unique_ptr<Uniform> ptr = std::make_unique<Uniform>();
                allEmitters.push_back(ptr.release());
            }

            if (window.button("Add Directional")) {
                std::unique_ptr<Directional> ptr = std::make_unique<Directional>();
                allEmitters.push_back(ptr.release());
            }

            if (window.button("Add Spinner")) {
                std::unique_ptr<Spinner> ptr = std::make_unique<Spinner>();
                allEmitters.push_back(ptr.release());
            }

            if (allEmitters.size() > 0) {
                if (window.button("Remove Current Emitter")) {
                    allEmitters.erase(allEmitters.begin() + currentEmitter);
                    currentEmitter = 0;
                }
            }

            if (allEmitters.size() > 0) {
                window.sliderVec2("Position (x,y)", allEmitters[currentEmitter]->position, -1, 1);

                // If we're on a directional emitter, show slider for direction and width
                if (Directional* ptrDirectional =
                        dynamic_cast<Directional*>(allEmitters[currentEmitter])) {
                    glm::vec2 values(ptrDirectional->getDirection(), ptrDirectional->getWidth());
                    window.sliderVec2("Direction and Width", values, 0, 6.24f);
                    ptrDirectional->changeDirValues(values);
                }
            }

            window.endGuiWindow();
        }

        // UI - Effect
        {
            window.beginGuiWindow("Effects");
            if (allEffects.size() > 0) {
                window.sliderInt("Current Effect", currentEffect, 0, (int)allEffects.size() - 1);
            }
            if (window.button("Add Gravity Well")) {
                std::unique_ptr<GravityWell> ptr = std::make_unique<GravityWell>();
                allEffects.push_back(ptr.release());
            }
            if (window.button("Add Wind")) {
                std::unique_ptr<Wind> ptr = std::make_unique<Wind>();
                allEffects.push_back(ptr.release());
            }
            if (allEffects.size() > 0) {
                if (window.button("Remove Current Effect")) {
                    allEffects.erase(allEffects.begin() + currentEffect);
                    currentEffect = 0;
                }
            }
            if (allEffects.size() > 0) {
                window.sliderVec2("Position (x,y)", allEffects[currentEffect]->position, -1, 1);
            }

            window.endGuiWindow();
        }

        window.endFrame();
        running = running && !window.shouldClose();
    }

    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}
