#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_ANIMATIONCOMPONENT
#define IGEEK_RPG_TOOLKIT_ANIMATIONCOMPONENT

class AnimationComponent {
 private:
  class Animation {
   public:
    sf::Sprite& sprite_;
    sf::Texture& texture_sheet_;
    float animation_timer_, timer_;
    bool done_;
    int width_;
    int height_;
    sf::IntRect start_rect_, current_rect_, end_rect_;

    Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
              float animation_timer, int start_frame_x, int start_frame_y,
              int frames_x, int frames_y, int width, int height)
        : sprite(sprite),
          textureSheet(texture_sheet),
          animationTimer(animation_timer),
          timer(0.f),
          done(false),
          width(width),
          height(height) {
      start_rect = sf::IntRect(start_frame_x * width, start_frame_y * height,
                               width, height);
      current_rect = start_rect;
      endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

      sprite.setTexture(textureSheet, true);
      sprite.setTextureRect(start_rect);
    }

    const bool& IsDone() const;

    const bool& Play(const float& dt);

    const bool& Play(const float& dt, float mod_percent);

    void Reset();
  };

  sf::Sprite& sprite_;
  sf::Texture& texture_sheet_;
  _::ADic<_::AString, Animation*> animations;
  Animation* last_animation_;
  Animation* priority_animation_;

 public:
  AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
  virtual ~AnimationComponent();

  const bool& IsDone(const _::AString key);

  void AddAnimation(const _::AString key, float animation_timer,
                    int start_frame_x, int start_frame_y, int frames_x,
                    int frames_y, int width, int height);

  const bool& Play(const _::AString key, const float& dt,
                   const bool priority = false);
  const bool& Play(const _::AString key, const float& dt, const float& modifier,
                   const float& modifier_max, const bool priority = false);
};

#endif
