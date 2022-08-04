#ifndef D135ABE5_DB75_4EFE_A086_3A52F29A594E
#define D135ABE5_DB75_4EFE_A086_3A52F29A594E

#include "gameProcess.h"
/**
 * @brief pick idiot but not totally idiot act
 *
 * @param game
 * @param me
 * @param depth max recursion depth
 * @param lifeMe
 * @param lifeYou
 * @return int act can be 0 1 or 2
 */
int idiotAct(Game game, int me, int depth, int lifeMe, int lifeYou);
/**
 * @brief pick best act for me in game
 *
 * @param game
 * @param me
 * @param depth max recursion depth
 * @param lifeMe
 * @param lifeYou
 * @return int act can be 0 1 or 2
 */
int bestAct(Game game, int me, int depth, int lifeMe, int lifeYou);
/**
 * @brief evaluate how good it is for p[me] to take act in the next move.
 *
 * @param game current game
 * @param i player, either 0 or 1
 * @param act act, either 0 1 or 2
 * @param depth recursion depth
 * @param lifeMe life of p[me] in the last depth
 * @param lifeYou life of p[you] in the last depth
 * @return double how good it is, the better the higher
 */
double evaluateAct(Game game, int me, int act, int depth, int lifeMe, int lifeYou);
/**
 * @brief evaluate how good the situation is for p[me]. Notice that the map is STATIC!!!
 *
 * @param game
 * @param me can be 0 or 1
 * @return double how good the situation is for p[me]
 */
double evaluatePlayer(Game game, int me);
/**
 * @brief evaluate how likely the bullets are gonna hit p[me]
 *
 * @param game
 * @param me can be 0 or 1
 * @return double how likely the bullets are gonna hit p[me]
 */
double bulletHit(Game game, int me);
/**
 * @brief evaluate how likely p[me] are going to be damaged due to out of boundary
 *
 * @param game
 * @param me can be 0 or 1
 * @return double
 */
double boundaryPenalty(Game game, int me);
/**
 * @brief evaluate how likely p[me] are going to be damaged due to collision
 *
 * @param game
 * @param me
 * @return double
 */
double crashPenalty(Game game, int me);
/**
 * @brief evaluate how aggressive p[me] is
 *
 * @param game
 * @param me
 * @return
 */
double evaluateAggressiveness(Game game, int me);
#endif /* D135ABE5_DB75_4EFE_A086_3A52F29A594E */
