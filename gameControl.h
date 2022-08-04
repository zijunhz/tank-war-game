#ifndef A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA
#define A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA
typedef enum {
    PvP,
    PvE,
    Demo
} Mode;
/**
 * @brief judge whether the two actions are valid
 *
 * @param f0
 * @param f1
 * @return int
 */
int isValidDirection(int f0, int f1);
/**
 * @brief judge whether an act is valid
 *
 * @param act
 * @return int
 */
int isValidAct(int act);
/**
 * @brief judge whether the user inputs too many command
 *
 * @return int
 */
int somethingLeft();
/**
 * @brief judge whether (x,y) is in the initial board
 *
 * @param x
 * @param y
 * @return int
 */
int isIn20(int x, int y);
/**
 * @brief handle the game's loop
 *
 * @param mode what mode is it
 * @param life init life
 * @param logFile where to store the log file
 */
void mainLoop(Mode mode, int life, char* logFile);
void pvp();
void pve();
/**
 * @brief this is the demo mode
 *
 */
void eVIdiot();
#endif /* A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA */
