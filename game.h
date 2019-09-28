#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_GAME
#define IGEEK_RPG_TOOLKIT_GAME

#include "state_menu_main.h"

class Game {
  GraphicsSettings grfx_settings_;  //<
  StateData state_data_;            //<
  sf::RenderWindow *window_;        //<
  sf::Event event_;                 //<
  sf::Clock time_delta_;            //<
  float dt,                         //<
      grid_size_;
  _::AStack<State *> states_;                //<
  _::ADic<_::AString, int> supported_keys_;  //<

  void InitVariables();

  void InitGraphicsSettings();

  void InitWindow();

  void InitKeys();

  void InitStateData();

  void InitStates();

 public:
  Game();

  virtual ~Game();

  void EndApplication();

  void UpdateTimeDelta();

  void UpdateEvents();

  void Update();

  void Render();

  void Run();
};

#endif
