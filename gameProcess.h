#ifndef D006ACF8_6C3E_4ECF_B81B_8150B9BD023B
#define D006ACF8_6C3E_4ECF_B81B_8150B9BD023B
#define bltMAXSIZE 200

#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */
typedef enum {
    Up,
    Right,
    Down,
    Left
} Direction;
const char icon[4] = {'A', '>', 'V', '<'};
int dx(Direction d);
int dy(Direction d);

class Player {
   public:
    int x, y;
    int life;
    int dx, dy;
    Direction dir;
    int isTurned;
    void turn(int act);
    void move();
    void init(int x, int y, int life, int dx, int dy, Direction dir, int isTurned);
};
class Bullet {
   public:
    int x, y;
    Direction dir;
    int dx, dy;
    void init(int x, int y, Direction dir, int dx, int dy);
};
class Game {
   public:
    Player p[2];
    int turn;
    int bltCnt;
    Bullet blt[bltMAXSIZE];
    int canCollide;  // is it possible for the tanks to collide
    char* fileLog;
    Game(int x0, int y0, int x1, int y1, Direction dir0, Direction dir1, int life, char* logFile);
    int processOneTurn(int act1, int act2, int doPrint);
    void generateBullet();
    int tankTankCollision();
    void moveBullet();
    int isIn(int x, int y);
    int isBulletOut(int x, int y);
    void print();
    void printLog();
    int gameEnd();
    void showFinalResult();
    int getBoundMin();
    int getBoundMax();
};
#endif /* D006ACF8_6C3E_4ECF_B81B_8150B9BD023B */
