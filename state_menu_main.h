#pragma once
#include "stdafx.h"

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "gui.h"
#include "state_editor.h"
#include "state_game.h"
#include "state_settings.h"

class StateMenuMain : public State {
  sf::Texture background_texture_;
  sf::RectangleShape background_;
  sf::Font font_;

  sf::RectangleShape bttn_background_;
  _::ADic<_::AString, gui::Button*> buttons_;

  void InitVariables();
  void InitFonts();
  void InitKeybinds();
  void InitGUI();
  void ResetGUI();

 public:
  StateMenuMain(StateData* state_data);
  virtual ~StateMenuMain();

  void UpdateInput(const float& dt);
  void UpdateButtons();
  void Update(const float& dt);
  void RenderButtons(sf::RenderTarget& target);
  void Render(sf::RenderTarget* target = nullptr);
};

#endif
