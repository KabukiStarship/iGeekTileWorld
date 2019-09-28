#ifndef IGEEK_RPG_TOOLKIT_MELEEWEAPON
#define IGEEK_RPG_TOOLKIT_MELEEWEAPON

#include "item.h"

class Item;

class MeleeWeapon : public Item {
 private:
 protected:
  sf::Texture weapon_texture;
  sf::Sprite weapon_sprite;

  int damage_min_;
  int damage_max_;

 public:
  MeleeWeapon();
  virtual ~MeleeWeapon();

  virtual void Update(const sf::Vector2f& mouse_pos_view,
                      const sf::Vector2f center) = 0;
  virtual void Render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

#endif
