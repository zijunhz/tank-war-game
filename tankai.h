#ifndef D135ABE5_DB75_4EFE_A086_3A52F29A594E
#define D135ABE5_DB75_4EFE_A086_3A52F29A594E

#include "gameProcess.h"
int idiotAct(Game game, int me, int depth, int lifeMe, int lifeYou);
int bestAct(Game game, int me, int depth, int lifeMe, int lifeYou);
double evaluateAct(Game game, int me, int act, int depth, int lifeMe, int lifeYou);
double evaluatePlayer(Game game, int me);
double bulletHit(Game game, int me);
double boundaryPenalty(Game game, int me);
double crashPenalty(Game game, int me);
double evaluateAggressiveness(Game game, int me);
#endif /* D135ABE5_DB75_4EFE_A086_3A52F29A594E */
