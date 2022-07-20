#include "gameControl.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "gameProcess.h"
#include "tankai.h"

/**
 * @brief handle the game's loop
 *
 * @param mode what mode is it
 * @param life init life
 * @param logFile where to store the log file
 */
void mainLoop(Mode mode, int life, char* logFile) {
    int x0, y0, x1, y1;
    int f0, f1;
    if (mode != Demo) {
        printf("%s\n", mode == PvE ? "You have chosen the PvE mode. You will take control of " CYAN "player 2" RESET : "You have chosen the PvP mode.");
        printf("Please enter coordinates for " RED "player 1" RESET " and " CYAN "player 2" RESET " and their initial directions.\n");
        printf("Coordinates should be integers within [1, 20].\n");
        printf("Directions are represented by integers within [0, 3]. 0: up, 1: right, 2: down, 3:left\n");
        printf("e.g. If player 1 is at (5,5) facing down and player 2 is at (15,15) facing up, your input should be   5 5 15 15 2 0\n");
        printf("Input coordinates and directions > ");
        while ((scanf("%d%d%d%d%d%d", &x0, &y0, &x1, &y1, &f0, &f1) != 6)) {
            fflush(stdin);
            printf("Input valid coordinates and directions > ");
        }
    } else {
        printf("You have chosen the DEMO mode. " RED "Player 1 " RESET "is slightly smarter than " CYAN "Player 2" RESET ". Enjoy their fight!\n");
        srand(time(NULL));
        x0 = rand() % 7 + 2;
        y0 = rand() % 18 + 2;
        x1 = rand() % 7 + 12;
        y1 = rand() % 18 + 2;
        f0 = rand() % 4;
        f1 = rand() % 4;
        printf("Press ENTER to continue.");
        getchar();
    }
    Game game(x0, y0, x1, y1, (Direction)f0, (Direction)f1, life, logFile);
    int act0, act1;

    game.print();
    FILE* fp = fopen(logFile, "w");
    fclose(fp);
    game.printLog();

    if (mode == PvP) {
        printf("Actions for " RED "player 1" RESET " and " CYAN "player 2" RESET " can be inputted as an integer within [0, 2].\n");
        printf("0: go straight  1: turn left in place and go straight  2: turn right in place and go straight.\n");
        printf("e.g. If player 1 wants to turn left and player 2 wants to go straight, the input should be  1 0\n");
    }
    if (mode == PvE) {
        printf("Action for " CYAN "player 2" RESET " can be inputted as an integer within [0, 2].\n");
        printf("0: go straight  1: turn left in place and go straight  2: turn right in place and go straight.\n");
        printf("e.g. If you wants to go straight, the input should be  0\n");
    }
    do {
        switch (mode) {
            case PvP: {
                printf("Input actions for " RED "player 1" RESET " and " CYAN "player 2" RESET " > ");
                while (scanf("%d%d", &act0, &act1) != 2) {
                    fflush(stdin);
                    printf("Input valid actions for " RED "player 1" RESET " and " CYAN "player 2" RESET " > ");
                }
                break;
            }
            case PvE: {
                printf("Input action for " CYAN "player 2" RESET " > ");
                while (scanf("%d", &act1) != 1) {
                    fflush(stdin);
                    printf("Input valid actions for " CYAN "player 2" RESET " > ");
                }
                act0 = bestAct(game, 0, 5, game.p[0].life, game.p[1].life);
                break;
            }
            case Demo: {
                act0 = bestAct(game, 0, 5, game.p[0].life, game.p[1].life);
                act1 = idiotAct(game, 1, 1, game.p[1].life, game.p[0].life);
                printf("Press ENTER to continue.");
                getchar();
                break;
            }
        }
    } while (game.processOneTurn(act0, act1, 1));
    game.showFinalResult();
    puts("Press enter to exit");
    if (mode != Demo) {
        getchar();
    }
    getchar();
}
