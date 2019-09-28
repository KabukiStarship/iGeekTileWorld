#include "player.h"

void Player::InitVariables() { attacking_ = false; }

void Player::initComponents() {}

void Player::InitAnimation() {
  animation_->AddAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
  animation_->AddAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
  animation_->AddAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
  animation_->AddAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
  animation_->AddAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
  animation_->AddAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

Player::Player(float x, float y, sf::Texture& texture_sheet) {
  InitVariables();

  CreateHitboxComponent(sprite_, 12.f, 10.f, 40.f, 54.f);
  CreateMovementComponent(200.f, 1600.f, 1000.f);
  CreateAnimation(texture_sheet);
  CreateAttribute(1);
  CreateSkill();

  PositionSet(x, y);
  InitAnimation();
}

Player::~Player() {}

AttributeComponent* Player::GetAttributeComponent() { return attribute_; }

void Player::LoseHP(const int hp) { attribute_->LoseHP(hp); }

void Player::GainHP(const int hp) { attribute_->GainHP(hp); }

void Player::LoseEXP(const int exp) { attribute_->LoseEXP(exp); }

void Player::GainEXP(const int exp) { attribute_->GainExp(exp); }

void Player::UpdateAttack() {
  if (sf::Mouse::IsButtonPressed(sf::Mouse::Left)) {
    attacking_ = true;
  }
}

void Player::UpdateAnimation(const float& dt) {
  if (attacking) {
  }
  if (movement_->GetState(IDLE)) {
    animation_->Play("IDLE", dt);
  } else if (movement_->GetState(kMovingLeft)) {
    animation_->Play("WALK_LEFT", dt, movement_->Velocity().x,
                     movement_->VelocityMax());
  } else if (movement_->GetState(kMovingRight)) {
    animation_->Play("WALK_RIGHT", dt, movement_->Velocity().x,
                     movement_->VelocityMax());
  } else if (movement_->GetState(kMovingUp)) {
    animation_->Play("WALK_UP", dt, movement_->Velocity().y,
                     movement_->VelocityMax());
  } else if (movement_->GetState(kMovingDown)) {
    animation_->Play("WALK_DOWN", dt, movement_->Velocity().y,
                     movement_->VelocityMax());
  }
}

void Player::Update(const float& dt, sf::Vector2f& mouse_pos_view) {
  movement_->Update(dt);

  UpdateAttack();

  UpdateAnimation(dt);

  hitbox_->Update();

  sword_.Update(mouse_pos_view, Center());
}

void Player::Render(sf::RenderTarget& target, sf::Shader* shader,
                    const sf::Vector2f light_position, const bool show_hitbox) {
  if (shader) {
    shader->setUniform("HasTexture", true);
    shader->setUniform("LightPos", light_position);
    target.draw(sprite, shader);

    shader->setUniform("HasTexture", true);
    shader->setUniform("LightPos", light_position);
    sword.Render(target, shader);
  } else {
    target.draw(sprite);
    sword.Render(target);
  }

  if (show_hitbox) hitbox_->Render(target);
}
