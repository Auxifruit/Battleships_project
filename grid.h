#ifndef GRID_h
    #define GRID_T      /*! To prevent circular inclusion */
    
        /*! @brief Structure to store the grid information */
        typedef struct {
            /*! Grid's matrix */
            int** matrix;
            /*! Grid's size */
            int size;                       
        } Grid ;

        /*! @brief Function to initialize a grid */   
        Grid* init_grid();              

        /*! @brief Function to display a grid */
        void display_grid(Grid* Grid, int person);    

        /*! @brief Function to get the color of a matrix character */
        int color_switch(int nb);
        
        /*! @brief Function to let the player shoot a cell */
        Grid* player_shooting(Grid* grid);

        /*! @brief Function to let the computer shoot a cell */
        Grid* computer_shooting(Grid* grid);

        /*! @brief Function to check if all the boat are destroyed in a grid */
        int verif_winner(Grid* grid);

#endif
