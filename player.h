#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    char *firstName;
    char *secondName;
    int points;
};

typedef struct Team
{
    int playerCount;
    char *teamName;
    struct Player *playerList;
    struct Team *next;
}Team;

typedef struct queueNode
{
    Team *team;
    struct queueNode *next;
}queueNode;

typedef struct Queue
{
    queueNode *front, *rear;
}Queue;

typedef struct stackNode
{
    Team *team;
    struct stackNode *next;
}stackNode;

typedef struct bstNode
{
    float teamPoints;
    char *teamName;
    struct bstNode *left, *right;
}bstNode;

typedef struct avlNode
{
    char *teamName;
    int height;
    float teamPoints;
    struct avlNode *left, *right;
}avlNode;

typedef struct sortedTeam
{
    float teamPoints;
    char *teamName;
    struct sortedTeam *next;
}sortedTeam;

void isFileOpen(FILE *);
struct Player createPlayer(char *, char *, int);
Team* initTeam();
Team* createTeam(Team *, int , char *, struct Player *);
Team* read(char *, float *);
void firstTaskPrint(Team *, char *);
void freeTeamList(Team **);
void freePlayerList(struct Player *, int );
Team* secondTask(Team *, float *);
int getTwoPowered(float );
Team* findMinPoints(Team *);
float calculatePoints(struct Player *, float );
void removeTeam(Team **, Team *);
Team* thirdTask(Team *, float, FILE *);
void showTeams(Team *, FILE *);
Queue* createQueue();
void addTeamsToQueue(Queue *, Team *);
void enQueue(Queue *, Team *);
int isQueueEmpty(Queue *);
Team* getTeamFromQueue(Queue *); 
void push(stackNode **, Team *);
int isStackEmpty(stackNode *);
void showRoundWinners(stackNode *, FILE *, int);
void addPointsToWinners(stackNode *);
Queue* addWinnersToQueue(stackNode *);
void deleteStack(stackNode **);
Team* copyTop8FromStack(stackNode *);
bstNode* createBST(Team *);
bstNode* insertInBST(bstNode *, float, char *);
bstNode* createBSTNode(float, char *);
void RightRootLeft(bstNode *, FILE *);
avlNode* createAVL(sortedTeam *);
avlNode* insertInAVL(avlNode *, char *, float);
avlNode* createAVLNode(char *, float);
int max(int , int);
int avlNodeHeight(avlNode *);
avlNode* rightRotation(avlNode *);
avlNode* leftRotation(avlNode *);
avlNode* LRRotation(avlNode *);
avlNode* RLRotation(avlNode *);
void task5Print(avlNode *, FILE *, int);
int getBalance(avlNode *);
void copyTop8FromTree(bstNode *, sortedTeam **);
sortedTeam* createSortedTeam(sortedTeam *, float, char *);
void freeSortedTeamList(sortedTeam **);
void freeBST(bstNode *);
void freeAVL(avlNode *);
void freeAll(Team *, Team *, sortedTeam *, bstNode *, avlNode *);

#endif