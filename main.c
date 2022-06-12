#include "player.h"

int main(int argc, char *argv[])
{
    FILE *taskInputFile, *outputFile;
    int tasks[5];
    float teamCount;
    Team *firstTeam, *top8 = NULL;
    bstNode *bstRoot = NULL;
    avlNode *avlRoot = NULL;
    sortedTeam *sortedTop8 = NULL;

    taskInputFile = fopen(argv[1], "rt");
    isFileOpen(taskInputFile);

    fscanf(taskInputFile, "%d%d%d%d%d", &tasks[0], &tasks[1], &tasks[2], &tasks[3], &tasks[4]);

    fclose(taskInputFile);

    firstTeam = read(argv[2], &teamCount);

    if(tasks[0] == 1)
    {
        firstTaskPrint(firstTeam, argv[3]);
    }

    if(tasks[1] == 1)
    {
        firstTeam = secondTask(firstTeam, &teamCount);
        firstTaskPrint(firstTeam, argv[3]);
    }

    if(tasks[2] == 1)
    {
        outputFile = fopen(argv[3], "w+");
        isFileOpen(outputFile);

        top8 = thirdTask(firstTeam, teamCount, outputFile);
    }

    if(tasks[3] == 1)
    {
        bstRoot = createBST(top8);

        fprintf(outputFile, "\nTOP 8 TEAMS:\n");
        RightRootLeft(bstRoot, outputFile);

        sortedTop8 = NULL;
        copyTop8FromTree(bstRoot, &sortedTop8);
    }

    if(tasks[4] == 1)
    {
        avlRoot = createAVL(sortedTop8);

        fprintf(outputFile, "\nTHE LEVEL 2 TEAMS ARE:\n");
        task5Print(avlRoot, outputFile, 0);
    }

    if(outputFile)
        fclose(outputFile);
    freeAll(firstTeam, top8, sortedTop8, bstRoot, avlRoot);

    return 0;
}