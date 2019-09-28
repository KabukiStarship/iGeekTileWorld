#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_MOVEMENTCOMPONENT
#define IGEEK_RPG_TOOLKIT_MOVEMENTCOMPONENT

enum movement_states {
  kIdle = 0,
  kMoving,
  kMovingLeft,
  kMovingRight,
  kMovingUp,
  kMovingDown
};

class MovementComponent {
 private:
  sf::Sprite& sprite_;

  float velocity_max_, acceleration_, deceleration_;

  sf::Vector2f velocity_;

 public:
  MovementComponent(sf::Sprite& sprite, float velocity_max, float acceleration,
                    float deceleration);
  virtual ~MovementComponent();

  const float& VelocityMax() const;
  const sf::Vector2f& Velocity() const;

  const bool GetState(const short unsigned state) const;
  void StopVelocity();
  void StopVelocityX();
  void StopVelocityY();

  void Move(const float x, const float y, const float& dt);
  void Update(const float& dt);
};

#endif
