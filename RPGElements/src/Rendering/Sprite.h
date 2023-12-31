#pragma once

#include <initializer_list>
#include <vector>

#include "Color.h"

class Sprite
{
public:
   struct Frame
   {
      char glyph;
      Color color;

      Frame() : glyph(' '), color(Colors::Reset) {}
      Frame(char ch, Color col = Colors::Reset) : glyph(ch), color(col) {}
   
      bool operator==(const Frame& other) const { return glyph == other.glyph && color == other.color; }
      bool operator!=(const Frame& other) const { return !(*this == other); }
   };

   static constexpr float DEFAULT_FRAME_RATE = 1.67f;

   Sprite(std::initializer_list<Frame> initFrames, int startingFrame = 0, float frameRate = DEFAULT_FRAME_RATE);
   Sprite(Frame frame, int startingFrame = 0, float frameRate = DEFAULT_FRAME_RATE);

   void NextFrame(float deltaTime);
   inline void AddFrame(char frame) { m_frames.push_back(frame); }
   inline Frame GetCurrentFrame() const { return m_frames.empty() ? Frame(' ') : m_frames[m_currentFrame]; }

   inline const std::vector<Frame>& GetFrames() const { return m_frames; }
   inline size_t GetCurrentFrameIndex() const { return m_currentFrame; }

private:
   std::vector<Frame> m_frames;
   size_t m_currentFrame;
   float m_frameRate;
   float m_invFrameRate;
   float m_frameAccumulator;
};

namespace Sprites
{
   const Sprite FLOOR(Sprite::Frame('.', Colors::Grey));
   const Sprite WALL(Sprite::Frame('#', Colors::White));
   const Sprite PLAYER(Sprite::Frame('@', Colors::Cyan));
   const Sprite PLAYER_HURT( { Sprite::Frame('@', Colors::Cyan), Sprite::Frame('@', Colors::Red) }, 0, 4 );
   const Sprite GOBLIN(Sprite::Frame('G', Colors::BrightGreen));
}
