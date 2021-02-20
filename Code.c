#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

const int TIE = 1;
const int MAX_BOARD_SIZE = 1024;

// This module implements function to determine outcome of a connect game

// clear() clears the console output and prints out two empty ines
void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
        printf("\n\n");
}

// print_board(a, width, height) prints current board of the game
void print_board(int a[], int width, int height) {
  int pos = 0;
  for (int i = 0; i < height; i++) {
      printf("%c[0;34m|\e[m", 0x1b);
      pos = i * width;
      for (int j = 0; j < width; j++) {
          if (a[pos + j]!= 0) {
              printf("%c[0;34m| \e[m", 0x1b);
              if (a[pos + j] == 1) {
                  printf("%c[0;31mX\e[m", 0x1b);
              } else if (a[pos + j] == 2){
                  printf("%c[0;32mO\e[m", 0x1b);
              } else {
                  printf(" ");
              }
              printf("%c[0;34m |\e[m", 0x1b);
          } else {
              printf("%c[0;34m|   |\e[m", 0x1b);
          }
          
          if(j == width - 1) {
             printf("%c[0;34m|\e[m", 0x1b); 
          }
      }
      printf("\n");
  }    
}


// check_horizontal(a[], width, height, col, row, length, x) Checks if the 
// player wins horizontally
bool check_horizontal(int a[], int width, int height, int col, int row, int length, int x) {
  int counter = 0;
  int curr_pos = col + (row * width);
  for(int i = col; i < width; i++) { // checking horizontally rightwards
    if(counter == length) {
      return true;
    } else if (a[curr_pos + (i - col)] == x) {
      ++counter;
      continue;
    } else {
      break;
    }
  }
  if (counter == length) {
    return true;
  }
  for(int i = 1; i <= col; ++i) { // checking horizontally leftwards
    if(counter == length) {
      return true;
    } else if (a[curr_pos - i] == x) {
      ++counter;
      continue;    
    } else {
      break;
    }
  }
  if (counter == length) {
    return true;
  }
  return false;
}

// check_vertical(a[], width, height, col, row, length, x) Checks if the 
// player wins vertically
bool check_vertical(int a[], int width, int height, int col, int row, int length, int x) {
  int counter = 0; 
  for (int i = row; i < height; i++) { // checking vertically upwards
    if (counter == length) {
      return true;
    } else if (a[(i * width) + col] == x) {
      ++counter;
      continue;
    } else {
      break;
    }     
  }
  if (counter == length) {
    return true;
  }
  for (int i = row-1; i >= 0; i--) { // checking vertically downwards
    if (counter == length) {
      return true;
    } else if (a[(i * width) + col] == x) {
      ++counter;
      continue;
    } else {
      break;
    }     
  }
  if (counter == length) {
    return true;
  }
  return false;
}

// check_diagonally(a[], width, height, col, row, length, x) Checks if the 
// player wins diagonally
bool check_diagonally(int a[], int width, int height, int col, int row, int length, int x) {
  int counter = 0;
  for(int i = 0; i < (width - col); i++) {  //checking downwards along left diagonal
    if(counter == length) {
      return true;
    } else if (row - i < 0){
      break; 
    } else if (a[(col + i) + ((row - i) * width)] == x) {
      ++counter;
      continue;
    } else {
      break;
    }
  }
  for(int i = 1; i <= col ; i++) { //checking upwards along left diagonal
    if(counter == length) {
      return true;
    } else if (row + i >= height){
      break;
    } else if (a[(col - i) + ((row + i) * width)] == x) {
      ++counter;
      continue;
    } else {
      break;
    }
  }
  if (counter == length) {
    return true;
  }
  counter = 0;
  for(int i = 0; i <= col; i++) { //checking downwards along right diagonal
    if(counter == length) {
      return true;
    } else if (row - i < 0){
      break;
    } else if (a[(col - i) + ((row - i) * width)] == x) {
      ++counter;
      continue;
    } else {
      break;
    }
  }
  for(int i = 1; i < (width - col); i++) { //checking upwards along right diagonal
    if(counter == length) {
      return true;
    } else if (row + i >= height){
      break;
    } else if (a[(col + i) + ((row + i) * width)] == x) {
      ++counter;
      continue;
    } else {
      break;
    }
  }
  if (counter == length) {
    return true;
  }
  return false;
}

int connect_analysis(int width, int height, int length) {
  assert(width > 2);
  assert(height > 2);
  assert(width * height < MAX_BOARD_SIZE);
  assert(length > 2);
  if (width >= height) {
    assert(length <= width);
  } else {
    assert(length <= height);
  }
  int board[1024] = {0}; 
  int size = width * height;
  int player = 0;
  int row = 0;
  int col = 0;
  int pos = 0;
  while (pos < size) {
    if (pos % 2 == 0) {
      player = 1;
    } else {
      player = 2;
    }
    printf("Select Column, Player %d: ", player);
    scanf("%d", &col);
    --col;
    if (col < 0 || col >= width) {
        printf("Invalid Input. Try again\n");
        continue;
    } 
    if (board[col] != 0) {
        printf("Invalid Input. Try again\n");
        continue;
    }
    for (int i = height-1 ; 0 <= i; i--) {
      clear();
      if(board[col + (i * width)] == 0) {
        board[col + (i * width)] = player;
        row = i;
        break;
      } else if (i == 0) {
        return INVALID_GAME;
      }  
    }
    if (check_horizontal(board, width, height, col, row, length, player)) {
      print_board(board, width, height);
      if (player == 1) {
        return ++pos;
      } else {
        return (-1 * ++pos);
      }
    } else if (check_vertical(board, width, height, col, row, length, player)) {
      print_board(board, width, height);
      if (player == 1) {
        return ++pos;
      } else {
        return (-1 * ++pos);
      }
    } else if (check_diagonally(board, width, height, col, row, 
                                length, player)) {
      print_board(board, width, height);
      if (player == 1) {
        return ++pos;
      } else {
        return (-1 * ++pos);
      }
    } else {
      ++pos;
      print_board(board, width, height);
      printf("\n");
      continue;
    }
  }
  return TIE;
}

int main (void) {
  int width = 0;
  int height = 0;
  int length = 0;
  printf("Enter Number Of Columns: ");
  scanf("%d", &width);
  printf("Enter Number Of Rows: ");
  scanf("%d", &height);
  printf("Enter Length: ");
  scanf("%d", &length);
  int flag = connect_analysis(width, height, length);
  if (flag < 0) {
    printf("%c[0;34mCongrats Player 2!\n", 0x1b);
  } else if (flag == 1) {
    printf("It's a Tie");
  } else if (flag > 0) {
    printf("%c[0;31mCongrats Player 1!\n", 0x1b);
  }
}
