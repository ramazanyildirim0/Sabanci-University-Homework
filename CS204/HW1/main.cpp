/*
    THIS CODE WAS WRITTEN BY RAMAZAN YILDIRIM 32501
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/* PRINT THE MATRIX */
void print_matrix(vector<vector<char>> matrix){
    for(int x=0;x<matrix.size();x++){
        for(int y=0; y<matrix[x].size();y++){
            cout << matrix[x][y];
        }
        cout << endl;
    }
}

/* CHECK POSSIBLE MOVES */
int game_check(vector<vector<char>> matrix){
    int answer = 0;

    for(int r=0;r<matrix.size();r++){
        for(int c=0;c<matrix[r].size();c++){
            if(matrix[r][c] == '-'){

            }else if(matrix[r][c] == 'r'){
                if(c < matrix[r].size()){
                    if(matrix[r][c+1] == '-'){
                        return 1;
                    }
                }else if(c + 1 == matrix[r].size()){
                    return 1;
                }
                answer = -1;
            }else if(matrix[r][c] == 'l'){
                if(c>=1){
                    if(matrix[r][c-1] == '-'){
                        return 1;
                    }
                }else if (c==0){
                    return 1;
                }
                answer = -1;
            }else if(matrix[r][c] == 'u'){
                if(r>=1) {
                    if (matrix[r - 1][c] == '-') {
                        return 1;
                    }
                }else if(r == 0){
                    return 1;
                }
                answer = -1;
            }else if(matrix[r][c] == 'd'){
                if(r < matrix.size()-1){
                    if (matrix[r + 1][c] == '-') {
                        return 1;
                    }
                }else if(r == 0 && matrix.size() == 1){
                    return 1;
                }else if (r == matrix.size() -1){
                    return 1;
                }
                answer = -1;
            }
        }
    }
    return answer;
}

/* EDIT MATRIX */
void edit_matrix(vector<vector<char>> & matrix,vector<char> & each_row, int rowId, int colId, char newChar){
    each_row.clear();

    for (int i = 0; i < colId; i++) {
        each_row.push_back(matrix[rowId][i]);
    }

    each_row.push_back(newChar);

    for(int i=colId+1; i<matrix[0].size();i++){
        each_row.push_back(matrix[rowId][i]);
    }

    matrix.erase(matrix.begin() + rowId);
    matrix.insert(matrix.begin() + rowId,each_row);
}

/* PRINT MOVE OR NOT */
void print_result(bool move, int rowId, int colId){

    if(move){
        cout << "Tile at (" << rowId << "," << colId << ") has been moved." << endl;
    }else{
        cout << "No tiles have been moved." << endl;
    }
}
int main() {

    /* FORCE USER TO INPUT VALID FILE NAME */
    string file_name;
    ifstream file_str;

    bool is_open=false, is_tried=false;

    do {
        if (is_tried){
            cout << "Could not open the file. Please enter a valid file name:" << endl;
        }else{
            cout << "Please enter the file name:" << endl;
        }

        cin >> file_name;
        file_str.open(file_name);
        if(file_str.is_open()){
            is_open = true;
        }
        is_tried=true;

    }while(!is_open);

    /* CREATE MATRIX AND PUSHBACK DATA INTO IT */
    bool is_empty = true, checked = false;
    string line;
    vector<vector<char>> matrix;
    vector<char> each_row;
    int prevLineSize ,currentLineSize = 0;

    while(getline(file_str,line)){

        /* CHECK FOR CONSISTENCY OF THE NUMBER OF CHARACTERS IN EACH ROW */
        prevLineSize = currentLineSize;
        currentLineSize = line.length();
        if (prevLineSize != currentLineSize && checked){
            cout << "Erroneous file content. Program terminates.";
            return 0;
        }

        for(int i = 0 ; i < line.length();i++){
            if(is_empty && line[i] != '-'){ // CHECK MATRIX IS EMPTY OR NOT
                is_empty = false;
            }

            if(line[i] == 'r' || line[i] == 'l' || line[i] == 'u' || line[i] == 'd'|| line[i] == '-'){
                each_row.push_back(line[i]);
            }else{
                cout << "Erroneous file content. Program terminates.";
                return 0;
            }
        }
        matrix.push_back(each_row);
        each_row.clear();
        checked = true;

    }

    /* TERMINATE THE PROGRAM IF MATRIX IS EMPTY */
    if (is_empty){
        cout << "The matrix file contains:" << endl;
        print_matrix(matrix);
        cout << "The matrix is empty.";
        return 0;
    }

    /* PRINT THE MATRIX */
    cout << "The matrix file contains:" << endl;
    print_matrix(matrix);

    /* GET COORDINATE FROM USER AND MAKE MOVES */
    while (game_check(matrix) == 1){
        int xCoordinate, yCoordinate;
        cout << "Please enter the row and column of the tile that you want to move:" << endl;
        cin >> xCoordinate >> yCoordinate;

        if (xCoordinate > matrix.size() - 1 || yCoordinate > matrix[0].size() - 1){
            cout << "Invalid row or column index." << endl;
        }else {
            if (matrix[xCoordinate][yCoordinate] == '-') {
                cout << "No tiles have been moved." << endl;
            }
            if (matrix[xCoordinate][yCoordinate] == 'r') {

                if(yCoordinate == matrix[0].size()-1){ // R IS ON THE RIGHT
                    edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                    print_result(true, xCoordinate, yCoordinate);
                }else{

                    /* CHECK THE RIGHT SIDE OF THE COORDINATES */
                    int maxRight = matrix[xCoordinate].size();
                    for (int i = yCoordinate + 1; i < matrix[xCoordinate].size(); i++) {
                        if (matrix[xCoordinate][i] == 'r' || matrix[xCoordinate][i] == 'l' ||
                            matrix[xCoordinate][i] == 'u' || matrix[xCoordinate][i] == 'd') {
                            maxRight = i;
                            i = matrix[xCoordinate].size();
                        }
                    }

                    if (maxRight == matrix[xCoordinate].size()){
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        print_result(true, xCoordinate, yCoordinate);
                    }else if(maxRight != yCoordinate +1){
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        edit_matrix(matrix,each_row,xCoordinate,maxRight -1, 'r');
                        print_result(true, xCoordinate, yCoordinate);
                    }else{
                        print_result(false, xCoordinate, yCoordinate);
                    }
                }
            }

            if (matrix[xCoordinate][yCoordinate] == 'l') {
                if(yCoordinate == 0 ){ // L IS ON THE LEFT
                    edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                    print_result(true, xCoordinate, yCoordinate);
                }else{
                    /* CHECK THE LEFT SIDE OF THE COORDINATES */
                    int maxLeft = -1;
                    for (int i = yCoordinate - 1 ; 0<= i; i--) {
                        if (matrix[xCoordinate][i] == 'r' || matrix[xCoordinate][i] == 'l' ||
                            matrix[xCoordinate][i] == 'u' || matrix[xCoordinate][i] == 'd') {
                            maxLeft = i;
                            i = -1;
                        }
                    }

                    if(maxLeft == -1){
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        print_result(true, xCoordinate, yCoordinate);
                    }else if(maxLeft + 1 != yCoordinate){
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        edit_matrix(matrix,each_row,xCoordinate,maxLeft +1, 'l');
                        print_result(true, xCoordinate, yCoordinate);
                    }else{
                        print_result(false, xCoordinate, yCoordinate);
                    }
                }
            }

            if (matrix[xCoordinate][yCoordinate] == 'u') {

                if(xCoordinate == 0){ // U IS ON THE TOP
                    edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                    print_result(true, xCoordinate, yCoordinate);
                }else{

                    /* CHECK THE UP SIDE OF THE COORDINATES */
                    int maxUp = -1;
                    for (int i = xCoordinate - 1; 0 <= i; i--) {
                        if (matrix[i][yCoordinate] == 'r' || matrix[i][yCoordinate] == 'l' ||
                            matrix[i][yCoordinate] == 'u' || matrix[i][yCoordinate] == 'd') {
                            maxUp = i;
                            i = -1;
                        }
                    }

                    if(maxUp == -1){ // IF THERE ARE ONLY '-' ON THE UP
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        print_result(true, xCoordinate, yCoordinate);
                    }else if(maxUp + 1 != xCoordinate){
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        edit_matrix(matrix,each_row,maxUp + 1,yCoordinate, 'u');
                        print_result(true, xCoordinate, yCoordinate);
                    }else{
                        print_result(false, xCoordinate, yCoordinate);
                    }
                }
            }

            if (matrix[xCoordinate][yCoordinate] == 'd') {
                if(xCoordinate == matrix.size()){ // D IS ON THE BOTTOM
                    edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                    print_result(true, xCoordinate, yCoordinate);
                }else{
                    /* CHECK THE DOWN SIDE OF THE COORDINATES */
                    int maxDown = matrix.size();
                    for (int i = xCoordinate + 1; i <= matrix.size() - 1 ; i++) {
                        if (matrix[i][yCoordinate] == 'r' || matrix[i][yCoordinate] == 'l' ||
                            matrix[i][yCoordinate] == 'u' || matrix[i][yCoordinate] == 'd') {
                            maxDown = i;
                            i = matrix.size();
                        }
                    }

                    if(maxDown == matrix.size()){
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        print_result(true, xCoordinate, yCoordinate);
                    }else if(maxDown - 1 !=xCoordinate ){
                        edit_matrix(matrix,each_row,xCoordinate,yCoordinate, '-');
                        edit_matrix(matrix,each_row,maxDown - 1,yCoordinate, 'd');
                        print_result(true, xCoordinate, yCoordinate);
                    }else{
                        print_result(false, xCoordinate, yCoordinate);
                    }
                }
            }

            print_matrix(matrix);
        }
    }

    /* CHECK IF GAME ENDED */
    if(game_check(matrix) == -1){
        cout << "No more moves are possible.";
    }else if(game_check(matrix) == 0){
        cout << "The matrix is empty.";
    }

    return 0;
}