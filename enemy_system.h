#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_ENEMYSYSTEM
#define IGEEK_RPG_TOOLKIT_ENEMYSYSTEM

#include "rat.h"
#include "tile_spawner_enemy.h"

enum EnemyTypes { RAT = 0 };

class EnemySystem {
 private:
  _::ADic<_::AString, sf::Texture>& textures;
  _::Array<Enemy*>& active_enemies_;

 public:
  EnemySystem(_::Array<Enemy*>& active_enemies_,
              _::ADic<_::AString, sf::Texture>& textures);
  virtual ~EnemySystem();

  // Modifiers

  void CreateEnemy(const short type, const float xPos, const float yPos);

  void Update(const float& dt);
  void Render(sf::RenderTarget* target);
};
#endif
