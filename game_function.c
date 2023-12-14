#include "game_function.h"

/*! @brief Function to initialize the game */
Game* init_game() {
    Game* match = NULL;                                 // Locals
    
    match = malloc(sizeof(Game));
    if(match == NULL) {                                 // Allocation check 
        printf("Allocation error (init_grid).\n");
        exit(ALLOCATION_ERROR);
    }

    match->player_grid = init_grid();
    match->player_boat = init_boat();

    match->computer_grid = init_grid();

    return match;
}

/*! @brief Function to shoot on a cell */
Grid* shoot(Grid* grid) {
    int row;                                            // Locals
    int col;

    if(grid == NULL) {                                  // Argument verification
        printf("Argument error (shoot).\n");
        exit(ARGUMENT_ERROR);
    }

    do {                                                // The player input the cell he want to shoot
        printf("Choose a ROW between 1 and 10 : ");
        if(scanf("%d", &row) != 1) {
            printf("Error scanf (shoot).\n");
            exit(SCANF_ERROR);
        }

        printf("\n");
        printf("Choose a COLUMN between 1 and 10 : ");
        if(scanf("%d", &col) != 1) {
            printf("Error scanf (shoot).\n");
            exit(SCANF_ERROR);
        }

        if((row < 0 || row > 10) || (col < 0 || col > 10)) {
            printf("You input the wrong coordinates. Please try again.\n\n");
        }
        else if(grid->matrix[row][col] != WATER && grid->matrix[row][col] != BOAT) {
            printf("The cell you want to shoot is already touched. Please try again.\n\n");
        }
        
    } while ((row < 0 || row > 10) || (col < 0 || col > 10) || (grid->matrix[row][col] != WATER && grid->matrix[row][col] != BOAT));    // Verification if the cell can be shoot

    switch (grid->matrix[row][col]) {
    case WATER:
        grid->matrix[row][col] = WATER_SHOT;
        return grid;
    case BOAT:
        grid->matrix[row][col] = BOAT;
        // VERIFIER BATEAU
        return grid;
    default:
        printf("ERROR\n");
        exit(SCANF_ERROR);
    }
    
}