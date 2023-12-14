#include "game.h"

int main() {
    Game* match = NULL;
    printf("HELLO INITIAL\n");
    match = init_game();
    
    printf("\033[0;32mYour grid :\033[0;37m\n");
    display_grid(match->player_grid, 1);


    printf("\n\033[0;35mComputer's grid :\033[0;37m\n");
    display_grid(match->computer_grid, 0);

    /*
    match->player_grid = shoot(match->computer_grid);

    printf("\n\033[0;35mComputer's grid :\033[0;37m\n");
    display_grid(match->player_grid, 0);
    */

    printf("HELLO FINAL\n");
    return 0;
}

