#pragma once

#include "GOL/GOL.hpp"
#include "ControllableCamera.hpp"

#include <SFML/Graphics.hpp>
#include <random>

class App
{
    private:
        unsigned int m_Width, m_Height;
        const unsigned int m_Fps;
        bool m_Paused;
        sf::RenderWindow m_Window;
        ControllableCamera m_Camera;
        sf::Clock m_Clock;
        std::default_random_engine m_RngEngine;
        gol::GOL m_GOL;
    public:
        App(unsigned int width, unsigned int height, unsigned int fps);
        void Run();
    private:
        void PollEvents();
        void PollKeyPresses(sf::Keyboard::Key& key);
        void Resize(float x, float y);
        void Update();
        void Render();
};