#include "tile.h"

Tile::Tile() {
  collision_ = false;
  type_ = 0;
}

Tile::Tile(short type, int grid_x, int grid_y, float grid_size_f_,
           const sf::Texture& texture, const sf::IntRect& texture_rect,
           const bool collision) {
  // shape.setOutlineThickness(1.f);
  // shape.setOutlineColor(sf::Color::Black);
  shape_.PositionSet(static_cast<float>(grid_x) * grid_size_f_,
                     static_cast<float>(grid_y) * grid_size_f_);
  shape_.setTexture(texture);
  shape_.setTextureRect(texture_rect);

  collision_ = collision;
  type_ = type;
}

Tile::~Tile() {}

const short& Tile::GetType() const { return type_; }

const bool& Tile::GetCollision() const { return collision_; }

const sf::Vector2f& Tile::GetPosition() const { return shape_.getPosition(); }

const sf::FloatRect Tile::GlobalBounds() const { return shape_.GlobalBounds(); }

const bool Tile::Intersects(const sf::FloatRect bounds) const {
  return shape_.GlobalBounds().intersects(bounds);
}
