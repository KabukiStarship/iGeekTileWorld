#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_HITBOXCOMPONENT
#define IGEEK_RPG_TOOLKIT_HITBOXCOMPONENT

class HitboxComponent {
 private:
  sf::Sprite& sprite;
  sf::RectangleShape hitbox;
  sf::FloatRect nextPosition;
  float offsetX;
  float offsetY;

 public:
  HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y,
                  float width, float height);
  virtual ~HitboxComponent();

  const sf::Vector2f& getPosition() const;
  const sf::FloatRect GlobalBounds() const;
  const sf::FloatRect& NextPosition(const sf::Vector2f& velocity);

  void SetPosition(const sf::Vector2f& position);
  void SetPosition(const float x, const float y);

  bool Intersects(const sf::FloatRect& frect);

  void Update();
  void Render(sf::RenderTarget& target);
};

#endif
