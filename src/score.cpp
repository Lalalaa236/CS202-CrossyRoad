#include "score.h"

HighScore::HighScore(): currentScore(0){
    highScoreList.resize(3);
    for (int i = 0; i < 3; i++){
        highScoreList[i] = 0;
    }
}
HighScore& HighScore::getHighScoreManager()
{
    static HighScore instance;
    return instance;
}

HighScore::~HighScore() {
    highScoreList.resize(0);
}

int HighScore::getCurrentScore() const
{
    return currentScore;
}

int HighScore::getHighestScore(int t) const
{
    return highScoreList[t-1];
}

void HighScore::setCurrentScore(int score)
{
    currentScore = score;
}

void HighScore::updateHighestScore()
{
    for (int i = 0; i < highScoreList.size(); i++){
        if (currentScore >= highScoreList[i]){
            highScoreList[i] = currentScore;
            break;
        }
    }
}
