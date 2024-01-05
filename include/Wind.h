#pragma once

#include "SpecialEffect.h"

class Wind : public SpecialEffect {
private:
    float windSpeed;
    Rectangle rectangle;

public:
    Wind();
    void update(int screenWidth, int screenHeight) override;
    void drawTo() override;
    ~Wind() override;
};
