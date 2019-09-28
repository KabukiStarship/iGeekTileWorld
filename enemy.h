#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_ENEMY
#define IGEEK_RPG_TOOLKIT_ENEMY

#include "entity.h"
#include "tile_spawner_enemy.h"

class Entity;
class EnemySpawnerTile;

class Enemy : public Entity {
 private:
  // EnemySpawner& enemySpawner;

  virtual void InitVariables() = 0;
  virtual void InitAnimation() = 0;

 public:
  Enemy();
  virtual ~Enemy();

  virtual void UpdateAnimation(const float& dt) = 0;

  virtual void Update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
  virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr,
                      const sf::Vector2f light_position = sf::Vector2f(),
                      const bool show_hitbox = false) = 0;
};

#endif  //! ENEMY_H
