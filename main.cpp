#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* change this to change the size of the board */
#define size (4)

using namespace std;

static int board [size][size];    // game board (4x4)
static int score;                 // score of the player

// method list
void addTile();
bool canMoveUp();
bool canMoveDown();
bool canMoveLeft();
bool canMoveRight();
void clearBoard();
bool isGameOver();
bool isGameWon();
void moveAllUp();
void moveAllDown();
void moveAllLeft();
void moveAllRight();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();
void printBoard();
void printCommands();
void updateScore(int add);
// end of method list

void addTile(){
    
    // counts the number of empty spots on the board
    int counter = 0;
    
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] == 0){
                counter++;
            }
        }
    }
    
    // gets a random blank spot on the board
    int RandIndex = rand() % counter;   // position for new tile
    
    // 90% chance tile is a 2, 10% change tile is a 4
    int magnitude = rand() % 100;
    
    // counts down until it finds the spot to put the new tile
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] == 0){
                if(RandIndex == 0){
                    if(magnitude > 89){
                        board[outer][inner] = 4;
                    }
                    else{
                        board[outer][inner] = 2;
                    }
                }
                RandIndex--;
            }
        }
    }
}

bool canMoveUp(){
    for(int outer = 0; outer < size - 1; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer + 1][inner] != 0 && board[outer][inner] == 0){
                return true;
            }
            if(board[outer + 1][inner] == board[outer][inner] && board[outer][inner] != 0){
                return true;
            }
        }
    }
    return false;
}

bool canMoveDown(){
    for(int outer = 0; outer < size - 1; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer + 1][inner] == 0 && board[outer][inner] != 0){
                return true;
            }
            if(board[outer + 1][inner] == board[outer][inner] && board[outer][inner] != 0){
                return true;
            }
        }
    }
    return false;
}

bool canMoveLeft(){
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size - 1; inner++){
            if(board[outer][inner + 1] != 0 && board[outer][inner] == 0){
                return true;
            }
            if(board[outer][inner + 1] == board[outer][inner] && board[outer][inner] != 0){
                return true;
            }
        }
    }
    return false;
}

bool canMoveRight(){
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size - 1; inner++){
            if(board[outer][inner + 1] == 0 && board[outer][inner] != 0){
                return true;
            }
            if(board[outer][inner + 1] == board[outer][inner] && board[outer][inner] != 0){
                return true;
            }
        }
    }
    return false;
}

void clearBoard(){
    score = 0;
    // fill board up with zeroes
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size; inner++){
            board[outer][inner] = 0;
        }
    }
}

bool isGameOver(){
    // checking for empty spots
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] == 0){
                return false;
            }
        }
    }
    
    // checking for vertical duplicates
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size - 1; inner++){
            if(board[outer][inner] == board[outer][inner + 1]){
                return false;
            }
        }
    }

    // checking for horizontal duplicates
    for(int outer = 0; outer < size - 1; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] == board[outer + 1][inner]){
                return false;
            }
        }
    }
    
    return true;
}

bool isGameWon(){
    // checks for any 2048 tiles
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] == 2048){
                return true;
            }
        }
    }
    return false;
}

void moveAllUp(){
    for(int outer = size - 1; outer > 0; outer--){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] != 0 && board[outer - 1][inner] == 0){
                board[outer - 1][inner] = board[outer][inner];
                board[outer][inner] = 0;
            }
        }
    }
}

void moveAllDown(){
    for(int outer = 0; outer < size - 1; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] != 0 && board[outer + 1][inner] == 0){
                board[outer + 1][inner] = board[outer][inner];
                board[outer][inner] = 0;
            }
        }
    }
}

void moveAllLeft(){
    for(int outer = 0; outer < size; outer++){
        for(int inner = size - 1; inner > 0; inner--){
            if(board[outer][inner] != 0 && board[outer][inner - 1] == 0){
                board[outer][inner - 1] = board[outer][inner];
                board[outer][inner] = 0;
            }
        }
    }
}

void moveAllRight(){
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size - 1; inner++){
            if(board[outer][inner] != 0 && board[outer][inner + 1] == 0){
                board[outer][inner + 1] = board[outer][inner];
                board[outer][inner] = 0;
            }
        }
    }
}

void moveUp(){
    // used to store the duplicate tile
    int temp;
    
    // pushes everything all the way
    for(int i = 0; i < size - 1; i++){
        moveAllUp();
    }
    
    // checks for matching adjacent tiles and adds them up
    for(int outer = 0; outer < size - 1; outer++){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] == board[outer + 1][inner] && board[outer][inner] != 0){
                temp = board[outer][inner];
                board[outer][inner] = 2*temp;
                board[outer + 1][inner] = 0;
                updateScore(temp);
            }
        }
    }
    
    // pushes everything all the way again
    for(int i = 0; i < size - 1; i++){
        moveAllUp();
    }
}

void moveDown(){
    // used to store the duplicate tile
    int temp;
    
    // pushes everything all the way
    for(int i = 0; i < size - 1; i++){
        moveAllDown();
    }
    
    // checks for matching adjacent tiles and adds them up
    for(int outer = size - 1; outer > 0; outer--){
        for(int inner = 0; inner < size; inner++){
            if(board[outer][inner] == board[outer - 1][inner] && board[outer][inner] != 0){
                temp = board[outer][inner];
                board[outer][inner] = 2*temp;
                board[outer - 1][inner] = 0;
                updateScore(temp);
            }
        }
    }
    
    // pushes everything all the way again
    for(int i = 0; i < size - 1; i++){
        moveAllDown();
    }
}

void moveLeft(){
    // stores the value of the matching tiles
    int temp;
    
    // pushes everything all the way
    for(int i = 0; i < size - 1; i++){
        moveAllLeft();
    }
    
    // checks for matching adjacent tiles and adds them up
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size - 1; inner++){
            if(board[outer][inner] == board[outer][inner + 1] && board[outer][inner] != 0){
                temp = board[outer][inner];
                board[outer][inner] = 2*temp;
                board[outer][inner + 1] = 0;
                updateScore(temp);
            }
        }
    }
    
    // pushes everything all the way again
    for(int i = 0; i < size - 1; i++){
        moveAllLeft();
    }
}

void moveRight(){
    // stores the value of the matching tiles
    int temp;
    
    // pushes everything all the way
    for(int i = 0; i < size - 1; i++){
        moveAllRight();
    }
    
    // checks for matching adjacent tiles and adds them up
    for(int outer = 0; outer < size; outer++){
        for(int inner = size - 1; inner > 0; inner--){
            if(board[outer][inner] == board[outer][inner - 1] && board[outer][inner] != 0){
                temp = board[outer][inner];
                board[outer][inner] = 2*temp;
                board[outer][inner - 1] = 0;
                updateScore(temp);
            }
        }
    }
    
    // pushes everything all the way again
    for(int i = 0; i < size - 1; i++){
        moveAllRight();
    }
}

void printCommands(){
    // prints commands
    cout << "These are the commands: " << endl;
    cout << "WASD to move, (n)ew game and (q)uit" << endl;
}

void printBoard(){
    cout << "Score: " << score << endl;
    cout << "--------" << endl;
    
    // prints each element of the board
    for(int outer = 0; outer < size; outer++){
        for(int inner = 0; inner < size; inner++){
            cout << board[outer][inner] << " ";
        }
        cout << endl;
    }
    
    cout << "--------" << endl;
}

void updateScore(int add){
    score += add;   // add to the score
}

int main(){
    srand(time(NULL));  // initialize random seed
    
    cout << "Welcome to 2048!" << endl;
    
    clearBoard();   // in case the board has leftover elements (shouldn't)
    printCommands();    // display commands to user
    
    // add two starting tiles
    addTile();
    addTile();
    
    // print initial table to user
    printBoard();
    
    // the actual gameplay
    while(1){
        char buffer;    // used to hold the command key
        
        cin >> buffer;
        
        switch(buffer){
            case 'n' :
                cout << "new game" << endl;

                clearBoard();   // also clears the score
                addTile();
                addTile();
                printBoard();
                
                break;
            case 'a' :
                cout << "moving left" << endl;
                
                if(canMoveLeft()){
                    moveLeft();
                    addTile();
                    printBoard();
                }
                break;
            case 'd' :
                cout << "moving right" << endl;
                
                if(canMoveRight()){
                    moveRight();
                    addTile();
                    printBoard();
                }
                break;
            case 'w' :
                cout << "moving up" << endl;
                
                if(canMoveUp()){
                    moveUp();
                    addTile();
                    printBoard();
                }
                break;
            case 's' :
                cout << "moving down" << endl;
                
                if(canMoveDown()){
                    moveDown();
                    addTile();
                    printBoard();
                }
                break;
            case 'q' :
                cout << "quitting game" << endl;
                return 0;
            default :
                cout << "invalid command!" << endl;
                printCommands();
            break;
        }
            
        // checks if game is over at the end of each move
        if(isGameOver()){
            cout << "You lost! Get good." << endl;
            break;
        }
        if(isGameWon()){
            cout << "You won!" << endl;
            break;
        }
    }
}