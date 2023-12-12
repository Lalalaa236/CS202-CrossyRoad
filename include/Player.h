#ifndef PLAYER_H
#define PLAYER_H

#include "GameSettings.h"
#include "TextureHolder.h"

class Player {
private:
    bool isMoving;
    std::pair<float, float> position;
    std::pair<float, float> targetPosition;
    float mapSpeed;
    bool isAlive;
    Rectangle boxCollision;
    Rectangle frame[4];
    float vSpeed;
    float hSpeed;
    const int frames = 4;
    const int fps = 24;
    Texture2D* atlas;
    int frameCount;
    float elapsedTime;

    void up();
    void down();
    void left();
    void right();

public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };

    Player(float x, float y, float mapSpeed, Textures::ID skin);
    Player(float x, float y, float mapSpeed, Texture2D* atlas);
    Player(float x, float y, bool isAlive, Textures::ID skin);

    // Getter & Setter
    void setPosition(float x, float y);
    void setTargetPosition(float x, float y);
    void setSpeed(float vSpeed, float hSpeed);
    void setFrameCount(int frameCount);
    void setIsAlive(bool isAlive);
    void setMapSpeed(float mapSpeed);
    void setSkin(Textures::ID skin);
    void setMoving(bool isMoving);
    Rectangle getBoxCollision() const;
    std::pair<float, float> getPosition() const;
    std::pair<float, float> getTargetPosition() const;
    std::pair<float, float> getSpeed() const;
    int getFrameCount() const;
    bool getIsAlive() const;
    bool getMoving() const;

    void draw();
    void update();
    void move(Direction direction);
    void setSpeed(float vSpeed, float hSpeed);
};

#endif