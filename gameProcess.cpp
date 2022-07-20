#include "gameProcess.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "tankai.h"
#define SMALL 0.0001

int getDx(Direction d) {
    int res[4] = {-1, 0, 1, 0};
    return res[d];
}
int getDy(Direction d) {
    int res[4] = {0, 1, 0, -1};
    return res[d];
}

/**
 * @brief Construct a new Game:: Game object
 *
 * @param x0 x=x0+1
 * @param y0 y=t0+1
 * @param x1 same
 * @param y1 same
 * @param dir0 direction of p0
 * @param dir1 direction of p1
 * @param life init life
 * @param logFile where to store the log file
 */
Game::Game(int x0, int y0, int x1, int y1, Direction dir0, Direction dir1, int life, char* logFile) {
    p[0].init(x0, y0, life, getDx(dir0), getDy(dir0), dir0, 0);
    p[1].init(x1, y1, life, getDx(dir1), getDy(dir1), dir1, 0);
    turn = 0;
    bltCnt = 0;
    canCollide = (abs(x0 - x1) + abs(y0 - y1)) % 2 == 0;
    fileLog = logFile;
}

/**
 * @brief p[0] takes act1 and p[1] takes act2, update the game by 1 turn by calling other methods in Game class
 *
 * @return 1: game continues 0: game ends
 *
 * @param act0 0: move 1/2: turn left/right
 * @param act1 same as act1
 * @param doPrint whether to print the result or not
 */
int Game::processOneTurn(int act0, int act1, int doPrint) {
    turn++;
    p[0].turn(act0);
    p[1].turn(act1);
    p[0].move();
    p[1].move();
    if (canCollide && tankTankCollision()) {
        return 0;
    }
    generateBullet();
    moveBullet();
    if (!isIn(p[0].x, p[0].y)) {
        p[0].life--;
    }
    if (!isIn(p[1].x, p[1].y)) {
        p[1].life--;
    }
    if (gameEnd()) {
        return 0;
    }
    if (doPrint) {
        print();
        printLog();
    }
    return 1;
}

/**
 * @brief judge whether the game ends or not
 *
 * @return int 1 if end 0 if not
 */
int Game::gameEnd() {
    return (p[0].life <= 0 || p[1].life <= 0);
}

/**
 * @brief print final result when game ends
 *
 */
void Game::showFinalResult() {
    print();
    printLog();
    puts("");
    if (p[0].life <= 0) {
        if (p[1].life > 0) {
            printf(CYAN "Player 2 wins\n");
        } else {
            printf("Draw\n");
        }
    } else {
        printf(RED "Player 1 wins\n");
    }
    printf(RESET "\n");

    FILE* fp = fopen(fileLog, "a");
    fprintf(fp, "\n");
    if (p[0].life <= 0) {
        if (p[1].life > 0) {
            fprintf(fp, "Player 2 wins\n");
        } else {
            fprintf(fp, "Draw\n");
        }
    } else {
        fprintf(fp, "Player 1 wins\n");
    }
    fclose(fp);
}

/**
 * @brief generate the game's bullet
 *
 */
void Game::generateBullet() {
    if ((turn - 1) % 3 == 0) {
        for (int i = 0; i <= 1; i++) {
            Player t = p[i];
            bltCnt++;
            blt[bltCnt].init(t.x + t.dx, t.y + t.dy, t.dir, t.dx, t.dy);
        }
    }
}

/**
 * @brief judge tank collision
 *
 * @return int 1: a collision happens 0: no collision
 */
int Game::tankTankCollision() {
    if (p[0].x == p[1].x && p[0].y == p[1].y) {
        if (p[0].life < p[1].life) {
            p[0].life = 0;
            p[1].life = 1;
        } else if (p[0].life > p[1].life) {
            p[0].life = 1;
            p[1].life = 0;
        } else {
            p[0].life = p[1].life = 0;
        }
        return 1;
    }
    return 0;
}

/**
 * @brief move bullet
 *
 */
void Game::moveBullet() {
    int i = 1;
    while (i <= bltCnt) {
        for (int j = 0; j <= 1; j++) {
            if (blt[i].x == p[j].x && blt[i].y == p[j].y) {
                p[j].life -= 2;
                blt[i--] = blt[bltCnt--];
                break;
            }
        }
        i++;
    }
    for (int T = 1; T <= 2; T++) {
        int i = 1;
        while (i <= bltCnt) {
            blt[i].x += blt[i].dx;
            blt[i].y += blt[i].dy;
            while (i <= bltCnt && isBulletOut(blt[i].x, blt[i].y)) {
                blt[i] = blt[bltCnt--];
                blt[i].x += blt[i].dx;
                blt[i].y += blt[i].dy;
            }
            for (int j = 0; j <= 1; j++) {
                if (blt[i].x == p[j].x && blt[i].y == p[j].y) {
                    p[j].life -= 2;
                    blt[i--] = blt[bltCnt--];
                    break;
                }
            }
            i++;
        }
    }
}

/**
 * @brief judge whether a bullet is too far away from the boundary
 *
 * @param x x of the bullet
 * @param y y of the bullet
 * @return int 1 if it's too far 0 if it's not
 */
int Game::isBulletOut(int x, int y) {
    return (x < -5 || x > 25 || y < -5 || y > 25);
}

/**
 * @brief judge whether (x,y) is in the boundary
 *
 * @param x
 * @param y
 * @return int 0 if it's out and 1 if it's in
 */
int Game::isIn(int x, int y) {
    int boundaryL = getBoundMin(), boundaryR = getBoundMax();
    return (boundaryL <= x && x <= boundaryR && boundaryL <= y && y <= boundaryR);
}

/**
 * @brief print the game
 *
 */
void Game::print() {
    puts("");
    printf(GREEN "Life " RED "Player 1: %d" RESET ", " CYAN "Player 2: %d" RESET ", Turn: %d\n", p[0].life, p[1].life, turn);
    for (int i = -1; i <= 22; i++) {
        printf("%2d ", i);
        for (int j = -1; j <= 22; j++) {
            int boundaryL = getBoundMin(), boundaryR = getBoundMax();

            char ch = ' ';
            if (!(boundaryL <= i && i <= boundaryR && boundaryL <= j && j <= boundaryR)) {
                printf(YELLOW);
                ch = '-';
            }
            for (int k = 1; k <= bltCnt; k++) {
                if (blt[k].x == i && blt[k].y == j) {
                    ch = icon[blt[k].dir];
                    break;
                }
            }
            if (i == p[0].x && j == p[0].y && p[0].life > 0) {
                printf(RED);
                ch = icon[p[0].dir];
            }
            if (i == p[1].x && j == p[1].y && p[1].life > 0) {
                printf(CYAN);
                ch = icon[p[1].dir];
            }
            printf("%c" RESET "|", ch);
        }
        printf("\n");
    }
    // printf("Suggested move Player 1: %d Player 2: %d\n", bestAct(*this, 0, 4, p[0].life, p[1].life), bestAct(*this, 1, 4, p[1].life, p[0].life));
    printf("\n");
}

/**
 * @brief print the game in log
 *
 */
void Game::printLog() {
    FILE* fp = fopen(fileLog, "a");
    fprintf(fp, "\nLife Player 1: %d, Player 2: %d, Turn: %d\n", p[0].life, p[1].life, turn);
    for (int i = -1; i <= 22; i++) {
        fprintf(fp, "%2d ", i);
        for (int j = -1; j <= 22; j++) {
            int boundaryL = getBoundMin(), boundaryR = getBoundMax();

            char ch = ' ';
            if (!(boundaryL <= i && i <= boundaryR && boundaryL <= j && j <= boundaryR)) {
                ch = '-';
            }
            for (int k = 1; k <= bltCnt; k++) {
                if (blt[k].x == i && blt[k].y == j) {
                    ch = icon[blt[k].dir];
                    break;
                }
            }
            if (i == p[0].x && j == p[0].y && p[0].life > 0) {
                ch = icon[p[0].dir];
            }
            if (i == p[1].x && j == p[1].y && p[1].life > 0) {
                ch = icon[p[1].dir];
            }
            fprintf(fp, "%c|", ch);
        }
        fprintf(fp, "\n");
    }
    // printf("Suggested move Player 1: %d Player 2: %d\n", bestAct(*this, 0, 4, p[0].life, p[1].life), bestAct(*this, 1, 4, p[1].life, p[0].life));
    fprintf(fp, "\n");
    fclose(fp);
}

/**
 * @brief Get the Bound Min object
 *
 * @return int min boundary
 */
int Game::getBoundMin() {
    int size = 10 - turn / 16;
    size = size < 0 ? 0 : size;
    return 11 - size;
}

/**
 * @brief Get the Bound Max object
 *
 * @return int max boundary
 */
int Game::getBoundMax() {
    int size = 10 - turn / 16;
    size = size < 0 ? 0 : size;
    return 10 + size;
}

/**
 * @brief init a player
 *
 * @param x_
 * @param y_
 * @param life_
 * @param dx_
 * @param dy_
 * @param dir_
 * @param isTurned_ this variable can be used if a player cannot move after turning, but in this set of rule it's useless
 */
void Player::init(int x_, int y_, int life_, int dx_, int dy_, Direction dir_, int isTurned_) {
    x = x_;
    y = y_;
    life = life_;
    dir = dir_;
    dx = dx_;
    dy = dy_;
    isTurned = isTurned_;
}

/**
 * @brief update the player's dx and dy based on act
 *
 * @param act
 */
void Player::turn(int act) {
    if (act == 0) {
        return;
    }
    act = (act - 1) * 2 - 1;
    dir = (Direction)(((dir + act) % 4 + 4) % 4);
    dx = getDx(dir);
    dy = getDy(dir);
}

/**
 * @brief move this player
 *
 */
void Player::move() {
    x = x + dx;
    y = y + dy;
}

/**
 * @brief init a bullet
 *
 * @param x
 * @param y
 * @param dir
 * @param dx
 * @param dy
 */
void Bullet::init(int x_, int y_, Direction dir_, int dx_, int dy_) {
    x = x_;
    y = y_;
    dir = dir_;
    dx = dx_;
    dy = dy_;
}
