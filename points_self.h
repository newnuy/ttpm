#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/* user defined begin */
#define BASE_POINT              1000
#define WIN_BASE_POINT          30
#define WIN_STEP_POINT          10
#define FAIL_BASE_POINT         -20
#define FAIL_STEP_POINT         0
#define GIVE_UP_BASE_POINT      -60
#define LEVEL_NUM               4
#define DEFAULT_LEVEL           'C'
#define CUSTOM_SCORE            0
#define CUSTOM_BALLOT_LEVEL     1

#define PLAYERS_NUM_MAX         64
#define WEEK_NUM_MAX            64
#define PIC_HEIGHT              7
/* user defined end */


#define YES                     1
#define NO                      0
#define NAME_LEN_MAX            32
#define TEXT_LEN_MAX            256
#define RANDOM_LOOP             8
#define ALL_DATA_DIR_PATH       "./files"
#define PLAYERS_FILE_PATH       "./files/players"
#define PLAYERS_SWP_FILE_PATH   "./files/players.swp"
#define DATA_FILE_PATH          "./files/data"
#define DATA_FILE_SWP_PATH      "./files/data.swp"
#define WEEK_DATE_FILE_PATH     "./files/week_date"
#define WEEK_DATE_SWP_FILE_PATH "./files/week_date.swp"
#define BALLOT_FILE_PATH        "./files/ballot"
#define BALLOT_SWP_FILE_PATH    "./files/ballot.swp"
#define BACKUP_DIR_PATH_PRE     "./files_time/"
#define BACKUP_LIST_PATH        "./files_time/backup_list"

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

struct weekInfoStruct {
    struct playerInfo *p_playerInfo;
    struct oneGameInfo *p_oneGameInfoFirst;
    struct oneGameInfo *p_oneGameInfoLast;
    int winNum;
    int failNum;
    int point;
    double rate;
    double score;
    int rank;
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
    PRINT_TYPE_SOME_WEEKS,
    PRINT_TYPE_PLAYER,
};

/* function statement */
int addPlayer(struct playerInfo* p_playerInfo[], int *p_playerNum);
int ballot(struct playerInfo *p_playerInfo[], int playerNum);
int recordOneGameResult(struct playerInfo *p_playerInfo[], int playerNum);
int printInfo(struct playerInfo *p_playerInfo[], int playerNum);
int drawPlayer(struct playerInfo *p_playerInfo[], int playerNum);
int backupAndRestore(void);
int printBallotResult(struct playerInfo *p_playerInfo[],
        int playerNum, int *p_ballotArray, int lines, int cols);
int calcFromOneNewGameResult(struct playerInfo *p_playerInfo[],
        int playerNum, int oneGameResult[][3], int resultNum);
int addOneGameResult(struct playerInfo *p_playerInfo[], int playerNum,
        int oneGameResult[][3]);
int addOneGameResultFromBallotFile(struct playerInfo *p_playerInfo[],
        int playerNum, int oneGameResult[][3]);
void printOneGameResult(struct playerInfo *p_playerInfo[], int playerNum,
        int oneGameResult[][3], int resultNum);
void printPlayerName(struct playerInfo *p_playerInfo[], int playerNum);
void printAllPlayerName(struct playerInfo *p_playerInfo[], int playerNum);
void printPlayerInfoByType(struct playerInfo *p_playerInfo[], int playerNum,
        int type);
void printPlayerInfoTableHeadByType(int type);
void printPlayerInfoTableBodyByType(struct weekInfoStruct *p_weekInfo[],
        int actualPlayerNum, int type);
int drawOnePlayer(struct playerInfo *p_playerInfo[], int playerNum,
        int thisPlayerNum);
int drawPointPic(struct playerInfo *p_playerInfo, int yMin, int yMax, int yStep);
void backupData(void);
void restoreData(void);
int readPlayerInfo(struct playerInfo *p_playerInfo[]);
void writePlayerInfo(struct playerInfo *p_playerInfo[], int playerNum);
void freePlayerInfoStruct(struct playerInfo *p_playerInfo[], int playerNum);
int createWeeksPlayerInfoStruct(struct playerInfo *p_playerInfo[],
        int playerNum, struct weekInfoStruct *p_weekInfo[],
        int firstWeek, int lastWeek, int type);
void freeWeeksPlayerInfoStruct(struct weekInfoStruct *p_weekInfo[],
        int actualPlayerNum);
int getCurrentGameWeek(void);
int readWeekDate(int weekDate[][4]);
void writeWeekDate(int week, int year, int month, int day);
void printWeekDate(void);
void writeBallotResult(int oneGameResult[][3], int resultNum, int week);
int rankCmpFunction(const void *p1, const void *p2);
int oneGameRankCmpFunction(const void *p1, const void *p2);
int weekInfoDefaultSortCmpFunction(const void *p1, const void *p2);
int weekInfoPointSortCmpFunction(const void *p1, const void *p2);
int weekInfoRateSortCmpFunction(const void *p1, const void *p2);
int isThisWeekValid(int thisWeek, int startWeek, int stopWeek);
double defaultScore(int point, double rate);
double customScore(int point, double rate);
char customPrintBallotLevel(struct playerInfo *p_playerInfo[], int index);
