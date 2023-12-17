#include "score.h"

HighScore::HighScore() : currentScore(0) {
    highScoreList.resize(3);
    loadData();
}
HighScore &HighScore::getHighScoreManager() {
    static HighScore instance;
    return instance;
}

HighScore::~HighScore() {
    highScoreList.resize(0);
}

int HighScore::getCurrentScore() const {
    return currentScore;
}

int HighScore::getHighestScore(int t) const {
    return highScoreList[t - 1];
}

void HighScore::setCurrentScore(int score) {
    currentScore = score;
}

void HighScore::updateHighestScore() {
    for (int i = 0; i < 3; i++) {
        if (currentScore >= highScoreList[i]) {
            //shift
            for (int j = i + 1; j < 3; j++) {
                highScoreList[j] = highScoreList[j - 1];
            }
            highScoreList[i] = currentScore;
            break;
        }
    }
}

void HighScore::loadData(){
    std::ifstream fin("highScore.txt");
    for (int i = 0; i < 3; i++){
        fin >> highScoreList[i];
    }
    fin.close();
}

void HighScore::unloadData(){
    std::ofstream fout("highScore.txt");
    for (int i = 0; i < 3; i++){
        fout << highScoreList[i] << "\n";
    }
    fout.close();
}
