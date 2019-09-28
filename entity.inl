#include "entity.h"

void Entity::InitVariables() {
  hitbox_ = nullptr;
  movement_ = nullptr;
  animation_ = nullptr;
  attribute_ = nullptr;
  skill_ = nullptr;
}

Entity::Entity() { InitVariables(); }

Entity::~Entity() {
  delete hitbox_;
  delete movement_;
  delete animation_;
  delete attribute_;
  delete skill_;
}

void Entity::setTexture(sf::Texture& texture) { sprite_.setTexture(texture); }

void Entity::CreateHitboxComponent(sf::Sprite& sprite_, float offset_x,
                                   float offset_y, float width, float height) {
  hitbox_ = new HitboxComponent(sprite_, offset_x, offset_y, width, height);
}

void Entity::CreateMovementComponent(const float velocity_max,
                                     const float acceleration,
                                     const float deceleration) {
  movement_ =
      new MovementComponent(sprite_, velocity_max, acceleration, deceleration);
}

void Entity::CreateAnimation(sf::Texture& texture_sheet) {
  animation_ = new AnimationComponent(sprite_, texture_sheet);
}

void Entity::CreateAttribute(const unsigned level) {
  attribute_ = new AttributeComponent(level);
}

void Entity::CreateSkill() { skill_ = new SkillComponent(); }

const sf::Vector2f& Entity::getPosition() const {
  if (hitbox_) return hitbox_->getPosition();

  return sprite_.getPosition();
}

const sf::Vector2f Entity::Center() const {
  if (hitbox_)
    return hitbox_->getPosition() +
           sf::Vector2f(hitbox_->GlobalBounds().width / 2.f,
                        hitbox_->GlobalBounds().height / 2.f);

  return sprite_.getPosition() +
         sf::Vector2f(sprite_.GlobalBounds().width / 2.f,
                      sprite_.GlobalBounds().height / 2.f);
}

const sf::Vector2i Entity::GridPosition(const int grid_size_f_) const {
  if (hitbox_)
    return sf::Vector2i(
        static_cast<int>(hitbox_->getPosition().x) / grid_size_f_,
        static_cast<int>(hitbox_->getPosition().y) / grid_size_f_);

  return sf::Vector2i(static_cast<int>(sprite_.getPosition().x) / grid_size_f_,
                      static_cast<int>(sprite_.getPosition().y) / grid_size_f_);
}

const sf::FloatRect Entity::GlobalBounds() const {
  if (hitbox_) return hitbox_->GlobalBounds();

  return sprite_.GlobalBounds();
}

const sf::FloatRect Entity::NextPositionBounds(const float& dt) const {
  if (hitbox_ && movement_)
    return hitbox_->NextPosition(movement_->Velocity() * dt);

  return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

// Functions
void Entity::PositionSet(const float x, const float y) {
  if (hitbox_)
    hitbox_->PositionSet(x, y);
  else
    sprite_.PositionSet(x, y);
}

void Entity::Move(const float dir_x, const float dir_y, const float& dt) {
  if (movement_) movement_->move(dir_x, dir_y, dt);  // Sets velocity

  if (skill_) {
    skill_->GainExp(SKILLS::ENDURANCE, 1);
    // std::cout <<skill_->GetSkill(SKILLS::ENDURANCE) << "\n";
  }
}

void Entity::StopVelocity() {
  if (movement_) movement_->StopVelocity();
}

void Entity::StopVelocityX() {
  if (movement_) movement_->StopVelocityX();
}

void Entity::StopVelocityY() {
  if (movement_) movement_->StopVelocityY();
}
