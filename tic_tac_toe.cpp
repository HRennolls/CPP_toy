#include <iostream>
#include <algorithm>
#include <vector>
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))

char gamestate[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};


void drawBoard(){ //prints board to terminal
    std::cout << " " << gamestate[0][0] << " | " << gamestate[0][1] << " | " << gamestate[0][2] << std::endl;
    std::cout << "___________" << std::endl;
    std::cout << " " << gamestate[1][0] << " | " << gamestate[1][1] << " | " << gamestate[1][2] << std::endl;
    std::cout << "___________" << std::endl;
    std::cout << " " << gamestate[2][0] << " | " << gamestate[2][1] << " | " << gamestate[2][2] << std::endl;
}



void unmakeMove(int digit, char board[3][3]){
    int i = (digit-1)/3;
    int j = (digit-1)%3;
    board[i][j] = '0' + digit;
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
    std::vector<int> actions;
    for (int i; i<3; i++){
        for (int j; j<3; j++){
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
    for (int i; i<3; i++){
        for (int j; j<3; j++){
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


bool terminal(char board[3][3]){
    for (int i; i<3; i++){
        //row check
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]){
            return true;
            }
        //column check
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]){
            return true;
            }   
        }
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]){
            return true;
        }
    if (board[2][0] == board[1][1] &&
        board[1][1] == board[0][2]){
            return true;
        }
    return false;
    }


int utility(char board[3][3]){
    if      (terminal(board) == 'X'){return 1;}
    else if (terminal(board) == 'O'){return -1;}
    else    {return 0;}
}

bool checkDraw(char board[3][3]){
    int count{};
    for (int i{}; i<9; i++){
        for (int j{}; j<9; j++){
            if (board[i][j]=='X'||board[i][j]=='O'){
                count++;
            }
        }
    }
    if (count == 9){return true;}
    return false;
}


int miniMax(char board[3][3], bool isMaximizingPlayer = true){

    if (terminal(board)){
        return utility(board);
        }
    if (isMaximizingPlayer){
        int bestVal = -9999;
        std::vector<int> moves = actions(board);
        for (int i{}; i< moves.size(); i++){
            makeMove(moves[i], board);
            int value = miniMax(board, false);
            int bestVal = new_max( bestVal, value);
            unmakeMove(moves[i], board);
            }
        return bestVal;
    }
    else {
        int bestVal = 9999;
        std::vector<int> moves = actions(board);
        for (int i{}; i<moves.size(); i++){
            makeMove(moves[i], board);
            int value = miniMax(board, true);
            int bestVal = new_min( bestVal, value);
            unmakeMove(moves[i], board);
        }
        return bestVal;
    }
}


int findBestMove(char board[3][3]){
    int bestVal{9999};
    std::vector<int> moves = actions(board);
    int bestAct{};
    //for (i = actions.begin(); i != actions.end(); i++){
    for (int i{}; i < moves.size(); i++){
        int move = moves[i];
        makeMove(move, board);
        int score = miniMax(board);
        if (score < bestVal){
            bestVal = score;
            bestAct = move;
        }
        unmakeMove(move, board);
    }
    return bestAct;
}

int main(){
    bool running{true};
    while (running){
        drawBoard();
        makeMove(playerInput(), gamestate);
        if (terminal(gamestate) || checkDraw(gamestate)){
            break;
        }

        makeMove(findBestMove(gamestate), gamestate);
        if (terminal(gamestate)){
            running = false;
        }

    }
    drawBoard();

    return 0;
}
