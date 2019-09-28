#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_SWORD
#define IGEEK_RPG_TOOLKIT_SWORD

#include "weapon_melee.h"

class MeleeWeapon;

class Sword : public MeleeWeapon {
 private:
 public:
  Sword();
  virtual ~Sword();

  virtual void Update(const sf::Vector2f& mouse_pos_view,
                      const sf::Vector2f center);
  virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

#endif
