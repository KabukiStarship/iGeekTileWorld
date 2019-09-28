#ifndef IGEEK_RPG_TOOLKIT_DEFAULTEDITORMODE
#define IGEEK_RPG_TOOLKIT_DEFAULTEDITORMODE

#include "modeeditor.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode : public EditorMode {
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
  void initGui();

 public:
  DefaultEditorMode(StateData* state_data, TileMap* tile_map,
                    EditorStateData* editor_state_data);
  virtual ~DefaultEditorMode();

  void updateInput(const float& dt);
  void updateGui(const float& dt);
  void Update(const float& dt);

  void renderGui(sf::RenderTarget& target);
  void Render(sf::RenderTarget& target);
};

#endif  //! IGEEK_RPG_TOOLKIT_DEFAULTEDITORMODE
