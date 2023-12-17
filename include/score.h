#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include<vector>
#include<fstream>
class HighScore
{
private:
    int currentScore;
    std::vector<int> highScoreList;


public:
    static HighScore& getHighScoreManager();
    HighScore();
    ~HighScore();

    int getCurrentScore() const;
    int getHighestScore(int t) const;

    void setCurrentScore(int score);
    void updateHighestScore();
    void loadData();
    void unloadData();
};

#endif
