#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <utility>

class Player {
private:
    double x = 0.0, y = 0.0;    // position of player
    bool isAlive = true;        // is player alive?

public:
    Player();
    Player(double x, double y);
    ~Player();

    // Getters and Setters
    std::pair<double, double> getPosition() const;

    // Methods
    void draw();
    void update();
};


#endif // PLAYER_H