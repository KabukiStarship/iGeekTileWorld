#ifndef IGEEK_RPG_TOOLKIT_EDITORMODE_H
#define IGEEK_RPG_TOOLKIT_EDITORMODE_H

#include "gui.h"
#include "state.h"
#include "tilemap.h"

class EditorStateData {
 public:
  EditorStateData(){};

  sf::View* view;
  sf::Font* font;
  float *keytime,   //<
      *keytimeMax;  //<

  _::ADictionary<_::AString, int>* keybinds;

  sf::Vector2i *mouse_pos_screen,  //<
      *mouse_pos_window,           //<
      *mouse_pos_view,             //<
      *mouse_pos_grid;             //<
};

class ModeEditor {
 protected:
  StateData* state_data_;
  EditorStateData* editor_state_data_;
  TileMap* tiles_;

 public:
  ModeEditor(StateData* state_data, TileMap* tiles,
             EditorStateData* editor_state_data);
  virtual ~ModeEditor();

  const bool KeyTime();

  virtual void UpdateInput(const float& dt) = 0;
  virtual void UpdateGUI(const float& dt) = 0;
  virtual void Update(const float& dt) = 0;

  virtual void RenderGUI(sf::RenderTarget& target) = 0;
  virtual void Render(sf::RenderTarget& target) = 0;
};

#endif
