#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_ENEMYEDITORMODE
#define IGEEK_RPG_TOOLKIT_ENEMYEDITORMODE

#include "mode_editor.h"
#include "tile_spawner_enemy.h"

class ModeEditorEnemy : public ModeEditor {
  sf::Text cursor_text_;        //<
  sf::RectangleShape sidebar_,  //<
      selector_rect_;           //<
  sf::IntRect texture_rect_;    //<
  int type_, amount_,           //<
      time_to_spawn_;           //<
  float distance_max_;          //<

  void InitVariables();
  void InitGUI();

 public:
  ModeEditorEnemy(StateData* state_data, TileMap* tiles,
                  EditorStateData* editor_state_data);
  virtual ~ModeEditorEnemy();

  void UpdateInput(const float& dt);
  void UpdateGUI(const float& dt);
  void Update(const float& dt);

  void RenderGUI(sf::RenderTarget& target);
  void Render(sf::RenderTarget& target);
};

#endif  //! ENEMYEDITORMODE_H
