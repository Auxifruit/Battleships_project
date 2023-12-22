#include "game.h"

int main() {
    Game* match = NULL;
    int end = 0;

    //welcome();


    match = init_game();

    match = create_navy(match);

    match = place_boat_player(match);
    match = place_boat_computer(match);


    printf("\nHere's your final grid :\n");
    display_grid(match->player_grid, 1);
    sleep(1);

    printf("\nNow, you can destroy boats !\n");
    sleep(1);

    do {
        printf("\nIt's your time to shoot !\n");
        sleep(1);

        boat_remaining(match);

        display_grid(match->computer_grid, 0);
        match->computer_grid = player_shooting(match->computer_grid);
        display_grid(match->computer_grid, 0);

        printf("\nBe carefull, the computer is shooting !\n");
        sleep(1);
        
        match->player_grid = computer_shooting(match->player_grid);
        display_grid(match->player_grid, 1);
        sleep(1);

        end = verif_winner(match->player_grid, 1);
        end = verif_winner(match->computer_grid, 0);
    } while(end == 0);
    
    if(end == 1) {
        printf("\nYou lost, better luck next time !\n");
    }
    else {
        printf("\nYou won, you're the best commander !\n");
    }
    
    printf("\nTHANK YOU FOR PLAYING !\n");
    
    return 0;
}

