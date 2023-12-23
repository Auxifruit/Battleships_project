#include "game.h"

int main() {
    //Locals
    Game* match = NULL;
    int end = 0;

    welcome();                                                              // Welcome message

    match = init_game();                                                    // Initialization of the game (boat and grid)

    match = create_navy(match);                                             // We create all the boat

    match = place_boat_player(match);                                       // The player places his boats
    match = place_boat_computer(match);                                     // The computer places its boats


    // We show the player's grid with all his boat
    printf("\nHere's your final grid :\n");
    display_grid(match->player_grid, 1);
    sleep(1);

    printf("\nNow, you can destroy boats !\n");
    sleep(1);

    do {
        printf("\nIt's your time to shoot !\n");
        sleep(1);

        boat_remaining(match);                                              // We show the remaining boats

        // The player shoot
        display_grid(match->computer_grid, 0);
        match->computer_grid = player_shooting(match->computer_grid);
        display_grid(match->computer_grid, 0);
        sleep(2);

        end = verif_winner(match->computer_grid, 0);                        // We verify the player won

        // If we don't have a winner yet
        if(end == 0) {
            printf("\nBe carefull, the computer is shooting !\n");
            sleep(1);
            
            // The computer shoot
            match->player_grid = computer_shooting(match->player_grid);
            display_grid(match->player_grid, 1);
            sleep(2);
        
            end = verif_winner(match->player_grid, 1);                      // We verify the computer won
        }
        
    } while(end == 0);
    
    // If the computer won
    if(end == 1) {
        printf("\nYou lost, better luck next time !\n");
    }
    // If the player won
    else {
        printf("\nYou won, you're the best commander !\n");
    }
    
    free_all(match);

    printf("\nTHANK YOU FOR PLAYING !\n");
    
    return 0;
}

