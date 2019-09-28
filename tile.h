#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_TILE
#define IGEEK_RPG_TOOLKIT_TILE

enum TileTypes { kDefault = 0, kDamaging, kDoodad, kSpawnerEnemy };

class Tile {
 protected:
  sf::Sprite shape_;
  bool collision_;
  short type_;

 public:
  Tile();
  Tile(short type, int grid_x, int grid_y, float grid_size_f_,
       const sf::Texture& texture, const sf::IntRect& texture_rect,
       const bool collision);
  virtual ~Tile();

  const short& GetType() const;
  virtual const bool& GetCollision() const;

  virtual const sf::Vector2f& GetPosition() const;
  virtual const sf::FloatRect GlobalBounds() const;
  virtual const bool Intersects(const sf::FloatRect bounds) const;
  virtual const _::AString ToString() const = 0;

  virtual void Update() = 0;
  virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr,
                      const sf::Vector2f player_position = sf::Vector2f()) = 0;
};

#endif
