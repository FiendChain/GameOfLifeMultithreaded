#include "GOL.hpp"
#include <functional>
#include <thread>
#include <memory>

namespace gol
{

GOL::GOL(unsigned int width, unsigned int height, unsigned int totalThreads)
    : m_Width(width), m_Height(height),
      m_Grid(std::make_unique<GOLGrid>(width, height)),
      m_Buffer(std::make_unique<GOLGrid>(width, height)),
      m_ThreadPool(totalThreads),
      m_ThreadFunctions(0),
      m_TotalThreads(totalThreads)
{
    if (m_TotalThreads <= 0)
        throw std::runtime_error("Couldn't create threads for GOL");
    CreateThreads();
}

void GOL::CreateThreads()
{
    unsigned int rowIter = m_Height/m_TotalThreads;
    unsigned int row = 0;
    unsigned int rowEnd = 0;
    for (unsigned int threadID = 0; threadID < m_TotalThreads; threadID++)
    {
        if (threadID == m_TotalThreads-1) rowEnd = m_Height;
        else                              rowEnd = row + rowIter;
        m_ThreadFunctions.emplace_back([this, row, rowEnd](const GOLFunc& func) {
            UpdateThread(func, row, rowEnd);
        });
        row = rowEnd;
    }
}

void GOL::Update(const GOLFunc& func)
{
    for (auto& threadFunc: m_ThreadFunctions)
    {
        m_ThreadPool.AddJob(std::bind(threadFunc, func));
    }

    m_ThreadPool.WaitUntilFinished();

    SwapBuffers();
}

void GOL::UpdateThread(const GOLFunc& func, unsigned int rowStart, unsigned int rowEnd)
{
    for (unsigned int row = rowStart; row < rowEnd; row++)
        for (unsigned int col = 0; col < m_Width; col++)
        {
            GOLGrid::State state = func(*m_Grid, row, col);
            m_Buffer->SetState(state, row, col);
        }
}

void GOL::SwapBuffers()
{
    m_Grid.swap(m_Buffer);
}

void GOL::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*m_Grid, states);
}

}