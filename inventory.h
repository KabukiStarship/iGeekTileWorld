#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_INVENTORY
#define IGEEK_RPG_TOOLKIT_INVENTORY

#include "item.h"

class Inventory {
 private:
  Item** items_;
  unsigned item_count_;
  unsigned item_count_max_;

  void Initialize();
  void Expand();
  void Nullify(const unsigned from = 0);
  void FreeMemory();

 public:
  Inventory();
  virtual ~Inventory();
};
#endif
