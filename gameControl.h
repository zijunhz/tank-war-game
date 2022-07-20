#ifndef A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA
#define A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA
typedef enum {
    PvP,
    PvE,
    Demo
} Mode;
void mainLoop(Mode mode, int life, char* logFile);
void pvp();
void pve();
void eVIdiot();
#endif /* A2AD3DBA_1A39_4DA7_98E8_082561A0C1AA */
