#include "tilemap.h"

void TileMap::Clear() {
  if (!map_.empty()) {
    for (int x = 0; x < map_.size(); x++) {
      for (int y = 0; y < map_[x].size(); y++) {
        for (int z = 0; z < map_[x][y].size(); z++) {
          for (size_t k = 0; k < map_[x][y][z].size(); k++) {
            delete map_[x][y][z][k];
            map_[x][y][z][k] = nullptr;
          }
          map_[x][y][z].clear();
        }
        map_[x][y].clear();
      }
      map_[x].clear();
    }
    map_.clear();
  }
#if DEBUG_THIS
  std::cout << map.size() << "\n";
#endif
}

TileMap::TileMap(float grid_size, int width, int height,
                 _::AString texture_file) {
  grid_size_f_ = grid_size;
  grid_size_f_ = static_cast<int>(grid_size_f_);
  max_size_world_grid_.x = width;
  max_size_world_grid_.y = height;
  max_size_world_f_.x = static_cast<float>(width) * grid_size;
  max_size_world_f_.y = static_cast<float>(height) * grid_size;
  layers = 1;
  texture_file = texture_file;

  from_x = 0;
  to_x = 0;
  from_y = 0;
  to_y = 0;
  layer = 0;

  map_.resize(max_size_world_grid_.x, _::Array<_::Array<_::Array<Tile*> > >());
  for (int x = 0; x < max_size_world_grid_.x; x++) {
    for (int y = 0; y < max_size_world_grid_.y; y++) {
      map_[x].resize(max_size_world_grid_.y, _::Array<_::Array<Tile*> >());

      for (int z = 0; z < layers; z++) {
        map_[x][y].resize(layers, _::Array<Tile*>());
      }
    }
  }

  if (!tile_sheet_.LoadFromFile(texture_file))
    D_COUT("\nERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: "
           << texture_file);

  collision_box_.setSize(sf::Vector2f(grid_size, grid_size));
  collision_box_.setFillColor(sf::Color(255, 0, 0, 50));
  collision_box_.setOutlineColor(sf::Color::Red);
  collision_box_.setOutlineThickness(1.f);
}

TileMap::TileMap(const _::AString filename) {
  from_x = 0;
  to_x = 0;
  from_y = 0;
  to_y = 0;
  layer = 0;

  LoadFromFile(filename);

  collision_box_.setSize(sf::Vector2f(grid_size_f_, grid_size_f_));
  collision_box_.setFillColor(sf::Color(255, 0, 0, 50));
  collision_box_.setOutlineColor(sf::Color::Red);
  collision_box_.setOutlineThickness(1.f);
}

TileMap::~TileMap() { clear(); }

const bool TileMap::TileEmpty(const int x, const int y, const int z) const {
  if (x >= 0 && x < max_size_world_grid_.x && y >= 0 &&
      y < max_size_world_grid_.y && z >= 0 && z < layers)

  {
    return map_[x][y][z].empty();
  }

  return false;
}

const sf::Texture* TileMap::TileSheet() const { return &tile_sheet_; }

const int TileMap::LayerSize(const int x, const int y, const int layer) const {
  if (x >= 0 && x < static_cast<int>(map_.size())) {
    if (y >= 0 && y < static_cast<int>(map_[x].size())) {
      if (layer >= 0 && layer < static_cast<int>(map_[x][y].size())) {
        return map_[x][y][layer].size();
      }
    }
  }

  return -1;
}

const sf::Vector2i& TileMap::SizeGridMax() const {
  return max_size_world_grid_;
}

const sf::Vector2f& TileMap::SizeMaxF() const { return max_size_world_f_; }

void TileMap::AddTile(const int x, const int y, const int z,
                      const sf::IntRect& texture_rect, const bool& collision,
                      const short& type) {
  if (x < max_size_world_grid_.x && x >= 0 && y < max_size_world_grid_.y &&
      y >= 0 && z < layers && z >= 0) {
    map_[x][y][z].Push(new TileRegular(type, x, y, grid_size_f_, tile_sheet_,
                                       texture_rect, collision));
    D_CUT("\nDEGBUG: ADDED TILE!");
  }
}

void TileMap::AddTile(const int x, const int y, const int z,
                      const sf::IntRect& texture_rect, const int enemy_type,
                      const int enemy_amount, const int enemy_tts,
                      const int enemy_md) {
  if (x < max_size_world_grid_.x && x >= 0 && y < max_size_world_grid_.y &&
      y >= 0 && z < layers && z >= 0) {
    map_[x][y][z].Push(new EnemySpawnerTile(x, y, grid_size_f_, tile_sheet_,
                                            texture_rect, enemy_type,
                                            enemy_amount, enemy_tts, enemy_md));
  }
}

void TileMap::RemoveTile(const int x, const int y, const int z,
                         const int type) {
  if (x < max_size_world_grid_.x && x >= 0 && y < max_size_world_grid_.y &&
      y >= 0 && z < layers && z >= 0) {
    if (!map_[x][y][z].empty()) {
      if (type >= 0) {
        if (map_[x][y][z].back()->getType() == type) {
          delete map_[x][y][z][map_[x][y][z].size() - 1];
          map_[x][y][z].pop_back();
        }
      } else {
        delete map_[x][y][z][map_[x][y][z].size() - 1];
        map_[x][y][z].pop_back();
        D_COUT("\nRemoved tile.")
      }
    }
  }
}

void TileMap::SaveToFile(const _::AString filename) {
  /*Saves the entire tilemap to a text-file.
  Format:
  Basic:
  Size x y
  grid_size
  layers
  texture file

  All tiles:
  type
  gridPos x y layer
  Texture rect x y
  collision
  tile_specific...
  */

  std::ofstream out_file;

  out_file.open(filename);

  if (out_file.is_open()) {
    out_file << max_size_world_grid_.x << " " << max_size_world_grid_.y << "\n"
             << grid_size_f_ << "\n"
             << layers << "\n"
             << texture_file_ << "\n";

    for (int x = 0; x < max_size_world_grid_.x; x++) {
      for (int y = 0; y < max_size_world_grid_.y; y++) {
        for (int z = 0; z < layers; z++) {
          if (!map_[x][y][z].empty()) {
            for (size_t k = 0; k < map_[x][y][z].size(); k++) {
              out_file << x << " " << y << " " << z << " "
                       << map_[x][y][z][k]->ToString() << " ";
            }
          }
        }
      }
    }
  } else {
    D_COUT("\nError:Saving tilemap: " << filename);
  }

  out_file.close();
}

void TileMap::LoadFromFile(const _::AString filename) {
  std::ifstream in_file;

  in_file.open(filename);

  if (in_file.is_open()) {
    sf::Vector2i size;
    int grid_size = 0;
    int layers = 0;
    _::AString texture_file = "";
    int x = 0;
    int y = 0;
    int z = 0;
    int trX = 0;
    int trY = 0;
    bool collision = false;
    short type = 0;

    in_file >> size.x >> size.y >> grid_size >> layers >> texture_file_;

    grid_size_f_ = static_cast<float>(grid_size);
    grid_size_f_ = grid_size;
    max_size_world_grid_.x = size.x;
    max_size_world_grid_.y = size.y;
    max_size_world_f_.x = static_cast<float>(size.x * grid_size);
    max_size_world_f_.y = static_cast<float>(size.y * grid_size);
    layers = layers;
    texture_file_ = texture_file_;

    clear();

    map_.resize(max_size_world_grid_.x,
                _::Array<_::Array<_::Array<Tile*> > >());
    for (int x = 0; x < max_size_world_grid_.x; x++) {
      for (int y = 0; y < max_size_world_grid_.y; y++) {
        map_[x].resize(max_size_world_grid_.y, _::Array<_::Array<Tile*> >());

        for (int z = 0; z < layers; z++) {
          map_[x][y].resize(layers, _::Array<Tile*>());
        }
      }
    }

    if (!tile_sheet_.LoadFromFile(texture_file_))
      D_COUT(
          "\nError:Tilemap failed to load TileTextureSheet:" << texture_file_);

    while (in_file >> x >> y >> z >> type) {
      if (type == TileTypes::kSpawnerEnemy) {
        int enemy_type = 0;
        int enemy_am = 0;
        int enemy_tts = 0;
        int enemy_md = 0;

        in_file >> trX >> trY >> enemy_type >> enemy_am >> enemy_tts >>
            enemy_md;

        map_[x][y][z].Push(new EnemySpawnerTile(
            x, y, grid_size_f_, tile_sheet_,
            sf::IntRect(trX, trY, grid_size_f_, grid_size_f_), enemy_type,
            enemy_am, enemy_tts, enemy_md));
      } else {
        in_file >> trX >> trY >> collision;

        map_[x][y][z].Push(new TileRegular(
            type, x, y, grid_size_f_, tile_sheet_,
            sf::IntRect(trX, trY, grid_size_f_, grid_size_f_), collision));
      }
    }
  } else {
    D_COUT("\nError:Error reading tilemap: " << filename);
  }

  in_file.close();
}

const bool TileMap::CheckType(const int x, const int y, const int z,
                              const int type) const {
  return map_[x][y][layer].back()->getType() == type;
}

void TileMap::UpdateWorldBoundsCollision(Entity* entity, const float& dt) {
  if (entity->getPosition().x < 0.f) {
    entity->PositionSet(0.f, entity->getPosition().y);
    entity->StopVelocityX();
  } else if (entity->getPosition().x + entity->GlobalBounds().width >
             max_size_world_f_.x) {
    entity->PositionSet(max_size_world_f_.x - entity->GlobalBounds().width,
                        entity->getPosition().y);
    entity->StopVelocityX();
  }
  if (entity->getPosition().y < 0.f) {
    entity->PositionSet(entity->getPosition().x, 0.f);
    entity->StopVelocityY();
  } else if (entity->getPosition().y + entity->GlobalBounds().height >
             max_size_world_f_.y) {
    entity->PositionSet(entity->getPosition().x,
                        max_size_world_f_.y - entity->GlobalBounds().height);
    entity->StopVelocityY();
  }
}

void TileMap::UpdateTileCollision(Entity* entity, const float& dt) {
  // TILES
  layer = 0;

  from_x = entity->GridPosition(grid_size_f_).x - 1;
  if (from_x < 0)
    from_x = 0;
  else if (from_x > max_size_world_grid_.x)
    from_x = max_size_world_grid_.x;

  to_x = entity->GridPosition(grid_size_f_).x + 3;
  if (to_x < 0)
    to_x = 0;
  else if (to_x > max_size_world_grid_.x)
    to_x = max_size_world_grid_.x;

  from_y = entity->GridPosition(grid_size_f_).y - 1;
  if (from_y < 0)
    from_y = 0;
  else if (from_y > max_size_world_grid_.y)
    from_y = max_size_world_grid_.y;

  to_y = entity->GridPosition(grid_size_f_).y + 3;
  if (to_y < 0)
    to_y = 0;
  else if (to_y > max_size_world_grid_.y)
    to_y = max_size_world_grid_.y;

  for (int x = from_x; x < to_x; x++) {
    for (int y = from_y; y < to_y; y++) {
      for (size_t k = 0; k < map_[x][y][layer].size(); k++) {
        sf::FloatRect playerBounds = entity->GlobalBounds();
        sf::FloatRect wallBounds = map[x][y][layer][k]->GlobalBounds();
        sf::FloatRect nextPositionBounds = entity->NextPositionBounds(dt);

        if (map_[x][y][layer][k]->getCollision() &&
            map_[x][y][layer][k]->intersects(nextPositionBounds)) {
          // Bottom collision
          if (playerBounds.Top < wallBounds.Top &&
              playerBounds.Top + playerBounds.height <
                  wallBounds.Top + wallBounds.height &&
              playerBounds.left < wallBounds.left + wallBounds.width &&
              playerBounds.left + playerBounds.width > wallBounds.left) {
            entity->StopVelocityY();
            entity->PositionSet(playerBounds.left,
                                wallBounds.Top - playerBounds.height);
          }

          // Top collision
          else if (playerBounds.Top > wallBounds.Top &&
                   playerBounds.Top + playerBounds.height >
                       wallBounds.Top + wallBounds.height &&
                   playerBounds.left < wallBounds.left + wallBounds.width &&
                   playerBounds.left + playerBounds.width > wallBounds.left) {
            entity->StopVelocityY();
            entity->PositionSet(playerBounds.left,
                                wallBounds.Top + wallBounds.height);
          }

          // Right collision
          if (playerBounds.left < wallBounds.left &&
              playerBounds.left + playerBounds.width <
                  wallBounds.left + wallBounds.width &&
              playerBounds.Top < wallBounds.Top + wallBounds.height &&
              playerBounds.Top + playerBounds.height > wallBounds.Top) {
            entity->StopVelocityX();
            entity->PositionSet(wallBounds.left - playerBounds.width,
                                playerBounds.Top);
          }

          // Left collision
          else if (playerBounds.left > wallBounds.left &&
                   playerBounds.left + playerBounds.width >
                       wallBounds.left + wallBounds.width &&
                   playerBounds.Top < wallBounds.Top + wallBounds.height &&
                   playerBounds.Top + playerBounds.height > wallBounds.Top) {
            entity->StopVelocityX();
            entity->PositionSet(wallBounds.left + wallBounds.width,
                                playerBounds.Top);
          }
        }
      }
    }
  }
}

void TileMap::UpdateTiles(Entity* entity, const float& dt,
                          EnemySystem& enemySystem) {
  layer = 0;

  from_x = entity->GridPosition(grid_size_f_).x - 15;
  if (from_x < 0)
    from_x = 0;
  else if (from_x > max_size_world_grid_.x)
    from_x = max_size_world_grid_.x;

  to_x = entity->GridPosition(grid_size_f_).x + 16;
  if (to_x < 0)
    to_x = 0;
  else if (to_x > max_size_world_grid_.x)
    to_x = max_size_world_grid_.x;

  from_y = entity->GridPosition(grid_size_f_).y - 8;
  if (from_y < 0)
    from_y = 0;
  else if (from_y > max_size_world_grid_.y)
    from_y = max_size_world_grid_.y;

  to_y = entity->GridPosition(grid_size_f_).y + 9;
  if (to_y < 0)
    to_y = 0;
  else if (to_y > max_size_world_grid_.y)
    to_y = max_size_world_grid_.y;

  for (int x = from_x; x < to_x; x++) {
    for (int y = from_y; y < to_y; y++) {
      for (size_t k = 0; k < map_[x][y][layer].size(); k++) {
        map_[x][y][layer][k]->Update();

        if (map_[x][y][layer][k]->getType() == TileTypes::kSpawnerEnemy) {
          EnemySpawnerTile* es =
              dynamic_cast<EnemySpawnerTile*>(map_[x][y][layer][k]);
          if (es) {
            if (!es->GetSpawned()) {
              enemySystem.CreateEnemy(RAT, x * grid_size_f_, y * grid_size_f_);
              es->SetSpawned(true);
            }
          }
        }
      }
    }
  }
}

void TileMap::Update(Entity* entity, const float& dt) {}

void TileMap::Render(sf::RenderTarget& target, const sf::Vector2i& gridPosition,
                     sf::Shader* shader, const sf::Vector2f playerPosition,
                     const bool show_collision) {
  layer = 0;

  from_x = gridPosition.x - 15;
  if (from_x < 0)
    from_x = 0;
  else if (from_x > max_size_world_grid_.x)
    from_x = max_size_world_grid_.x;

  to_x = gridPosition.x + 16;
  if (to_x < 0)
    to_x = 0;
  else if (to_x > max_size_world_grid_.x)
    to_x = max_size_world_grid_.x;

  from_y = gridPosition.y - 8;
  if (from_y < 0)
    from_y = 0;
  else if (from_y > max_size_world_grid_.y)
    from_y = max_size_world_grid_.y;

  to_y = gridPosition.y + 9;
  if (to_y < 0)
    to_y = 0;
  else if (to_y > max_size_world_grid_.y)
    to_y = max_size_world_grid_.y;

  for (int x = from_x; x < to_x; x++) {
    for (int y = from_y; y < to_y; y++) {
      for (size_t k = 0; k < map_[x][y][layer].size(); k++) {
        if (map_[x][y][layer][k]->getType() == TileTypes::kDoodad) {
          deferred_render_stack_.push(map_[x][y][layer][k]);
        } else {
          if (shader)
            map_[x][y][layer][k]->Render(target, shader, playerPosition);
          else
            map_[x][y][layer][k]->Render(target);
        }

        if (show_collision) {
          if (map_[x][y][layer][k]->getCollision()) {
            collision_box_.PositionSet(map_[x][y][layer][k]->getPosition());
            target.draw(collision_box_);
          }
        }

        if (map_[x][y][layer][k]->getType() == TileTypes::kSpawnerEnemy) {
          collision_box_.PositionSet(map_[x][y][layer][k]->getPosition());
          target.draw(collision_box_);
        }
      }
    }
  }
}

void TileMap::RenderDeferred(sf::RenderTarget& target, sf::Shader* shader,
                             const sf::Vector2f playerPosition) {
  while (!deferred_render_stack_.empty()) {
    if (shader)
      deferred_render_stack_.Top()->Render(target, shader, playerPosition);
    else
      deferred_render_stack_.Top()->Render(target);

    deferred_render_stack_.pop();
  }
}
