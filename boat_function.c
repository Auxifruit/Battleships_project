#include "game_function.h"

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