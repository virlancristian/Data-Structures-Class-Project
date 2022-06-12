#include "player.h"

void isFileOpen(FILE *file)
{
    if(file == NULL)
    {
        printf("Eroare in deschiderea fisierului");
        exit(1);
    }
}

struct Player createPlayer(char *firstName, char *secondName, int points)
{
    struct Player player;

    player.firstName = strdup(firstName);
    player.secondName = strdup(secondName);
    player.points = points;

    return player;
}

Team* initTeam()
{
    Team *team = (Team*) malloc(sizeof(Team));

    team->playerCount = 0;
    team->teamName = NULL;
    team->playerList = NULL;
    team->next = NULL;

    return team;
}

Team* createTeam(Team *firstTeam, int playerCount, char *teamName, struct Player *playerList)
{
    Team *newTeam = (Team*) malloc(sizeof(Team));
    
    newTeam->playerCount = playerCount;
    newTeam->teamName = strdup(teamName);
    newTeam->playerList = playerList;
    newTeam->next = firstTeam;
    firstTeam = newTeam;

    return firstTeam;
}

Team* read(char *inputPath, float *teamCount)
{
    FILE *inputFile;
    int playerCount, points;
    char teamName[100], firstName[100], secondName[100];
    struct Player *playerList;
    Team *firstTeam;

    inputFile = fopen(inputPath, "rt");
    isFileOpen(inputFile);
    firstTeam = initTeam();

    fscanf(inputFile, "%f", &*teamCount);
    for(int i = 0; i < *teamCount; i++)
    {
        fscanf(inputFile, "%d", &playerCount);
        fgets(teamName, 100, inputFile);
        teamName[strlen(teamName) - 1] = '\0';

        playerList = (struct Player*) calloc(playerCount, sizeof(struct Player));
        for(int j = 0; j < playerCount; j++)
        {
            fscanf(inputFile, "%s%s%d", firstName, secondName, &points);
            playerList[j] = createPlayer(firstName, secondName, points);
        }

        firstTeam = createTeam(firstTeam, playerCount, teamName, playerList);
        fgets(teamName, 100, inputFile);
    }

    fclose(inputFile);

    return firstTeam;
}

void firstTaskPrint(Team *firstTeam, char *inputPath)
{
    FILE *outputFile = fopen(inputPath, "w+");
    isFileOpen(outputFile);

    while(firstTeam->next != NULL)
    {
        fprintf(outputFile,"%s\n", firstTeam->teamName+1);
        firstTeam = firstTeam->next;
    }

    fclose(outputFile);
}

void freeTeamList(Team **firstTeam)
{
    Team *teamCopy;

    while((*firstTeam)->next != NULL)
    {
        free((*firstTeam)->teamName);
        freePlayerList((*firstTeam)->playerList, (*firstTeam)->playerCount);

        teamCopy = *firstTeam;
        *firstTeam = (*firstTeam)->next;
        free(teamCopy);
    }

    *firstTeam = NULL;
}

void freePlayerList(struct Player *playerList, int playerCount)
{
    for(int i = 0; i < playerCount; i++)
    {
        free(playerList[i].firstName);
        free(playerList[i].secondName);
    }
    free(playerList);
}

Team* secondTask(Team *firstTeam, float *teamCount)
{
    int twoPower;
    Team *keyTeam = (Team*) malloc(sizeof(Team));

    twoPower = getTwoPowered(*teamCount);

    while(*teamCount > twoPower)
    {
        keyTeam = findMinPoints(firstTeam);
        removeTeam(&firstTeam, keyTeam);
        (*teamCount)--;
    }

    return firstTeam;
}

int getTwoPowered(float target)
{
    int twoPower = 1;

    while(twoPower <= target){
        twoPower = twoPower * 2;
    }
    twoPower /= 2;

    return twoPower;
}

Team* findMinPoints(Team *firstTeam)
{
    Team *keyTeam;
    float minPoints, curentTeamPoints;
    
    keyTeam = firstTeam;
    minPoints = calculatePoints(firstTeam->playerList, firstTeam->playerCount);

    while(firstTeam->next != NULL)
    {
        curentTeamPoints = calculatePoints(firstTeam->playerList, firstTeam->playerCount);

        if(curentTeamPoints < minPoints)
        {
            minPoints = curentTeamPoints;
            keyTeam = firstTeam;
        }

        firstTeam = firstTeam->next;
    }

    return keyTeam;
}

float calculatePoints(struct Player *playerList, float playerCount)
{
    float sum = 0;

    for(int i = 0; i < playerCount; i++)
        sum += (float)playerList[i].points;

    return sum/playerCount;
}

void removeTeam(Team **firstTeam, Team *keyTeam)
{
    Team *aux, *firstTeamCopy;

    if(*firstTeam == keyTeam)
    {
        aux = *firstTeam;
        *firstTeam = (*firstTeam)->next;
        free(aux);
    }
    else
    {
        firstTeamCopy = *firstTeam;

        while(firstTeamCopy->next != keyTeam)
        {
            firstTeamCopy = firstTeamCopy->next;
        }

        aux = firstTeamCopy->next;
        firstTeamCopy->next = aux->next;
        free(aux);
    }
}

Team* thirdTask(Team *firstTeam, float teamCount, FILE *outputFile)
{
    Queue *q;
    Team *team1, *team2, *top8;
    stackNode *winners, *losers;
    int roundNumber = 1;
    float firsTeamPoints, secondTeamPoints;
    
    q = createQueue();

    showTeams(firstTeam, outputFile);
    addTeamsToQueue(q, firstTeam);

    while(teamCount > 1)
    {
        winners = NULL;
        losers = NULL;
        fprintf(outputFile, "--- ROUND NO:%d\n", roundNumber);
        
        while(!isQueueEmpty(q))
        {
            team1 = getTeamFromQueue(q);
            team2 = getTeamFromQueue(q);
            fprintf(outputFile, "%-33s-%33s\n", team1->teamName + 1, team2->teamName + 1);

            firsTeamPoints = calculatePoints(team1->playerList, team1->playerCount);
            secondTeamPoints = calculatePoints(team2->playerList, team2->playerCount);

            if(firsTeamPoints > secondTeamPoints)
            {
                push(&winners, team1);
                push(&losers, team2);
            }
            else
            {
                push(&winners, team2);
                push(&losers, team1);
            }
        }

        addPointsToWinners(winners);
        showRoundWinners(winners, outputFile, roundNumber);
        q = addWinnersToQueue(winners);

        if(teamCount == 16)
            top8 = copyTop8FromStack(winners);

        deleteStack(&winners);
        deleteStack(&losers);

        teamCount /= 2;
        roundNumber++;

        if(teamCount > 1)
            fprintf(outputFile, "\n");
    }

    return top8;
}

void showTeams(Team *firstTeam, FILE *outputFile)
{
    while(firstTeam->next != NULL)
    {
        fprintf(outputFile, "%s\n", firstTeam->teamName+1);
        firstTeam = firstTeam->next;
    }

    fprintf(outputFile, "\n");
}

Queue* createQueue()
{
    Queue *q = (Queue*) malloc(sizeof(Queue));

    if(q == NULL){
        return NULL;
    }
    
    q->front = q->rear = NULL;

    return q;
}

void addTeamsToQueue(Queue *q, Team *firstTeam)
{
    while(firstTeam->next != NULL)
    {
        firstTeam->teamName[strlen(firstTeam->teamName) - 1] = '\0';
        while(firstTeam->teamName[strlen(firstTeam->teamName) -1] == ' '){
            firstTeam->teamName[strlen(firstTeam->teamName) - 1] = '\0';
        }
        
        enQueue(q, firstTeam);
        firstTeam = firstTeam->next;
    }
}

void enQueue(Queue *q, Team *team)
{
    queueNode *newNode = (queueNode*) malloc(sizeof(queueNode));
    newNode->team = team;
    newNode->next = NULL;

    if(q->rear == NULL){
        q->rear = newNode;
    }
    else{
        (q->rear)->next = newNode;
        (q->rear) = newNode;
    }

    if(q->front == NULL){
        q->front = q->rear;
    }
}

int isQueueEmpty(Queue *q)
{
    return (q->front == NULL); 
}

Team* getTeamFromQueue(Queue *q)
{
    Team *team;
    queueNode *aux;

    team = (q->front)->team;
    aux = q->front;
    q->front = (q->front)->next;
    free(aux);

    return team; 
}

void push(stackNode **top, Team *team)
{
    stackNode *newNode = (stackNode*) malloc(sizeof(stackNode));

    newNode->team = team;
    newNode->next = *top;
    *top = newNode;
}

int isStackEmpty(stackNode *top)
{
    return (top == NULL);
}

void showRoundWinners(stackNode *top, FILE *outputFile, int roundNumber)
{
    float teamPoints;

    fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", roundNumber);

    while(!isStackEmpty(top))
    {
        teamPoints = calculatePoints(top->team->playerList, top->team->playerCount);
        fprintf(outputFile, "%-34s-  %.2f\n", top->team->teamName+1, teamPoints);

        top = top->next;
    }
}

void addPointsToWinners(stackNode *top)
{
    while(!isStackEmpty(top))
    {
        for(int i = 0; i < top->team->playerCount; i++)
            top->team->playerList[i].points++;

        top = top->next;
    }
}

Queue* addWinnersToQueue(stackNode *top)
{
    Queue *q = createQueue();

    while(!isStackEmpty(top))
    {
        enQueue(q, top->team);
        top = top->next;
    }

    return q;
}

void deleteStack(stackNode **top)
{
    stackNode *temp;

    while(!isStackEmpty(*top))
    {
        temp = *top;
        *top = (*top)->next;

        free(temp);
    }
}

Team* copyTop8FromStack(stackNode *top)
{
    Team* newTeam = initTeam();
    struct Player *playerList;

    while(!isStackEmpty(top))
    {
        playerList = (struct Player*) calloc(top->team->playerCount, sizeof(struct Player));
        for(int i = 0; i < top->team->playerCount; i++)
            playerList[i] = top->team->playerList[i];

        newTeam = createTeam(newTeam, top->team->playerCount, top->team->teamName, playerList);
        top = top->next;
    }

    return newTeam;
}

bstNode* createBST(Team *firstTeam)
{
    bstNode *root = NULL;
    float teamPoints;

    while(firstTeam->next != NULL)
    {
        teamPoints = calculatePoints(firstTeam->playerList, firstTeam->playerCount);

        root = insertInBST(root, teamPoints, firstTeam->teamName);

        firstTeam = firstTeam->next;
    }

    return root;
}

bstNode* insertInBST(bstNode *node, float teamPoints, char *teamName)
{
    if(node == NULL)
        return createBSTNode(teamPoints, teamName);

    if(teamPoints < node->teamPoints)
        node->left = insertInBST(node->left, teamPoints, teamName);
    else if(teamPoints > node->teamPoints)
        node->right = insertInBST(node->right, teamPoints, teamName);
    else if(teamPoints == node->teamPoints){
        if(strcmp(teamName, node->teamName) < 0)
            node->left = insertInBST(node->left, teamPoints, teamName);
        else
            node->right = insertInBST(node->right, teamPoints, teamName);
    }

    return node;
}

bstNode* createBSTNode(float teamPoints, char *teamName)
{
    bstNode *newNode = (bstNode*) malloc(sizeof(bstNode));

    newNode->teamPoints = teamPoints;
    newNode->teamName = strdup(teamName);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void RightRootLeft(bstNode *node, FILE *outputFile)
{
    if(node == NULL)
        return;
    
    RightRootLeft(node->right, outputFile);
    fprintf(outputFile, "%-34s-  %.2f\n", node->teamName + 1, node->teamPoints);
    RightRootLeft(node->left, outputFile);
}

avlNode* createAVL(sortedTeam *firstTeam)
{
    avlNode *root = NULL;
    int array_index = 7;
    float decreasingFactor;

    while(firstTeam != NULL)
    {
        sortedTeam *temp = firstTeam;
        decreasingFactor = 0.01;

        while(temp != NULL)
        {
            if(firstTeam->teamPoints = temp->teamPoints)
            {
                temp->teamPoints = temp->teamPoints - decreasingFactor;
                decreasingFactor = decreasingFactor + 0.01;

                temp = temp->next;
            }
        }

        root = insertInAVL(root, firstTeam->teamName, firstTeam->teamPoints);
        firstTeam = firstTeam->next;
        array_index--;
    }

    return root;
}

int avlNodeHeight(avlNode *node)
{
    if(node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

avlNode* createAVLNode(char *teamName, float teamPoints)
{
    avlNode* newNode = (avlNode*) malloc(sizeof(avlNode));

    newNode->teamName = strdup(teamName);
    newNode->teamPoints = teamPoints;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

avlNode* rightRotation(avlNode *y)
{
    avlNode *x = y->left;
    avlNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(avlNodeHeight(y->left), avlNodeHeight(y->right)) + 1;
    x->height = max(avlNodeHeight(x->left), avlNodeHeight(x->right)) + 1;

    return x;
}

avlNode* leftRotation(avlNode *x)
{
    avlNode *y = x->right;
    avlNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(avlNodeHeight(x->left), avlNodeHeight(x->right)) + 1;
    y->height = max(avlNodeHeight(y->left), avlNodeHeight(y->right)) + 1;

    return y;
}

int getBalance(avlNode *node)
{
    if(node == NULL)
        return 0;
    return avlNodeHeight(node->left) - avlNodeHeight(node->right);
}

avlNode* insertInAVL(avlNode *node, char *teamName, float teamPoints)
{
    if(node == NULL)
        return createAVLNode(teamName, teamPoints);

    if(teamPoints < node->teamPoints)
        node->left = insertInAVL(node->left, teamName, teamPoints);
    else if(teamPoints > node->teamPoints)
        node->right = insertInAVL(node->right, teamName, teamPoints);
    else
        return node;

    node->height = 1 + max(avlNodeHeight(node->left), avlNodeHeight(node->right));

    int balance = getBalance(node);

    if(balance > 1 && teamPoints < node->left->teamPoints)
        return rightRotation(node);

    if(balance < -1 && teamPoints > node->right->teamPoints)
        return leftRotation(node);

    if(balance > 1 && teamPoints > node->left->teamPoints)
    {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    if(balance < -1 && teamPoints < node->right->teamPoints)
    {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}

void task5Print(avlNode *node, FILE *outputFile, int height)
{
    if(node)
    {
        task5Print(node->right, outputFile, height + 1);
        task5Print(node->left, outputFile, height + 1);
        if(height == 2)
            fprintf(outputFile, "%s\n", node->teamName + 1);
    }
}

void copyTop8FromTree(bstNode *node, sortedTeam **head)
{
    if(node != NULL)
    {
        copyTop8FromTree(node->left, &*head);
        *head = createSortedTeam(*head, node->teamPoints, node->teamName);
        copyTop8FromTree(node->right, &*head);   
    }
}

sortedTeam* createSortedTeam(sortedTeam *team, float teamPoints, char *teamName)
{
    sortedTeam *newTeam = (sortedTeam*) malloc(sizeof(sortedTeam));

    newTeam->teamPoints = teamPoints;
    newTeam->teamName = strdup(teamName);
    newTeam->next = team;
    team = newTeam;

    return team;
}

void freeSortedTeamList(sortedTeam **head)
{
    sortedTeam *temp;

    while((*head) != NULL)
    {
        temp = *head;
        (*head) = (*head)->next;

        free(temp->teamName);
        free(temp);
    }

    *head = NULL;
}

void freeBST(bstNode *node)
{
    if(node)
    {
        freeBST(node->left);
        freeBST(node->right);

        free(node->teamName);
        free(node);
        node = NULL;
    }
}

void freeAVL(avlNode *node)
{
    if(node)
    {
        freeAVL(node->left);
        freeAVL(node->right);

        free(node->teamName);
        free(node);
        node = NULL;
    }
}

void freeAll(Team *firstTeam, Team *top8, sortedTeam *sortedTop8, bstNode *bstRoot, avlNode *avlRoot)
{
    freeTeamList(&firstTeam);
    if(top8)
        freeTeamList(&top8);
    if(sortedTop8)
        freeSortedTeamList(&sortedTop8);
    if(bstRoot)
        freeBST(bstRoot);
    if(avlRoot)
        freeAVL(avlRoot);
}