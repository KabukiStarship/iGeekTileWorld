#pragma once
#include "stdafx.h"

#ifndef IGEEK_RPG_TOOLKIT_SKILLCOMPONENT
#define IGEEK_RPG_TOOLKIT_SKILLCOMPONENT

enum SKILLS { kConstitution = 0, kCombatMelee, kCombatRanged, kEndurance };

class SkillComponent {
  class Skill {
   private:
    int type_, level_, level_max_, exp_, next_exp_;

   public:
    Skill(int type) {
      type = type;
      level_ = 1;
      level_max_ = 99;
      exp_ = 0;
      next_exp_ = 100;
    }

    ~Skill() {}

    inline const int& getType() const { return type_; }
    inline const int& getLevel() const { return level_; }
    inline const int& getExp() const { return exp_; }
    inline const int& getExpNext() const { return next_exp_; }

    // Modifiers
    void setLevel(const int level) { level_ = level; }
    void setLevelCap(const int level_cap) { level_max_ = level_cap; }

    void GainExp(const int exp) {
      exp_ += exp;
      UpdateLevel();
    }

    void LoseExp(const int exp) { exp_ -= exp; }

    void UpdateLevel(const bool up = true) {
      // Changes the skill depending on if there is a deficit in the exp or not.

      if (up) {
        if (level_ < level_max_) {
          while (exp_ >= next_exp_) {
            if (level_ < level_max_) {
              level_++;
              next_exp_ = static_cast<int>(std::pow(level_, 2)) + level_ * 10 +
                          level_ * 2;
            }
          }
        }
      } else {
        if (level_ > 0) {
          while (exp_ < 0) {
            if (level_ > 0) {
              level_--;
              next_exp_ = static_cast<int>(std::pow(level_, 2)) + level_ * 10 +
                          level_ * 2;
            }
          }
        }
      }
    }

    void Update() {}
  };

  _::Array<Skill> skills;

 public:
  SkillComponent();
  virtual ~SkillComponent();

  const int GetSkill(const int skill) const;
  const void GainExp(const int skill, const int exp);
};

#endif
