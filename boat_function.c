#include "game.h"

/*! @brief Function to initialize the boats */
Boat* init_boat() {
    // Locals
    Boat* boats = NULL;

    // Allocation memory for the boats
    boats = malloc(sizeof(Boat) * N_BOAT);
    // Allocation check 
    if(boats == NULL) {
        printf("Allocation error (init_boat).\n");
        exit(ALLOCATION_ERROR);
    }
    
    return boats;
}

/*! @brief Function to place boats*/
Boat create_boat() {
    // Locals
    Boat boat;
    int size;

    // For each boat we get its size
    do {
        printf("\nEnter the boat's \033[0;35msize\033[0;37m (between \033[0;35m1\033[0;37m and \033[0;35m%d\033[0;37m) : ", S_GRID);
        
        // Scanf check 
        if(scanf("%d", &size) != 1) {
            printf("Scanf error (create_boat).\n");
            exit(SCANF_ERROR);
        }

        // Size check
        if (size < 1 || size > S_GRID) {
            printf("The boat's size isn't correct. Please try again.\n");
            sleep(1);
        }
    } while(size < 1 || size > S_GRID);
    
    boat.size = size;                                       // We save the boat's size
    
    return boat;
}
