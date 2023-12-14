#ifndef GRID_h
    #define GRID_T 
    
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

#endif