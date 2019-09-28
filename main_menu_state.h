#ifndef IGEEK_RPG_TOOLKIT_MAINMENUSTATE
#define IGEEK_RPG_TOOLKIT_MAINMENUSTATE

#include "EditorState.h"
#include "GameState.h"
#include "SettingsState.h"
#include "gui.h"

class MainMenuState : public State {
 private:
  // Variables
  sf::Texture backgroundTexture;
  sf::RectangleShape background;
  sf::Font font;

  sf::RectangleShape btnBackground;
  std::map<_::AString, gui::Button*> buttons;

  // Functions
  void InitVariables();
  void initFonts();
  void initKeybinds();
  void initGui();
  void resetGui();

 public:
  MainMenuState(StateData* state_data);
  virtual ~MainMenuState();

  // Functions
  void updateInput(const float& dt);
  void updateButtons();
  void Update(const float& dt);
  void renderButtons(sf::RenderTarget& target);
  void Render(sf::RenderTarget* target = nullptr);
};

#endif
