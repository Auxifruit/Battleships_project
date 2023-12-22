#include "game.h"

/*! @brief Function to initialize a game */
Grid* init_grid() {
    // Locals
    Grid* grid = NULL;

    //Allocate memory for the grid
    grid = malloc(sizeof(Grid));
    // Allocation check
    if(grid == NULL) {
        printf("Allocation error (init_grid).\n");
        exit(ALLOCATION_ERROR);
    }

    grid->size = S_GRID;

    // Allocate memory for the "rows" 
    grid->matrix = malloc(sizeof(int*) * S_GRID);
    // Allocation check 
    if(grid->matrix == NULL) {
        printf("Allocation error (init_grid).\n");
        exit(ALLOCATION_ERROR);
    }

    for(int i = 0; i < S_GRID; i++) {
        // Allocate memory for the "Columns" 
        grid->matrix[i] = malloc(sizeof(int) * S_GRID);
        // Allocation check 
        if(grid->matrix[i] == NULL) {
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
    // Argument check
    if(grid == NULL || (person != 1 && person != 0)) {
        printf("Argument error (display_grid).\n");
        exit(ARGUMENT_ERROR);
    }

    // If it's the player's grid
    if(person == 1) {
        printf("\n\033[0;32mYour grid :\033[0;37m\n");

        printf("   ");
        for(int n_col = 0; n_col < S_GRID; n_col++) {
            printf("%d ", n_col + 1);                   // Print the column number
        }
        printf("\n");

        for(int row = 0; row < S_GRID; row++) {
            printf("%2d ", row + 1);                    // Print the row number 
            for(int col = 0; col < S_GRID; col++) {
                printf("\033[0;%dm%c \033[0;37m", color_switch(grid->matrix[row][col]), grid->matrix[row][col]);    // Print the character with the right color 
            }
            printf("\n");
        }
    }
    // If it's the computer's grid
    else {
        printf("\n\033[0;35mComputer's grid :\033[0;37m\n");

        printf("   ");
        for(int n_col = 0; n_col < S_GRID; n_col++) {
            printf("%d ", n_col + 1);                   // Print the column number 
        }
        printf("\n");

        for(int row = 0; row < S_GRID; row++) {
            printf("%2d ", row + 1);                    // Print the row number 
            for(int col = 0; col < S_GRID; col++) {
                // If it's a boat cell, we don't show it
                if(grid->matrix[row][col] == BOAT) {
                    printf("\033[0;%dm%c \033[0;37m", color_switch(WATER), WATER);
                }
                else {
                    printf("\033[0;%dm%c \033[0;37m", color_switch(grid->matrix[row][col]), grid->matrix[row][col]);
                }
            }
            printf("\n");
        }
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
        printf("Argument error (color_switch).\n");
        exit(ARGUMENT_ERROR);
        break;
    }
}

/*! @brief Function to check if all the boat are destroyed in a grid */
int verif_winner(Grid* grid, int person) {
    // Argument check 
    if(grid == NULL) {
        printf("Argument error (verif_winner).\n");
        exit(ARGUMENT_ERROR);
    }

    // Check if any boat remain in the grid
    for(int row = 0; row < S_GRID; row++) {
        for(int col = 0; col < S_GRID; col++) {
            if(grid->matrix[row][col] == BOAT) {        // If we find a boat, the game can continue
                return 0;
            }
        }
    }
    // We din't find a single boat, the game can end
    if(person == 1) {
        return 1;                                       // The player has lost                                   
    }
    else {
        return 2;                                       // The computer has lost
    }
}
