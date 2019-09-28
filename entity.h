#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_ENTITY
#define IGEEK_RPG_TOOLKIT_ENTITY

#include "animation_.h"
#include "component_attribute.h"
#include "component_hitbox.h"
#include "component_movement.h"
#include "skill_component.h"

class Entity {
 private:
  void InitVariables();

 protected:
  sf::Sprite sprite_;
  HitboxComponent* hitbox_component_;
  MovementComponent* movement_;
  AnimationComponent* animation_component_;
  AttributeComponent* attribute_component_;
  SkillComponent* skill_component_;

 public:
  Entity();
  virtual ~Entity();

  void setTexture(sf::Texture& texture);
  void CreateHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y,
                             float width, float height);
  void CreateMovementComponent(const float velocity_max,
                               const float acceleration,
                               const float deceleration);
  void CreateAnimation(sf::Texture& texture_sheet);
  void CreateAttribute(const unsigned level);
  void CreateSkill();

  virtual const sf::Vector2f& getPosition() const;
  virtual const sf::Vector2f Center() const;
  virtual const sf::Vector2i GridPosition(const int grid_size_f_) const;
  virtual const sf::FloatRect GlobalBounds() const;
  virtual const sf::FloatRect NextPositionBounds(const float& dt) const;

  virtual void PositionSet(const float x, const float y);

  virtual void Move(const float x, const float y, const float& dt);
  virtual void StopVelocity();
  virtual void StopVelocityX();
  virtual void StopVelocityY();

  virtual void Update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
  virtual void Render(sf::RenderTarget& target, sf::Shader* shader,
                      const sf::Vector2f light_position,
                      const bool show_hitbox) = 0;
};

#endif
