#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_TILEMAP
#define IGEEK_RPG_TOOLKIT_TILEMAP

#include "enemy_system.h"
#include "tile_regular.h"
#include "tile_spawner_enemy.h"

class TileMap {
  float grid_size_f_;
  int grid_size_f_, layers;
  sf::Vector2i max_size_world_grid_;
  sf::Vector2f max_size_world_f_;
  _::Array<_::Array<_::Array<_::Array<Tile*> > > > map_;
  _::AStack<Tile*> deferred_render_stack_;
  _::AString texture_file_;
  sf::Texture tile_sheet_;
  sf::RectangleShape collision_box_;
  int from_x,  //< culling
      to_x,    //< culling
      from_y,  //< culling
      to_y,    //< culling
      layer;   //< culling

 public:
  TileMap(float grid_size, int width, int height, _::AString texture_file);
  TileMap(const _::AString filename);
  virtual ~TileMap();

  const bool TileEmpty(const int x, const int y, const int z) const;
  const sf::Texture* TileSheet() const;
  const int LayerSize(const int x, const int y, const int layer) const;
  const sf::Vector2i& SizeGridMax() const;
  const sf::Vector2f& SizeMaxF() const;

  void AddTile(const int x, const int y, const int z,
               const sf::IntRect& texture_rect, const bool& collision,
               const short& type);
  void AddTile(const int x, const int y, const int z,
               const sf::IntRect& texture_rect, const int enemy_type,
               const int enemy_amount, const int enemy_tts, const int enemy_md);
  void RemoveTile(const int x, const int y, const int z, const int type = -1);
  void SaveToFile(const _::AString filename);
  void LoadFromFile(const _::AString filename);
  const bool CheckType(const int x, const int y, const int z,
                       const int type) const;

  void UpdateWorldBoundsCollision(Entity* entity, const float& dt);
  void UpdateTileCollision(Entity* entity, const float& dt);
  void UpdateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem);
  void Update(Entity* entity, const float& dt);

  void Render(sf::RenderTarget& target, const sf::Vector2i& gridPosition,
              sf::Shader* shader = nullptr,
              const sf::Vector2f playerPosition = sf::Vector2f(),
              const bool show_collision = false);
  void RenderDeferred(sf::RenderTarget& target, sf::Shader* shader = nullptr,
                      const sf::Vector2f playerPosition = sf::Vector2f());

 private:
  void Clear();
};

#endif
