#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_RAT
#define IGEEK_RPG_TOOLKIT_RAT

#include "enemy.h"

class Rat : public Enemy {
 private:
  void InitVariables();
  void InitAnimation();

 public:
  Rat(float x, float y, sf::Texture& texture_sheet);
  virtual ~Rat();

  void UpdateAnimation(const float& dt);
  void Update(const float& dt, sf::Vector2f& mouse_pos_view);

  void Render(sf::RenderTarget& target, sf::Shader* shader,
              const sf::Vector2f light_position, const bool show_hitbox);
};

#endif
