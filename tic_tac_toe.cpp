#include <iostream>
#include <algorithm>
#include <vector>
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))

char gamestate[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};


void drawBoard(char board[3][3]){ //prints board to terminal
    std::cout << " " << gamestate[0][0] << " | " << gamestate[0][1] << " | " << gamestate[0][2] << std::endl;
    std::cout << "___________" << std::endl;
    std::cout << " " << gamestate[1][0] << " | " << gamestate[1][1] << " | " << gamestate[1][2] << std::endl;
    std::cout << "___________" << std::endl;
    std::cout << " " << gamestate[2][0] << " | " << gamestate[2][1] << " | " << gamestate[2][2] << std::endl;
    std::cout <<std::endl;
    std::cout <<std::endl;
    std::cout <<std::endl;
}



void unmakeMove(int digit, char board[3][3]){
    board[(digit-1)/3][(digit-1)%3] = '0' + digit;
}

int playerInput(){
    int digit{};
    while (true){
        std::cout<<"Please enter: ";
        std::cin>>digit;
        if (gamestate[(digit-1)/3][(digit-1)%3] != 'X'&&
            gamestate[(digit-1)/3][(digit-1)%3] != 'O'){break;}
    }
    return digit;
}

std::vector<int> actions(char board[3][3]){
    //returns set of possible moves
    std::vector<int> actions{};
    for (int i{}; i<3; i++){
        for (int j{}; j<3; j++){
            if (board[i][j] != 'X' && board[i][j] != 'O'){
                actions.push_back(i+1+j*3);
            }
        }
    }
    return actions;
}

char player(char board[3][3]){
    int xcount{};
    int ocount{};
    for (int i{}; i<3; i++){
        for (int j{}; j<3; j++){
            if (board[i][j] == 'X'){
                xcount++;
            }
            else if(board[i][j] == 'O'){
                ocount++;
            }
        }
    }
    if (xcount == ocount){
        return 'X';
    }
    else {
        return 'O';
    }
}


void makeMove(int digit, char board[3][3]){
    board[(digit-1)/3][(digit-1)%3] = player(board);
}

bool checkDraw(char board[3][3]){
    int count{};
    for (int i{}; i<3; i++){
        for (int j{}; j<3; j++){
            if (board[i][j]=='X'||board[i][j]=='O'){
                count++;
            }
        }
    }
    if (count == 9){;
        return true;}
    return false;
}

char terminal(char board[3][3]){
    for (int i{}; i<3; i++){
        //row check
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            (board[i][0] == 'X' || board[i][0] == 'O')){
                return board[i][0];
            }
        //column check
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            (board[0][i] == 'X' || board[0][i] == 'O')){
                return board[0][i];
            }   
        }
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        (board[1][1] == 'X' || board[1][1] == 'O')){
            return board[1][1];
        }
    if (board[2][0] == board[1][1] &&
        board[1][1] == board[0][2] &&
        (board[1][1] == 'X' || board[1][1] == 'O')){
            return board[1][1];
        }
    if (checkDraw(board)){
        return 'd';
    }
    return 'n';
    }


int utility(char board[3][3]){
    if      (terminal(board) == 'X'){return 1;}
    else if (terminal(board) == 'O'){return -1;}
    else    {return 0;}
}




int miniMax(char board[3][3], bool isMaximizingPlayer = true){

    if (terminal(board) != 'n'){
        return utility(board);
        }
    if (isMaximizingPlayer){
        int bestVal = -9999;

        for (int i{}; i<3; i++){
            for (int j{}; j<3; j++){
                if (board[i][j] != 'X' && board[i][j] != 'O'){
                    board[i][j] = player(board);
                    int value = miniMax(board, false);
                    bestVal = new_max( bestVal, value);
                    board[i][j] = '0' + i*3+1+j;
                    }
                }
            }
        return bestVal;
    }
    else {
        int bestVal = 9999;

        for (int i{}; i<3; i++){
            for (int j{}; j<3; j++){
                if (board[i][j] != 'X' && board[i][j] != 'O'){
                    board[i][j] = player(board);
                    int value = miniMax(board, true);
                    bestVal = new_min(bestVal, value);
                    board[i][j] = '0' + i*3+j+1;
                    
                    }
                }
            }
        return bestVal;
    }
}


int findBestMove(char board[3][3]){
    int bestVal{9999};
    int bestAct{};

    for (int i{}; i<3; i++){
            for (int j{}; j<3; j++){
                if (board[i][j] != 'X' && board[i][j] != 'O'){
                    board[i][j] = player(board);
                    int value{miniMax(board, true)};
                    if (value < bestVal){
                        bestVal = value;
                        bestAct = i*3+j+1;
                    }
                    board[i][j] = '0' + i*3+j+1;
                }
            }
        }
    
    return bestAct;
}

int main(){
    bool running{true};
    while (running){
        drawBoard(gamestate);
        makeMove(playerInput(), gamestate);
        if (terminal(gamestate) != 'n'){ 
            break;
        }
        
    
        makeMove(findBestMove(gamestate), gamestate);
        if (terminal(gamestate) != 'n'){
            break;
        }
    }

    drawBoard(gamestate);
    if (terminal(gamestate) != 'd'){
        std::cout << terminal(gamestate) << " won!";
    }
    else {
        std::cout << "Draw!";
    }
    return 0;
}
