#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_EDITORSTATE_H
#define IGEEK_RPG_TOOLKIT_EDITORSTATE_H

#include "editor_modes.h"
#include "gui.h"
#include "menu_pause.h"
#include "state.h"
#include "tilemap.h"

enum EditorModes { kModeEditorDefault = 0, kModeEditorEnemy };

class StateEditor : public State {
  EditorStateData editor_state_data_;
  sf::View view_;
  float camera_speed_;
  sf::Font font_;
  PauseMenu* pmenu_;
  _::ADic<_::AString, gui::Button*> buttons_;
  TileMap* tiles_;
  _::Array<ModeEditor*> modes_;
  unsigned active_mode_;

  void InitVariables();
  void initEditorStateData();
  void InitView();
  void InitFonts();
  void InitKeybinds();
  void InitPauseMenu();
  void initButtons();
  void InitGUI();
  void initTileMap();
  void initModes();

 public:
  StateEditor(StateData* state_data);
  virtual ~StateEditor();

  void UpdateInput(const float& dt);
  void updateEditorInput(const float& dt);
  void UpdateButtons();
  void UpdateGUI(const float& dt);
  void UpdatePauseMenuButtons();
  void UpdateModes(const float& dt);
  void Update(const float& dt);
  void RenderButtons(sf::RenderTarget& target);
  void RenderGUI(sf::RenderTarget& target);
  void RenderModes(sf::RenderTarget& target);
  void Render(sf::RenderTarget* target = nullptr);
};

#endif
