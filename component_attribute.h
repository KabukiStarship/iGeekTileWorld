#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_COMPONENTATTRIBUTE
#define IGEEK_RPG_TOOLKIT_COMPONENTATTRIBUTE

class AttributeComponent {
 public:
  int level,             //<
      exp,               //<
      exp_next,          //<
      attribute_points,  //<
      vitality,          //<
      strength,          //<
      dexterity,         //<
      agility,           //<
      intelligence,      //<
      hp,                //<
      hp_max,            //<
      damage_min,        //<
      damage_max,        //<
      accuracy,          //<
      defence,           //<
      luck;

  AttributeComponent(int level);
  virtual ~AttributeComponent();

  _::AString DebugPrint() const;

  void LoseHP(const int hp);
  void GainHP(const int hp);
  void LoseEXP(const int exp);
  void GainExp(const int exp);

  void UpdateStats(const bool reset);
  void UpdateLevel();

  void Update();
};
#endif
