//***************************************************
// Filename: othello.c
//
// Author(s): Jake Irons
//***************************************************

#include "othello.h"

// Constructs and returns a string representation of the board
char *toString(int size, char board[][size])
{
	char *str = (char *) calloc(3 * (size+1) * (size+1), sizeof(char));
	char *ptr = str;

	for (int i = 0; i < size; i++) {
		ptr += sprintf(ptr,(i == 0 ? "%3d" : "%2d"),i+1);
	}
	sprintf(ptr,"\n");
	ptr++;

	for (int i = 0; i < size; i++) {
		sprintf(ptr,"%1d",i+1);
		ptr++;
		for (int j = 0; j < size; j++) {
			sprintf(ptr,"%2c",board[i][j]);
			ptr += 2;
		}
		sprintf(ptr,"\n");
		ptr++;
	}

	return str;
}

// Initializes the board with start configuration of discs (see project specs)
void initializeBoard(int size, char board[][size])
{
	// COMPLETE THIS FUNCTION
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = '-';
		}
	}
	board[size / 2 - 1][size / 2 - 1] = 'B';
	board[size / 2][size / 2] = 'B';
	board[size / 2 - 1][size / 2] = 'W';
	board[size / 2][size / 2 - 1] = 'W';
	
}

// Returns true if moving the disc to location row,col is valid; false otherwise
bool isValidMove(int size, char board[][size], int row, int col, char disc)
{
	char otherDisc;
	if(disc == 'B'){
		otherDisc = 'W';
	}
	else{
		otherDisc = 'B';
	}
	if(board[row][col] == '-'){
		int newRow;
		int newCol;
		for(int surrRow = -1; surrRow < 2; surrRow++){
			for(int surrCol = -1; surrCol < 2; surrCol++){
				if(surrRow != 0 || surrCol != 0){
					newRow = row + surrRow;
					newCol = col + surrCol;
					if(board[newRow][newCol] == otherDisc && (newRow >=0 && newRow < size) && (newCol >= 0 && newCol < size)){
						while(board[newRow][newCol] == otherDisc && (newRow >=0 && newRow < size) && (newCol >= 0 && newCol < size)) {
	    						newRow = newRow + surrRow;
							newCol = newCol + surrCol;
							if(board[newRow][newCol] == disc && (newRow >=0 && newRow < size) && (newCol >= 0 && newCol < size)){
								return true;
							}
						}
					} 
				}
			}
		}
	}
	return false;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

// Places the disc at location row,col and flips the opponent discs as needed
void placeDiscAt(int size, char board[][size], int row, int col, char disc)
{
	if (!isValidMove(size,board,row,col,disc)) {
		return;
	}
	else{
		board[row][col] = disc;
		char otherDisc;
		if(disc == 'B'){
			otherDisc = 'W';
		}
		else{
			otherDisc = 'B';
		}
		int newRow;
		int newCol;
		for(int surrRow = -1; surrRow < 2; surrRow++){
			for(int surrCol = -1; surrCol < 2; surrCol++){
				if(surrRow != 0 || surrCol != 0){
					newRow = row + surrRow;
					newCol = col + surrCol;
					if(board[newRow][newCol] == otherDisc && (newRow >=0 && newRow < size) && (newCol >= 0 && newCol < size)){
						int squareCount = 1;
						while(board[newRow][newCol] == otherDisc && (newRow >=0 && newRow < size) && (newCol >= 0 && newCol < size)) {
							++squareCount;
	    						newRow = newRow + surrRow;
							newCol = newCol + surrCol;
							if(board[newRow][newCol] == disc && (newRow >=0 && newRow < size) && (newCol >= 0 && newCol < size)){
								for(int i = squareCount - 1; i > 0; i--){
									board[newRow - (surrRow * i)][newCol - (surrCol * i)] = disc;
								}
								break;
							}
						}
					} 
				}
			}
		}
	}

	// COMPLETE REST OF THIS FUNCTION
}

// Returns true if a valid move for disc is available; false otherwise
bool isValidMoveAvailable(int size, char board[][size], char disc)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if(isValidMove(size, board, i, j, disc)){
				return true;
			}
		}
	}
	return false;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

// Returns true if the board is fully occupied with discs; false otherwise
bool isBoardFull(int size, char board[][size])
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if(board[i][j] == '-'){
				return false;
			}
		}
	}
	return true;	// REPLACE THIS WITH YOUR IMPLEMENTATION	
}

// Returns true if either the board is full or a valid move is not available for either disc; false otherwise
bool isGameOver(int size, char board[][size])
{
	if(isBoardFull(size, board)){
		return true;
	}
	else if(!isValidMoveAvailable(size, board, 'B') && !isValidMoveAvailable(size, board, 'W')){
		return true;
	}
	return false;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

// If there is a winner, it returns the disc (BLACK or WHITE) associated with the winner.
// In case of a tie, it returns TIE. When called before the game is over, it returns 0.
char checkWinner(int size, char board[][size])
{
	int blackCount; 
	int whiteCount;
	if (!isGameOver(size,board)) {
		return 0;
	}
	else{
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if(board[i][j] == 'B'){
					++blackCount;
				}
				else if(board[i][j] == 'W'){
					++whiteCount;
				}
			}
		}
	}
	
	if(whiteCount > blackCount){
		return 'W';
	}
	else if(blackCount > whiteCount){
		return 'B';
	}
	return 'T';	// REPLACE THIS WITH YOUR IMPLEMENTATION
}
