#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_REGULARTILE
#define IGEEK_RPG_TOOLKIT_REGULARTILE

#include "tile.h"

class TileRegular : public Tile {
 public:
  TileRegular(short type, int grid_x, int grid_y, float grid_size_f_,
              const sf::Texture& texture, const sf::IntRect& texture_rect,
              bool collision = false);

  virtual ~TileRegular();

  virtual const _::AString ToString() const;

  virtual void Update();
  virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr,
                      const sf::Vector2f player_position = sf::Vector2f());
};

#endif
