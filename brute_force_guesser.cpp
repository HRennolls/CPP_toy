#include <iostream>
#include <ctime>

std::string abet = "abcdefghijklmnopqrstuvwxyz ";
std::string goal = "oremob";

std::string string_gen(){
    std::string guess = "";
    for (int i=0; i< goal.length(); i++){
        int r = std::rand() % 28;
        char c = abet[r];
        guess += c;
    }
    return guess;
}

double scorer(std::string sentence){
    double count = 0;
    for (int i=0; i<goal.length(); i++){
        if (sentence[i] == goal[i]){
            count += 1;
        }
    }
    double score = count/goal.length();
    return score;
}

int runner(){
    double score = 0;
    int tries = 0;
    std::string best_guess = " ";
    while (score < 1){
        std::string guess = string_gen();
        double tscore = scorer(guess);
        if (tscore > score){
            score = tscore;
            best_guess = guess;
        }
        tries += 1;
        if (tries%10000 == 0){
            std::cout << "Tries: " << tries << std::endl;
            std::cout << "Best guess: " << best_guess << std::endl;
            std::cout << score << std::endl;
        }
    }
    std::cout << best_guess << "  " << score << std::endl;
    return tries;
}



int main() {
    srand(time(NULL));
    std::cout << runner();
    return 0;
}  