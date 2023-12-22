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

/*! @brief Function to let the player shoot a cell */
Grid* player_shooting(Grid* grid) {
    // Argument check
    if(grid == NULL) {
        printf("Argument error (shoot).\n");
        exit(ARGUMENT_ERROR);
    }

    // Locals
    int row;
    int col;

    // The player input the cell he want to shoot
    do {
        printf("\nEnter the \033[0;31mrow\033[0;37m where you want to shoot (between \033[0;31m1\033[0;37m and \033[0;31m10\033[0;37m) : ");

        // Scanf check 
        if(scanf("%d", &row) != 1) {
            printf("Error scanf (shoot).\n");
            exit(SCANF_ERROR);
        }

        printf("\nEnter the \033[0;36mcolumn\033[0;37m where you want shoot (between \033[0;36m1\033[0;37m and \033[0;36m10\033[0;37m) : ");

        // Scanf check 
        if(scanf("%d", &col) != 1) {
            printf("Error scanf (shoot).\n");
            exit(SCANF_ERROR);
        }

        // If the cell we want to shoot is outside the grid
        if((row < 0 || row > 10) || (col < 0 || col > 10)) {
            printf("You input a wrong coordinates. Please try again.\n\n");
            sleep(1);
        }
        // If a cell was already shot
        else if(grid->matrix[row - 1][col - 1] != WATER && grid->matrix[row - 1][col - 1] != BOAT) {
            printf("The cell you want to shoot was already shot. Please try again.\n\n");
            sleep(1);
        }
        
    } while ((row < 0 || row > 10) || (col < 0 || col > 10) || (grid->matrix[row][col] != WATER && grid->matrix[row][col] != BOAT));    // Verification if the cell can be shoot

    row -= 1;                                           // We get the true value of the row
    col -= 1;                                           // We get the true value of the column

    // Check what type of cell we touched
    if(grid->matrix[row][col] == WATER) {
        grid->matrix[row][col] = WATER_SHOT;            // If it's a WATER cell
    }                 
    else {
        grid->matrix[row][col] = WRECK;                 // If it's a BOAT cell
    }
    
    return grid;
}

/*! @brief Function to let the computer shoot a cell */
Grid* computer_shooting(Grid* grid) {
    // Argument check
    if(grid == NULL) {
        printf("Argument error (shoot).\n");
        exit(ARGUMENT_ERROR);
    }

    // Locals
    int row;
    int col;
    int try = 0;

    srand(time(NULL));

    // We choose a random cell
    do {
        row = rand() % S_GRID;
        col = rand() % S_GRID;
        try++;

    } while((grid->matrix[row][col] != WATER && grid->matrix[row][col] != BOAT) && try <= 30); // Check if we can shoot it

    // If the computer makes to much try, we'll search cell by cell
    if(try >= 30) {
        row = 0;
        col = 0;
        while(grid->matrix[row][col] != WATER && grid->matrix[row][col] != BOAT) {
            row++;
            col++;
        }
    }

    // Check what type of cell we touched
    if(grid->matrix[row][col] == WATER) {
        grid->matrix[row][col] = WATER_SHOT;            // If it's a WATER cell
    }                 
    else {
        grid->matrix[row][col] = WRECK;                 // If it's a BOAT cell
    }
    
    return grid;
}

/*! @brief Function to check if all the boat are destroyed in a grid */
int verif_winner(Grid* grid) {
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

    return 1;                                           // We din't find a single boat, the game can end
}
