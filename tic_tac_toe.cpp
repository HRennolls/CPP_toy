#include <iostream>

char gamestate [3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char token = 'X';

void draw_board(){
    std::cout << " " << gamestate[0][0] << " | " << gamestate[0][1] << " | " << gamestate[0][2] << std::endl;
    std::cout << "___________" << std::endl;
    std::cout << " " << gamestate[1][0] << " | " << gamestate[1][1] << " | " << gamestate[1][2] << std::endl;
    std::cout << "___________" << std::endl;
    std::cout << " " << gamestate[2][0] << " | " << gamestate[2][1] << " | " << gamestate[2][2] << std::endl;
}

void make_move(){
    int digit;
    while (true){
        std::cout<<"Please enter: ";
        std::cin>>digit;
        if (gamestate[(digit-1)/3][(digit-1)%3] != 'X'&&
            gamestate[(digit-1)/3][(digit-1)%3] != 'O'){break;}
    }
    gamestate[(digit-1)/3][(digit-1)%3] = token;
    if (token == 'X'){token = 'O';}
    else {token = 'X';}
}

char game_over(){
    for (int i; i<3; i++){
        //row check
        if (gamestate[i][0] == gamestate[i][1] &&
            gamestate[i][1] == gamestate[i][2]){
            return gamestate[i][0];
            }
        //column check
        if (gamestate[0][i] == gamestate[1][i] &&
            gamestate[1][i] == gamestate[2][i]){
            return gamestate[0][i];
            }   
        }
    if (gamestate[0][0] == gamestate[1][1] &&
        gamestate[1][1] == gamestate[2][2]){
            return gamestate[1][1];
        }
    if (gamestate[2][0] == gamestate[1][1] &&
        gamestate[1][1] == gamestate[0][2]){
            return gamestate[1][1];
        }
    return 'n';
    }

int main(){
    char winner = 'n';
    while (winner == 'n'){
        draw_board();
        make_move();
        winner = game_over();
    }
    draw_board();
    std::cout << winner << " wins!";
    return 0;
}