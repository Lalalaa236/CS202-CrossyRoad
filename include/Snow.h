#pragma once

#include "SpecialEffect.h"

class Snow : public SpecialEffect
{
public:
    Snow();
    void update(int screenWidth, int screenHeight) override;
    void drawTo() override;
    ~Snow() override;
};
