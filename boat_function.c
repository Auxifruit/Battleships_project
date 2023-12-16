#include "game.h"

/*! @brief Function to initialize the boats */
Boat* init_boat() {
    Boat* boats = NULL;                                 // Locals

    boats = malloc(sizeof(Boat) * N_BOAT);
    if(boats == NULL) {                                  // Allocation check 
        printf("Allocation error (init_grid).\n");
        exit(ALLOCATION_ERROR);
    }
    
    return boats;
}

/*! @brief Function to place boats*/
Boat create_boat() {
    Boat boat;                                          // Locals
    int size;

    do {                                                // For each boat we get its size
        printf("Enter the boat's size between 1 and %d : ", S_GRID);
        if(scanf("%d", &size) != 1) {                   // Scanf check 
            printf("Scanf error (create_boat).\n");
            exit(SCANF_ERROR);
        }
        if (size < 0 || size > S_GRID) {
            printf("The boat's size isn't correct. Please try again.\n");
        }
    } while(size < 0 || size > S_GRID);
    boat.size = size;
    
    return boat;
}
