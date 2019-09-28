#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_GAMESTATE
#define IGEEK_RPG_TOOLKIT_GAMESTATE

#include "bow.h"
#include "menu_pause.h"
#include "player_gui.h"
#include "state.h"
#include "sword.h"
#include "tilemap.h"

class GameState : public State {
  sf::View view_;
  sf::Vector2i view_grid_position_;
  sf::RenderTexture render_texture_;
  sf::Sprite render_sprite_;
  sf::Font font_;
  PauseMenu* pmenu_;
  sf::Shader core_shader_;
  Player* player_;
  PlayerGUI* player_gui_;
  sf::Texture texture;
  _::Array<Enemy*> active_enemies_;
  EnemySystem* enemy_system_;
  TileMap* tiles_;

  void InitDeferredRender();
  void InitView();
  void InitKeybinds();
  void InitFonts();
  void initTextures();
  void InitPauseMenu();
  void InitShaders();
  void InitPlayers();
  void InitPlayerGUI();
  void initEnemySystem();
  void initTileMap();

 public:
  GameState(StateData* state_data);
  virtual ~GameState();

  void updateView(const float& dt);
  void UpdateInput(const float& dt);
  void updatePlayerInput(const float& dt);
  void updatePlayerGUI(const float& dt);
  void UpdatePauseMenuButtons();
  void updateTileMap(const float& dt);
  void updatePlayer(const float& dt);
  void updateEnemies(const float& dt);
  void Update(const float& dt);
  void Render(sf::RenderTarget* target = nullptr);
};

#endif
