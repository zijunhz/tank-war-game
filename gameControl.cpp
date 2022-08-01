#include "gameControl.h"
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "gameProcess.h"
#include "tankai.h"

int isValidDirection(int f0, int f1) {
    return (0 <= f0 && f0 <= 3 && 0 <= f1 && f1 <= 3);
}

/**
 * @brief judge whether an act is valid
 *
 * @param act
 * @return int
 */
int isValidAct(int act) {
    return 0 <= act && act <= 2;
}

/**
 * @brief judge whether the user inputs too many command
 *
 * @return int
 */
int somethingLeft() {
    char ch;
    ch = getchar();
    while (ch != '\n') {
        if (ch != ' ') {
            return 1;
        }
        ch = getchar();
    }
    return 0;
}

/**
 * @brief judge whether (x,y) is in the initial board
 *
 * @param x
 * @param y
 * @return int
 */
int isIn20(int x, int y) {
    return 1 <= x && x <= 20 && 1 <= y && y <= 20;
}

/**
 * @brief handle the game's loop
 *
 * @param mode what mode is it
 * @param life init life
 * @param logFile where to store the log file
 */
void mainLoop(Mode mode, int life, char* logFile) {
    int x0 = 1, y0 = 1, x1 = 20, y1 = 20;
    int f0 = 2, f1 = 0;
    if (mode != Demo) {
        printf("%s\n", mode == PvE ? "You have chosen the PvE mode. You will take control of " CYAN "player 2" RESET : "You have chosen the PvP mode.");
        printf("Please enter coordinates for " RED "player 1" RESET " and " CYAN "player 2" RESET " and their initial directions.\n");
        printf("Coordinates should be integers within [1, 20].\n");
        printf("Directions are represented by integers within [0, 3]. 0: up, 1: right, 2: down, 3:left\n");
        printf("e.g. If player 1 is at (5,5) facing down and player 2 is at (15,15) facing up, your input should be   5 5 15 15 2 0\n");
        printf("Input coordinates and directions > ");
        while ((scanf("%d%d%d%d%d%d", &x0, &y0, &x1, &y1, &f0, &f1) != 6) || (!isIn20(x0, y0)) || (!isIn20(x1, y1)) || (x0 == x1 && y0 == y1) || (!isValidDirection(f0, f1)) || somethingLeft()) {
            fflush(stdin);
            printf("Input valid coordinates and directions > ");
        }
        fflush(stdin);
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
        fflush(stdin);
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
    int demoSkip = 1;
    do {
        switch (mode) {
            case PvP: {
                printf("Input actions for " RED "player 1" RESET " and " CYAN "player 2" RESET " > ");
                while (scanf("%d%d", &act0, &act1) != 2 || (!isValidAct(act0)) || (!isValidAct(act1)) || somethingLeft()) {
                    fflush(stdin);
                    printf("Input valid actions for " RED "player 1" RESET " and " CYAN "player 2" RESET " > ");
                }
                break;
            }
            case PvE: {
                printf("Input action for " CYAN "player 2" RESET " > ");
                while (scanf("%d", &act1) != 1 || (!isValidAct(act1)) || somethingLeft()) {
                    fflush(stdin);
                    printf("Input valid action for " CYAN "player 2" RESET " > ");
                }
                act0 = bestAct(game, 0, 5, game.p[0].life, game.p[1].life);
                break;
            }
            case Demo: {
                demoSkip--;
                act0 = bestAct(game, 0, 5, game.p[0].life, game.p[1].life);
                act1 = idiotAct(game, 1, 1, game.p[1].life, game.p[0].life);
                if (demoSkip == 0) {
                    printf("Press ENTER to continue, or input a number n to fast forward n turns. ");
                    fflush(stdin);
                    char ch = getchar();
                    demoSkip = 0;
                    while (isdigit(ch)) {
                        demoSkip = demoSkip * 10 + ch - '0';
                        ch = getchar();
                    }
                    if (demoSkip <= 0 || (ch != '\n' && somethingLeft())) {
                        demoSkip = 1;
                    }
                }
                break;
            }
        }
    } while (game.processOneTurn(act0, act1, 1));
    game.showFinalResult();
    puts("Press enter to exit");
    getchar();
}
