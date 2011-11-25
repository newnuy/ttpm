#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/* user defined begin */
#define WIN_BASE_POINT          3
#define WIN_STEP_POINT          1
#define FAIL_BASE_POINT         1
#define GIVE_UP_BASE_POINT      -3
#define LEVEL_NUM               4
#define DEFAULT_LEVEL           'C'
#define CUSTOM_SCORE            1
#define CUSTOM_BALLOT_LEVEL     1
/* user defined end */

#define YES                     1
#define NO                      0
#define NAME_LEN_MAX            32
#define TEXT_LEN_MAX            32
#define PLAYERS_NUM_MAX         64
#define RANDOM_LOOP             8
#define PLAYERS_FILE_PATH       "./files/players"
#define PLAYERS_SWP_FILE_PATH   "./files/players.swp"
#define DATA_FILE_PATH          "./files/data"
#define DATA_FILE_SWP_PATH      "./files/data.swp"
#define WEEK_DATE_FILE_PATH     "./files/week_date"
#define WEEK_DATE_SWP_FILE_PATH "./files/week_date.swp"
#define BALLOT_FILE_PATH        "./files/ballot"
#define BALLOT_SWP_FILE_PATH    "./files/ballot.swp"

struct oneGameInfo {
    int week;
    char levelBefore;
    int winNum;
    int failNum;
    int pointBefore;
    int point;
    double rateBefore;
    int rankBefore;
    int rank;
    struct oneGameInfo *next;
};

struct playerInfo {
    int num;
    int startWeek;
    int stopWeek;
    char name[NAME_LEN_MAX];
    char sex;
    char level;
    char iceLevel;
    int winNum;
    int failNum;
    int point;
    double rate;
    int rank;
    int lastWeek;
    int weekNum;
    struct oneGameInfo *p_oneGameInfo;
};

struct calcRankStruct {
    double score;
    struct playerInfo *p_playerInfo;
};

struct calcOneGameRankStruct {
    double score;
    struct oneGameInfo *p_oneGameInfo;
};

enum printType {
    PRINT_TYPE_CURRENT,
    PRINT_TYPE_CURRENT_WEEK,
    PRINT_TYPE_WEEK,
    PRINT_TYPE_MONTH,
    PRINT_TYPE_SEASON,
    PRINT_TYPE_PLAYER,
};

/* function statement */
int addPlayer(struct playerInfo* p_playerInfo[], int *p_playerNum);
int ballot(struct playerInfo *p_playerInfo[], int playerNum);
int recordOneGameResult(struct playerInfo *p_playerInfo[], int playerNum);
int printInfo(struct playerInfo *p_playerInfo[], int playerNum);
int printBallotResult(struct playerInfo *p_playerInfo[],
        int playerNum, int *p_ballotArray, int lines, int cols);
int calcFromOneNewGameResult(struct playerInfo *p_playerInfo[],
        int playerNum, int oneGameResult[][3], int resultNum);
int addOneGameResult(struct playerInfo *p_playerInfo[], int playerNum,
        int oneGameResult[][3]);
int addOneGameResultFromBallotFile(struct playerInfo *p_playerInfo[],
        int playerNum, int oneGameResult[][3]);
int editOneGameResult(void);
void printPlayerName(struct playerInfo *p_playerInfo[], int playerNum);
void printAllPlayerName(struct playerInfo *p_playerInfo[], int playerNum);
void printAllPlayerMainInfo(struct playerInfo *p_playerInfo[], int playerNum);
void printPlayerInfoByType(struct playerInfo *p_playerInfo[], int playerNum,
        int type);
int readPlayerInfo(struct playerInfo *p_playerInfo[]);
void writePlayerInfo(struct playerInfo *p_playerInfo[], int playerNum);
void freePlayerInfoStruct(struct playerInfo *p_playerInfo[], int playerNum);
int createActualPlayerInfoPointArray(struct playerInfo *p_playerInfo[],
        int playerNum, struct playerInfo *p_actualPlayerInfo[],
        int firstWeek, int lastWeek);
int getCurrentGameWeek(void);
int rankCmpFunction(const void *p1, const void *p2);
int oneGameRankCmpFunction(const void *p1, const void *p2);
int currentInfoDefaultSortCmpFunction(const void *p1, const void *p2);
int currentInfoPointSortCmpFunction(const void *p1, const void *p2);
int currentInfoRateSortCmpFunction(const void *p1, const void *p2);
int isThisWeekValid(int thisWeek, int startWeek, int stopWeek);
void swapTwoIntNum(int *i, int *j);
double defaultScore(int point, double rate);
double customScore(int point, double rate);
char customPrintBallotLevel(struct playerInfo *p_playerInfo[], int index);
