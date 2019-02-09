#include <stdbool.h>

// Sudoku: provides a Sudoku puzzle ADT.

struct sudoku;

// the dimension of a Sudoku puzzle
extern const int DIM;

// requires: all sudoku parameters are valid sudoku structs.

//====================================================
// You need to implement the following four functions.

// fill_cell(s,row,col,num) tries to fill num in the cell (row,col).  
// It returns 0 if doing so does not violate any of the row, column, 
// and box constraints.  Otherwise, it returns a negative integer.
// requires: row and col are valid indices. 
//           num is an integer between 1 and 9.
// effects:  mutates *s
// time: O(1), as the parameters for the loops are constant
int fill_cell(struct sudoku *s, int row, int col, int num);

// choices_cell(s,row,col,choices,num_choices) determines all the 
// possible values for the cell (row,col) that do not violate
// any of the row, column, and box constraints.  It mutates choices 
// to contain the possible values and mutates *num_choices to be
// the number of possible values.
// requires: row and col are valid indices.
//           choices is a valid array with length DIM
// effects:  mutates choices and *num_choices
// time: O(1), as the parameters for the loops are constant
void choices_cell(const struct sudoku *s, 
                 int row, int col, 
                 int choices[], 
                 int *num_choices);

// solved_puzzle(s) returns true if s has a valid solution to the puzzle, 
// and returns false otherwise.
// Time: O(n), n is the lenght of s
// justification: runs n times where n is the length of s
bool solved_puzzle(const struct sudoku *s);

// get_last_empty(s, pos) returns the index of the previous empty cell 
//  in the array
// requires: pos >= 1, pos <= 80
// time: O(n), n is the length of s
// justification: at most it will search through all of s
int get_last_empty(struct sudoku *s, int pos);

// get_next_empty(s, pos) returns the index of the next empty cell 
//  in the array
// requires: pos >= 1, pos <= 80
// time: O(n), n is the length of s 
// justification: at most it will search through all of s
int get_next_empty(struct sudoku *s, int pos);

// puzzle_calc(s, num, pos) solves the sudoku puzzle by search and 
//  backtracking. Returns true if s has a valid solution to the puzzle
//  and returns false otherwise. 
// effects: mutates *s
// time: O(n), where n is the length of s
// justification: passes over each value 
bool puzzle_calc(struct sudoku *s, int num, int pos);

// solve(s) solves the Sudoku puzzle by search and backtracking.  
// It returns true if s has a valid solution to the puzzle, 
// and returns false otherwise.
// effects: mutates *s
// time: O(n), where n is the length of s
// justification: passes over each value 
bool solve(struct sudoku *s);


//====================================================
// We have implemented the following functions for you.

// read_sudoku() reads in a Sudoku puzzle from input and returns a 
// pointer to a new sudoku structure
// effects: reads from input
//			allocates memory (client must call sudoku_destroy)
// time: O(1), as the for loops run a constant times
struct sudoku *read_sudoku(void);

// sudoku_destroy(s) frees all memory for s
// effects: s is no longer valid
// time: O(1)
void sudoku_destroy(struct sudoku *s);

// print_sol(s) prints the current solution
// effects: produces output
// time: O(1), as the for loops run a constant times
void print_sol(const struct sudoku *s); 

// reset_sol(s) resets the solution to be the initial puzzle.
// effects: mutates *s
// time: O(1), as the for loops run a constant times
void reset_sol(struct sudoku *s);

// erase_cell(s, row, col) tries to set the value of the cell (row,col)
// to be zero.  It returns 0 if successful and a negative integer otherwise.
// requires: row and col are valid indices
// effects:  mutates *s
// time: O(1)
int erase_cell(struct sudoku *s, int row, int col);

// next_cell(s) finds a cell that has only one possible value.  If such
// a cell exists, it mutates *row and *col to be the row and column 
// indices of the cell.  If no such cell exists, it returns a negative
// integer.
// requires: row and col are valid pointers.
// effects:  mutates *row and *col
// time: O(1), as the for loops run a constant times
int next_cell(const struct sudoku *s, int *row, int *col);
