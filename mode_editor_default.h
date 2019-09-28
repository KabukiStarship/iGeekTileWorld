#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_DEFAULTEDITORMODE
#define IGEEK_RPG_TOOLKIT_DEFAULTEDITORMODE

#include "mode_editor"

class DefaultEditorMode : public ModeEditor {
 private:
  sf::Text cursorText;
  sf::RectangleShape sidebar;
  sf::RectangleShape selectorRect;
  gui::TextureSelector* textureSelector;
  sf::IntRect textureRect;
  bool collision;
  short type;
  int layer;
  bool tileAddLock;

  void InitVariables();
  void InitGUI();

 public:
  DefaultEditorMode(StateData* state_data, TileMap* tiles,
                    EditorStateData* editor_state_data);
  virtual ~DefaultEditorMode();

  void UpdateInput(const float& dt);
  void UpdateGUI(const float& dt);
  void Update(const float& dt);

  void RenderGUI(sf::RenderTarget& target);
  void Render(sf::RenderTarget& target);
};

#endif
