#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_SETTINGSSTATE
#define IGEEK_RPG_TOOLKIT_SETTINGSSTATE

#include "gui.h"
#include "state.h"

class StateSettings : public State {
  sf::Texture background_texture_;
  sf::RectangleShape background_;
  sf::Font font_;

  _::ADic<_::AString, gui::Button*> buttons_;
  _::ADic<_::AString, gui::DropDownList*> drop_down_lists_;

  sf::Text options_text_;

  _::Array<sf::VideoMode> modes_;

  void InitVariables();
  void InitFonts();
  void InitKeybinds();
  void InitGUI();
  void ResetGUI();

 public:
  StateSettings(StateData* state_data);
  virtual ~StateSettings();

  void UpdateInput(const float& dt);
  void UpdateGUI(const float& dt);
  void Update(const float& dt);
  void RenderGUI(sf::RenderTarget& target);
  void Render(sf::RenderTarget* target = nullptr);
};

#endif
