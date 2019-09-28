#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_PLAYER
#define IGEEK_RPG_TOOLKIT_PLAYER

#include "entity.h"
#include "sword.h"

class Entity;

class Player : public Entity {
 private:
  bool attacking_;
  Sword sword_;

  void InitVariables();
  void initComponents();
  void InitAnimation();

 public:
  Player(float x, float y, sf::Texture& texture_sheet);
  virtual ~Player();

  AttributeComponent* GetAttributeComponent();

  void LoseHP(const int hp);
  void GainHP(const int hp);
  void LoseEXP(const int exp);
  void GainEXP(const int exp);
  void UpdateAttack();
  void UpdateAnimation(const float& dt);
  void Update(const float& dt, sf::Vector2f& mouse_pos_view);

  void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr,
              const sf::Vector2f light_position = sf::Vector2f(),
              const bool show_hitbox = false);
};

#endif
