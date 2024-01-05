#include "Wind.h"
#include <raylib.h>

Wind::Wind() : windSpeed(5.0f), rectangle({50, 50, 100, 30}) {}

void Wind::update(int screenWidth, int screenHeight) {
    // Update the wind effect logic here
    rectangle.x += windSpeed;

    // Reset position when the rectangle goes off-screen
    if (rectangle.x > screenWidth)
        rectangle.x = -rectangle.width;
}

void Wind::drawTo() {
    // Draw the wind effect here
    DrawRectanglePro(rectangle, {rectangle.width / 2, rectangle.height / 2}, 0, SKYBLUE);
}

Wind::~Wind() {}
