#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_STATE
#define IGEEK_RPG_TOOLKIT_STATE

#include "player.h"
#include "settings_graphics.h"

class StateData {
 public:
  StateData(){};

  float grid_size_;
  sf::RenderWindow* window_;
  GraphicsSettings* gfx_settings_;
  _::ADic<_::AString, int>* supported_keys;
  _::AStack<State*>* states_;
};

class State {
 private:
  StateData* state_data_;
  _::AStack<State*>* states_;
  sf::RenderWindow* window_;
  _::ADic<_::AString, int>* supported_keys_;
  _::ADic<_::AString, int> keybinds;
  bool quit_, paused_;
  float keytime_, key_press_time_max_, size_grid_;

  sf::Vector2i mouse_pos_screen_;
  sf::Vector2i mouse_pos_window_;
  sf::Vector2f mouse_pos_view_;
  sf::Vector2i mouse_pos_grid_;

  _::ADic<_::AString, sf::Texture> textures_;

  virtual void InitKeybinds() = 0;

 public:
  State(StateData* state_data);
  virtual ~State();

  const bool& GetQuit() const;
  const bool KeyTime();

  void EndState();
  void PauseState();
  void UnpauseState();

  virtual void UpdateMousePositions(sf::View* view = nullptr);
  virtual void UpdateKeyTime(const float& dt);
  virtual void UpdateInput(const float& dt) = 0;
  virtual void Update(const float& dt) = 0;
  virtual void Render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
