#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_ENEMYSPAWNERTILE
#define IGEEK_RPG_TOOLKIT_ENEMYSPAWNERTILE

#include "tile.h"

class EnemySpawnerTile : public Tile {
 private:
  int enemy_type_, enemy_amount_;
  int enemy_time_to_spawn_;
  float enemy_max_distance_;
  bool spawned_;

 public:
  EnemySpawnerTile(int grid_x, int grid_y, float grid_size_f_,
                   const sf::Texture& texture, const sf::IntRect& texture_rect,
                   int enemy_type, int enemy_amount, int enemy_time_to_spawn,
                   float enemy_max_distance);
  virtual ~EnemySpawnerTile();

  virtual const _::AString ToString() const;
  const bool& GetSpawned() const;

  // Modifiers
  void SetSpawned(const bool spawned);

  void Update();
  void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr,
              const sf::Vector2f player_position = sf::Vector2f());
};

#endif
