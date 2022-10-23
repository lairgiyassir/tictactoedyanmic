#include <iostream>
using namespace std;

void show(int);
void insert_symbol(int, char**);
bool check_column(int, char**, int, int);
bool check_row(int, char**, int, int);
bool check_diag(int, char**, int, int);
bool check_anti_diag(int, char**, int, int);
bool check_win(int, char**, int, int);
bool check_trial(int, char**, int, int);
bool check_size_N(int);
bool check_symbol(char);
bool check_no_win(int, char**, int , int);


int main(){
    int N, row, column;
    char symbol1;
    int player = 0;

    cout << "Enter the size of the board  :";
    cin >> N;

    while (!check_size_N(N)) {
        cout << "Enter the size of the board  :";
        cin >> N;
    }

    /* create a 2D table board */
    char **board = new char*[N];
    for (int i=0; i<N; i++){
        board[i] = new char[N];
    }

    /* Initialize the the board with "v" character */
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            board[i][j] = 'v';
    }
    }
    
    /* Show the empty board */
    show(N);


    cout << "PLAYER --" << player << " -- Choose the symbol X or O  :";
    cin >> symbol1;

    while (!check_symbol(symbol1)) {
        cout << "PLAYER --" << player << " -- Choose the symbol X or O  :";
        cin >> symbol1;
    }

    char symbol2 = (symbol1 == 'X')? 'O' : 'X';

    cout << "PLAYER -- "<< player <<" -- Insert the symbol in the row  :";
    cin >> row;

    cout << "PLAYER -- "<< player << " -- Insert the symbol in the column  :";
    cin >> column;

    while (!(check_trial(N, board, row, column))){
        cout << "PLAYER -- "<< player <<" -- Insert the symbol in the row  :";
        cin >> row;

        cout << "PLAYER -- "<< player << " -- Insert the symbol in the column  :";
        cin >> column;
    }

    board[row][column] = symbol1;

    insert_symbol(N, board);

    bool win = (check_win(N, board, row, column));
    

    
    while ((!win) && (!check_no_win(N, board, row, column))) {
        player = (player == 0) ? 1 : 0;
        char symbol = (player == 0) ? symbol1 : symbol2;
        bool trial = false;

        while (!trial) {
            cout << "PLAYER -- "<< player <<" -- Insert the symbol in the row  :";
            cin >> row;

            cout << "PLAYER -- "<< player << " -- Insert the symbol in the column  :";
            cin >> column;

            trial = (check_trial(N, board, row, column));
        }
        
        
        board[row][column] = symbol;

        insert_symbol(N, board);

        
        win = (check_win(N, board, row, column));
        
    }
    
    cout << endl;
    if (check_no_win(N, board, row, column)) {
            cout << "NO WIN";
        }
    else {cout << " * WINNER * IS PLAYER " << player ;}
    return 0;
}


void show(int N){
    /* Show the empty board */

    for (int j = 0; j<N; j++){

        cout << j << " "; 
        for (int i =0; i<N; i++){
        cout << "|____|";       
    }
    cout << endl;
    
}
}

void insert_symbol(int N, char**board){
    /* Show the state of the board using the table 2D board */
    for (int j = 0; j<N; j++){

        cout << j << " "; 
        for (int i =0; i<N; i++){
            
            if (board[j][i]=='v'){
                cout << "|____|";
            }
            else{
                cout << "|__" << board[j][i] << "_|" ;
                 
            }
                  
    }
    cout << endl;
    
}
}

bool check_column(int N, char** board, int row, int column)
{
    /* Verify if there is a continuity of X or O in the column of index "column" */
    int suite = true;
    char symbol = board[row][column];

    for (int i = 0; i < N; i++){
    suite = suite && (board[i][column]==symbol);
    }

    return suite;
}

bool check_row(int N, char** board, int row, int column)
{
    /* Verify if there is a continuity of X or O in the row of index "row" */
    int suite = true;
    char symbol = board[row][column];

    for (int i = 0; i < N; i++){
    suite = suite && (board[row][i] == symbol);
    }

    return suite;
}

bool check_diag(int N, char ** board, int row, int column) {
    /* Verify if there is a continuity of X or O in the diagonale */
    int suite = true;
    char symbol = board[row][column];

    for (int i = 0; i < N; i++){
    suite = suite && (board[i][i]==symbol);
    }

    return suite;
}

bool check_anti_diag(int N, char ** board, int row, int column) {
    /* Verify if there is a continuity of X or O in the anti-diagonale */
    int suite = true;
    char symbol = board[row][column];

    for (int i = 0; i < N; i++){
    suite = suite && (board[i][N-1-i]==symbol);
    }

    return suite;
}

bool check_win(int N, char ** board, int row, int column){
    /* Check if there is a winner */
    return (check_column(N, board, row, column)) || (check_row(N, board, row, column)) || (check_diag(N, board, row, column) || (check_anti_diag(N, board, row, column)));
}


bool check_trial(int N, char** board, int row, int column) {
    /* Verify if the user has chosen a valid position in the board */
    if ((row >= 0) && (column >= 0) && (row <= N-1) && (column <= N-1) && (board[row][column] == 'v')){
        return true;
    }
    else{
        return false;
    }
}

bool check_size_N(int N){
    /* Verify the input size N is valid */
    if (N > 0) {
        return true;
    }
    else {
        return false;
    }
}

bool check_symbol(char symbol){
    /* Verify if the symbol is valid */
    if ((symbol != 'X') && (symbol != 'O')) {
        return false;
    }

    else {
        return true;
    }
}

bool check_no_win(int N, char ** board, int row, int column){
    /* Verify if there is no winner */
    for (int j = 0; j<N; j++){

        for (int i =0; i<N; i++){
            if (board[j][i] == 'v'){
                return false;
            }
        }
}
    
    if (!(check_win(N, board, row, column))) {
        return true;
    }
}