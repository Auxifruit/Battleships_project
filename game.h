#ifndef NAVALE_h
    #define NAVALE_h 
        #include <stdio.h>
        #include <stdlib.h>
        #include "boat.h"
        #include "grid.h"

        #define N_BOAT 5                    /*! Number of boat for each person */
        #define S_GRID 10                   /*! Number for the size of the grid */
        #define ALLOCATION_ERROR 1          /*! Number for allocation error */
        #define SCANF_ERROR 2               /*! Number for scanf error */
        #define ARGUMENT_ERROR 3            /*! Number for scanf error */


        /*! @brief Enumeration to have the state of the cell */
        enum cell_state_enum {              
            /*! If it's a water cell */                
            WATER = 126,
            /*! If the water cell was shot */
            WATER_SHOT = 79,
            /*! If it's a boat cell */
            BOAT = 66,
            /*! If the boat is destroyed */
            WRECK = 88                      
        } ;

        /*! @brief Structure to store the game information */
        typedef struct {
            /*! Player's grid */
            Grid* player_grid;
            /*! Player's boats */
            Boat* player_boat;
            /*! Computer's grid */
            Grid* computer_grid;
            /*! Computer's boats */
            Boat* computer_boat;            
        } Game ;

        /*! @brief Function to initialize the game */
        Game* init_game();
        /*! @brief Function to shoot on a cell */
        Grid* shoot(Grid* grid);   

#endif