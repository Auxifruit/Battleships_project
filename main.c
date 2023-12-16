#include "game.h"

int main() {
    Game* match = NULL;
    printf("HELLO INITIAL\n");
    match = init_game();
    int end = 0;
    
    printf("\033[0;32mYour grid :\033[0;37m\n");
    display_grid(match->player_grid, 1);

    // printf("\n\033[0;35mComputer's grid :\033[0;37m\n");
    // display_grid(match->computer_grid, 0);

    for(int i = 0; i < N_BOAT; i++) {
        match->player_boat[i] = create_boat();
        match->computer_boat[i] = match->player_boat[i];
    }

    match = place_boat(match);

    do {
        match->player_grid = shoot(match->player_grid);
        printf("\033[0;32mYour grid :\033[0;37m\n");
        display_grid(match->player_grid, 1);
        end = verif_winner(match->player_grid);
    } while(end == 0);

    printf("HELLO FINAL\n");
    
    return 0;
}

