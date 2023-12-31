#include "Sprite.h"

Sprite::Sprite(std::initializer_list<Frame> initFrames, int startingFrame, float frameRate) :
   m_frames(initFrames),
   m_currentFrame(startingFrame),
   m_frameRate(frameRate),
   m_invFrameRate(1.0f / frameRate),
   m_frameAccumulator(0.0f)
{
}

Sprite::Sprite(Frame frame, int startingFrame, float frameRate) :
   m_frames({ frame }),
   m_currentFrame(startingFrame),
   m_frameRate(frameRate),
   m_invFrameRate(1.0f / frameRate),
   m_frameAccumulator(0.0f)
{
}

void Sprite::NextFrame(float deltaTime)
{
   if (m_frames.size() <= 1)
      return;

   m_frameAccumulator += deltaTime;

   while (m_frameAccumulator >= m_invFrameRate)
   {
      m_currentFrame = (m_currentFrame + 1) % m_frames.size();
      m_frameAccumulator -= m_invFrameRate;
   }
}
