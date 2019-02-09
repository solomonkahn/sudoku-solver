#Made for uWaterloo CS136 'Elementary Algorithm Design and Data Abstraction'


#include "cs136.h"
#include "sudoku.h"
#include "array.h"

const int DIM = 9;

static const int EMPTY = 0;
static const char BLANK = '-';
static const int MIN = 1;
static const int MAX = 9;

static const int SUCCESS = 0;
static const int ERROR = -1;
static const int ERASE_EMPTY_CELL = -2;
static const int ERASE_FILLED_CELL = -3;
static const int ERROR_NEXT_CELL = -4;

  
struct sudoku {
  int puzzle[DIM * DIM];
  int sol[DIM * DIM];
};


int fill_cell(struct sudoku *s, int row, int col, int num) {
  assert(s);
  assert(row >= 0 && row <= 8);
  assert(col >= 0 && col <= 8);
  assert(num <= MAX && num >= MIN);
  
  int rowstart = row * DIM;
  int rowend = rowstart + DIM;
  int colstart = col;
  int colend = colstart + (8 * DIM);
  int boxstartcol = (col / 3) * 3;
  int boxstartrow = (row / 3) * 3;
  int boxstartind = (boxstartrow * DIM) + boxstartcol;
  int boxend = boxstartind + (2 * DIM);
  
  for (int i = rowstart; i < rowend; i++) {
    if (s->sol[i] == num) return ERROR;
  }
  for (int i = colstart; i <= colend; i += DIM) {
    if (s->sol[i] == num) return ERROR;
  }
  while (boxstartind <= boxend) {
    for (int i = boxstartind; i <= boxstartind + 2; i++) {
      if (s->sol[i] == num) return ERROR;
    }
    boxstartind += DIM;
  }
  s->sol[row * DIM + col] = num; 
  return SUCCESS;
} 


void choices_cell(const struct sudoku *s, int row, int col, 
                 int choices[], int *num_choices) {
  assert(s);
  assert(row >= 0 && row <= 8);
  assert(col >= 0 && col <= 8);
  
  int potential_choices[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int count = 0;
  
  int rowstart = row * DIM;
  int rowend = rowstart + DIM;
  int colstart = col;
  int colend = colstart + (8 * DIM);
  int boxstartcol = (col / 3) * 3;
  int boxstartrow = (row / 3) * 3;
  int boxstartind = (boxstartrow * DIM) + boxstartcol;
  int boxend = boxstartind + (2 * DIM);
   
  if (s->puzzle[row * DIM + col] > 0) {
    for (int i = 0; i <= DIM; i++) {
      choices[i] = 0;
    }
    *num_choices = 0;
  } else {
    for (int i = rowstart; i < rowend; i++) {
      if (s->sol[i] > 0) potential_choices[s->sol[i] - 1] = 0;
    }
    for (int i = colstart; i <= colend; i += DIM) {
      if (s->sol[i] > 0) potential_choices[s->sol[i] - 1] = 0;
    }
    while (boxstartind <= boxend) {
      for (int i = boxstartind; i <= boxstartind + 2; i++) {
        if (s->sol[i] > 0) potential_choices[s->sol[i] - 1] = 0;
      }
      boxstartind += DIM;
    }
   for (int i = 0; i < DIM; i++) {
     if (potential_choices[i] > 0) {
       choices[count] = potential_choices[i];
       ++count;
       *num_choices = count; 
     }
   }
  }
}

bool solved_puzzle(const struct sudoku *s) {
  assert(s);
  
  int board_sum = 405;
  int sum = 0;
  for (int i = 0; i < (DIM * DIM); i++) {
    sum += s->sol[i];
  }
  return sum == board_sum;    
}

int get_last_empty(struct sudoku *s, int pos) { 
  int last_empty = 0;
  while(1) {
    --pos;
    if (s->puzzle[pos] == EMPTY) {
      last_empty = pos;
      break;
    }
  }
  return last_empty;
  
}
int get_next_empty(struct sudoku *s, int pos) {
  while(1) {
    ++pos;
    if (pos < (DIM * DIM) && s->puzzle[pos] == EMPTY) return pos;
    if (pos == (DIM * DIM)) return 80; 
  }
}

bool puzzle_calc(struct sudoku *s, int num, int pos) {
  while(1) {
  int row = pos / DIM;
  int col = pos % DIM;
  if (solved_puzzle(s)) return true; 
  if (num <= MAX && fill_cell(s, row, col, num) == 0) {
    num = 1;
    pos = get_next_empty(s, pos);
    
  } else if (num < MAX) {
    ++num;
  } else {
    s->sol[pos] = 0;
    pos = get_last_empty(s, pos);
      if (s->sol[pos] < MAX) num = s->sol[pos] + 1; 
      else num = MAX;
  }
  }
}

bool solve(struct sudoku *s) {
  int first_empty = 0;
  int num = 1;
  for (int i = 0; i < (DIM * DIM); i++) {
    if (s->puzzle[i] == 0) {
      first_empty = i;
      break;
    }
  }
  reset_sol(s);
  return puzzle_calc(s, num, first_empty);
    
}


struct sudoku *read_sudoku(void) {
  struct sudoku *s = malloc(sizeof(struct sudoku));
  char c = 0;
  for (int row = 0; row < DIM; ++row) {
    for (int col = 0; col < DIM; ++col) {
        scanf(" %c", &c);
      if (c == BLANK) {
        s->puzzle[row * DIM + col] = 0;
      } else {
        s->puzzle[row * DIM + col] = c - '0';
      }
    }
  }

  // copy puzzle to solution
  reset_sol(s);

  return s;
}

void sudoku_destroy(struct sudoku *s) {
  assert(s);
  free(s);
}

void print_sol(const struct sudoku *s) {
  assert(s);

  printf("\n");
  for (int row = 0; row < DIM; ++row) {
    for (int col = 0; col < DIM; ++col) {
      int num = s->sol[row * DIM + col];
      if (num == EMPTY) {
        printf("%c", BLANK);
      } else {
        printf("%d", num);
      }  
    }
    printf("\n");
  }
  printf("\n");
}

void reset_sol(struct sudoku *s) {
  assert(s);

  for (int row = 0; row < DIM; ++row) {
    for (int col = 0; col < DIM; ++col) {
      s->sol[row * DIM + col] = s->puzzle[row * DIM + col];
    }
  }  
}

// cell_empty(board, row, col) returns true
// if cell (row,col) is empty on board.
// requires: board is a valid sudoku puzzle.
static bool cell_empty(const int board[], int row, int col) {
  assert(board);
  assert(0 <= row && row <= DIM - 1);
  assert(0 <= col && col <= DIM - 1);

  return board[row * DIM + col] == EMPTY;
}

int erase_cell(struct sudoku *s, int row, int col) {
  assert(s);
  assert(0 <= row && row <= DIM - 1);
  assert(0 <= col && col <= DIM - 1);

  if (cell_empty(s->sol, row, col)) {
    return ERASE_EMPTY_CELL;
  }
  if (!cell_empty(s->puzzle, row, col)) {
    return ERASE_FILLED_CELL;
  }
  s->sol[row * DIM + col] = EMPTY;
  return SUCCESS;
}


int next_cell(const struct sudoku *s, int *row, int *col) {
  assert(s);
  assert(row);
  assert(col);

  int choices[DIM];
  int num_choices = 0;
  for (int i = 0; i < DIM; ++i) {
    for (int j = 0; j < DIM; ++j) {
      if (!cell_empty(s->sol, i, j)) continue;
      choices_cell(s, i, j, choices, &num_choices);
      if (num_choices == 1) {
        *row = i;
        *col = j;
        return SUCCESS;
      }
    }
  }
  return ERROR_NEXT_CELL;
}
