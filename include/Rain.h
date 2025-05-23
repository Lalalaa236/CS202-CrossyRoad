#pragma once

#include "SpecialEffect.h"

class Rain : public SpecialEffect
{
public:
    Rain();
    void update(int screenWidth, int screenHeight) override;
    void drawTo() override;
    ~Rain() override;
};
