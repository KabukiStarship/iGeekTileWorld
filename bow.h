#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_BOW
#define IGEEK_RPG_TOOLKIT_BOW

#include "weapon_ranged.h"

class WeaponRanged;

class Bow : public WeaponRanged {
 public:
  Bow();
  virtual ~Bow();
};

#endif
