#include "App.hpp"
#include "GOL.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

App::App(unsigned int width, unsigned int height, unsigned int fps)
    : m_Width(width), m_Height(height),
      m_Fps(fps),
      m_Window(sf::VideoMode(width, height), "Game of Life"),
      m_GOL(width, height),
      m_Camera(width, height),
      m_Paused(false)
{ 
    m_Window.setFramerateLimit(fps);
    m_GOL.Randomise(m_RngEngine, 0.3);
}

void App::Run()
{
    while (m_Window.isOpen())
    {
        PollEvents();
        if (!m_Paused)
            Update();
        Render();
    }
}

void App::PollEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        m_Camera.PollEvents(event);
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            PollKeyPresses(event.key.code);
        }
    }
}

void App::PollKeyPresses(sf::Keyboard::Key& key)
{
    switch (key)
    {
    case sf::Keyboard::R:
        m_GOL.Randomise(m_RngEngine, 0.3);
        break;
    case sf::Keyboard::P:
        m_Paused = !m_Paused;
        break;
    case sf::Keyboard::Space:
        if (m_Paused) Update();
        break;
    }
}

void App::Render()
{
    m_Camera.Clear(sf::Color::Transparent); 
    m_Camera.Draw(m_GOL);

    m_Window.clear(sf::Color::Black);
    m_Window.draw(m_Camera);
    m_Window.display();
}

void App::Update()
{
    m_GOL.Update();
}



