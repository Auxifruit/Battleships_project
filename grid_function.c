#include "game_function.h"

/*! @brief Function to initialize a game */
Grid* init_grid() {
    Grid* grid = NULL;                                  // Locals

    grid = malloc(sizeof(Grid));
    if(grid == NULL) {                                  // Allocation check 
        printf("Allocation error (init_grid).\n");
        exit(ALLOCATION_ERROR);
    }

    grid->size = S_GRID;

    grid->matrix = malloc(sizeof(int*) * S_GRID);       // Allocate memory for the "rows" 
    if(grid->matrix == NULL) {                          // Allocation check 
        printf("Allocation error (init_grid).\n");
        exit(ALLOCATION_ERROR);
    }

    for(int i = 0; i < S_GRID; i++) {
        grid->matrix[i] = malloc(sizeof(int) * S_GRID); // Allocate memory for the "Columns" 
        if(grid->matrix[i] == NULL) {                   // Allocation check 
            printf("Allocation error (init_grid).\n");
            exit(ALLOCATION_ERROR);
        }
    }

    for(int i = 0; i < S_GRID; i++) {
        for(int j = 0; j < S_GRID; j++) {
            grid->matrix[i][j] = WATER;                 // Default value for each cell 
        }
    }

    return grid;
}

/*! @brief Function to display a grid */
void display_grid(Grid* grid, int person) {
    if(grid == NULL || (person != 1 && person != 0)) {                                  // Allocation check 
        printf("Argument error (display_grid).\n");
        exit(ARGUMENT_ERROR);
    }

    printf("   ");
    for(int n_col = 0; n_col < S_GRID; n_col++) {       // Print the column number 
        printf("%d ", n_col + 1);
    }
    printf("\n");

    for(int row = 0; row < S_GRID; row++) {
        printf("%2d ", row + 1);                        // Print the row number 
        for(int col = 0; col < S_GRID; col++) {
            if(person == 1) {                           // If it's the player's grid
                printf("\033[0;%dm%c \033[0;37m", color_switch(grid->matrix[row][col]), grid->matrix[row][col]);    // Print the character with the right color 
            }
            else {                                      // If it's the computer's grid
                if(grid->matrix[row][col] == BOAT) {    // If it's a boat cell, we don't show it
                    printf("\033[0;%dm%c \033[0;37m", color_switch(WATER), WATER);
                }
                else {
                    printf("\033[0;%dm%c \033[0;37m", color_switch(grid->matrix[row][col]), grid->matrix[row][col]);
                }
            }
        }
        printf("\n");
    }
}

/*! @brief Function to get the color of a matrix character */
int color_switch(int nb) {
    switch (nb) {
    case 126:                                           // It's a WATER cell 
        return 34;                                      // Blue color 

    case 79:                                            // It's a WATER_SHOT cell 
        return 36;                                      // Cyan color 

    case 66:                                            // It's a BOAT cell 
        return 33;                                      // Yellow color 

    case 88:                                            // It's a WRECK cell 
        return 31;                                      // Red color 
    
    default:                                            // If the number isn't a valid one 
        printf("Argument error (color_case).\n");
        exit(ARGUMENT_ERROR);
        break;
    }
}
