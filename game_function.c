#include "game.h"

/*! @brief Function to print a welcome message */
void welcome() {
    printf("HELLO INITIAL\n");

    printf("\033[0;34m  ____        _   _   _       _____ _     _           \n");
    printf(" |  _ \\      | | | | | |     / ____| |   (_)          \n");
    printf(" | |_) | __ _| |_| |_| | ___| (___ | |__  _ _ __  ___ \n");
    printf(" |  _ < / _` | __| __| |/ _ \\____ \\| '_ \\| | '_ \\/ __|\n");
    printf(" | |_) | (_| | |_| |_| |  __/____) | | | | | |_) \\__ \\\n");
    printf(" |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_| .__/|___/\n");
    printf("                                           | |        \n");
    printf("                                           |_|        \033[0;37m\n");

    printf("Welcome to this Battleships game !\n");
    sleep(1);
    printf("First please create %d ships. Then place it.\n", N_BOAT);
    sleep(1);
    printf("You'll be able to play versus the computer next.\n");
    sleep(1);
}

/*! @brief Function to initialize the game */
Game* init_game() {
    // Locals
    Game* match = NULL; 

    // Allocation check 
    match = malloc(sizeof(Game));
    if(match == NULL) {                                 
        printf("Allocation error (init_grid).\n");
        exit(ALLOCATION_ERROR);
    }

    match->player_grid = init_grid();                   // Initialize player's grid
    match->player_boat = init_boat();                   // Initialize player's boats

    match->computer_grid = init_grid();                 // Initialize computer's grid
    match->computer_boat = init_boat();                 // Initialize computer's grid

    return match;
}

/*! @brief Function to creat a boat armada */
Game* create_armada(Game* game) {
    // Argument check
    if(game == NULL) {
        printf("Argument error (place_boat_computer).\n");
        exit(ARGUMENT_ERROR);
    }

    // We create all the boat one by one
    for(int i = 0; i < N_BOAT; i++) {
        printf("\nYou're creating the boat n°%d", i+1);

        game->player_boat[i] = create_boat();
        game->computer_boat[i] = game->player_boat[i];
    }
    return game;
}

/*! @brief Function to place the player's boats in his grid */
Game* place_boat_player(Game* game) {
    // Argument check
    if(game == NULL) {
        printf("Argument error (place_boat_player).\n");
        exit(ARGUMENT_ERROR);
    }

    // Locals
    int row = -1;
    int col = -1;
    int verif = 0;
    int orientation;

    // We do it for each bot the player has
    for(int indice = 0; indice < N_BOAT; indice++) {                        
        do {

            display_grid(game->player_grid, 1);
            
            printf("\nYou want to place a boat of size : %d\n", game->player_boat[indice].size);

            do {
                printf("\nEnter the \033[0;31mrow\033[0;37m where you want to place your boat (between \033[0;31m1\033[0;37m and \033[0;31m10\033[0;37m) : ");

                // Scanf check 
                if(scanf("%d", &row) != 1) {
                    printf("Scanf error (place_boat_player).\n");
                    exit(SCANF_ERROR);
                }
                // Row check 
                if(row < 0 || row > S_GRID) {
                    printf("You enter a wrong number for the row. Please try again.\n");
                    sleep(1);
                }

            } while (row < 0 || row > S_GRID);  // Check if we're in the grid or not
            
            do {
                printf("\nEnter the \033[0;36mcolumn\033[0;37m where you want to place your boat (between \033[0;36m1\033[0;37m and \033[0;36m10\033[0;37m) : ");

                // Scanf check 
                if(scanf("%d", &col) != 1) {
                    printf("Scanf error (place_boat_player).\n");
                    exit(SCANF_ERROR);
                }

                // Column check
                if(col < 0 || col > S_GRID) {
                    printf("You enter a wrong number for the column. Please try again.\n");
                    sleep(1);
                }

            } while (col < 0 || col > S_GRID);  // Check if we're in the grid or not
            
            do {
                printf("\nEnter the \033[0;32morientation\033[0;37m (\033[0;32mV\033[0;37m for vertical and \033[0;32mH\033[0;73m for horizontal) : ");

                // Scanf check 
                if(scanf("%d", &orientation) != 1) {
                    printf("Scanf error (place_boat_player).\n");
                    exit(SCANF_ERROR);
                }

                // Orientation check
                if(orientation != 86 && orientation != 72) {
                    printf("You enter a wrong orientation. Please try again.\n");
                    sleep(1);
                }
            } while (orientation != 86 && orientation != 72);   // Check if we have a valid orientation
            
            // Check if all the information are correct
            verif = verif_position(row - 1, col - 1, orientation, game->player_boat[indice], game->player_grid);
            // If not
            if(verif != 1) {
                printf("The position isn't possible, your boat go further than your grid. Please try again.\n");
                sleep(1);
            }
        } while(verif != 1);

        // All the information are correct, we can update our boat

        game->player_boat[indice].orientation = orientation;

        row -= 1;                                                           // We get the true value of the row
        col -= 1;                                                           // We get the true value of the column

        // Allocate memory for the position
        game->player_boat[indice].position = malloc(sizeof(int) * 2);
        // Allocation check
        if(game->player_boat[indice].position == NULL) {
            printf("Allocation error (place_boat_player).\n");
            exit(ALLOCATION_ERROR);
        }

        game->player_boat[indice].position[0] = row;                        // We save the boat's row
        game->player_boat[indice].position[1] = col;                        // We save the boat's column

        game->player_grid = put_boat(game->player_boat[indice], game->player_grid);     // We place the boat in the player's grid

        display_grid(game->player_grid, 1);
    }
    
    return game;
}

Game* place_boat_computer(Game* game) {    
    // Argument check
    if(game == NULL) {
        printf("Argument error (place_boat_computer).\n");
        exit(ARGUMENT_ERROR);
    }

    // Locals
    int row;
    int col;
    int ori;
    int orientation[2] = {86, 72};

    srand(time(NULL));

    // For each boat
    for(int indice = 0; indice < N_BOAT; indice++) {                        
        do {
            ori = rand() % 2;                                                       // We take a random orientation

            // If horizontale
            if(ori == 0) {
                row = rand() % S_GRID;                                              // We take a random row

                // We check is the boat's size is the same as the grid
                if(S_GRID - game->computer_boat[indice].size != 0) {
                    col = rand() % (S_GRID - game->computer_boat[indice].size);     // We take a valid column
                }
                else {
                    col = 0;
                } 
            }
            // If verticale
            else {                                                  
                // We check is the boat's size is the same as the grid        
                if(S_GRID - game->computer_boat[indice].size != 0) {
                    row = rand() % (S_GRID - game->computer_boat[indice].size);     // We take a valid row
                }
                else {
                    row = 0; 
                }
                
                col = rand() % S_GRID;                                              // We take a random column
            }
        } while(!verif_position(row, col, orientation[ori], game->computer_boat[indice], game->computer_grid));     // We do it while we can't place the boat
        
        // All the information are correct, we can update our boat

        game->computer_boat[indice].orientation = orientation[ori];         // We save the boat's orientation

        // Allocate memory for the position
        game->computer_boat[indice].position = malloc(sizeof(int) * 2);
        //Allocation check
        if(game->computer_boat[indice].position == NULL) {
            printf("Allocation error (place_boat_player).\n");
            exit(ALLOCATION_ERROR);
        }

        game->computer_boat[indice].position[0] = row;                      // We save the boat's row
        game->computer_boat[indice].position[1] = col;                      // We save the boat's column

        game->computer_grid = put_boat(game->computer_boat[indice], game->computer_grid);

    }

    return game;
}

Grid* put_boat(Boat boat, Grid* grid) {
    // Argument check 
    if((boat.position[0] < 0 || boat.position[0] > S_GRID) || (boat.position[1] < 0 || boat.position[1] > S_GRID) || (boat.orientation != 86 && boat.orientation != 72) || grid == NULL) {
        printf("Argument error (verif_position).\n");
        exit(ARGUMENT_ERROR);
    }
    
    // Locals
    int row = boat.position[0];
    int col = boat.position[1];

    // If the boat is horizontal
    if(boat.orientation == 86) {
        for(int j = col; j < boat.size + col; j++) {
            grid->matrix[row][j] = BOAT;
        }
    }
    // If the boat is vertical
    else {
        for(int j = row; j < boat.size + row; j++) {
            grid->matrix[j][col] = BOAT;
        }
    }

    return grid;
}

int verif_position(int row, int col, int orientation, Boat boat, Grid* grid) {
    // Argument check 
    if((row < 0 || row > S_GRID) || (col < 0 || col > S_GRID) || (orientation != 86 && orientation != 72) || grid == NULL) {
        printf("Argument error (verif_position).\n");
        exit(ARGUMENT_ERROR);
    }
    
    // If the boat is horizontal 
    if(orientation == 86) {

        // Check if the boat quit the grid
        if(col + boat.size > S_GRID) {
            return 0;
        }

        for(int i = col; i < boat.size + col; i++) {

            // Check if the boat meet another boat
            if(grid->matrix[row][i] == BOAT) {          
                return 0;
            }
        }
    }
    // If the boat is vertical
    else {                            
        // Check if the boat quit the grid                  
        if(row + boat.size > S_GRID) {
            return 0;
        }

        for(int i = row; i < boat.size + row; i++) {

            // Check if the boat meet another boat
            if(grid->matrix[i][col] == BOAT) {
                return 0;
            }
        }
    }
    
    return 1;
}
