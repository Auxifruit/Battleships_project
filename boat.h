#ifndef BOAT_h
    #define BOAT_T 
    
        /*! @brief Structure to store the boat information */
        typedef struct {
            /*! Boat's starting position */
            int** position;
            /*! Boat's size */
            int size;
            /*! Boat's orientation (V for vertical and H for Horizontale) */
            char orientation;               
        } Boat ;

        /*! @brief Function to initialize the boats */
        Boat* init_boat();        

#endif