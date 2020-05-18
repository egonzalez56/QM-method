#include <stdio.h>

char buffer[500];
char mSubstring[100];
char dSubstring[100];

typedef struct reductionGroupHeadPtrs{
    struct matchGroups *groupHead;
    struct reductionGroupHeadPtrs *next;
    unsigned int totalMatchGroups;
} sREDUCTIONS;

typedef struct matchGroups{
    // int *matches;
    unsigned int totalMatchElements;
    unsigned int index;
    // short int checkmark;
    // char pattern[inputsRead];       // may need to be dynamic
    struct matchGroups *next;
    struct matchedElements *elemList;
} sMATCHGROUPS;

typedef struct matchedElements{
    int *element;
    char *pattern; // 01-1
    short int checkmark;
    struct matchedElements *next;
} sMATCHELEMS;

extern unsigned int inputsRead, mintermsRead, dontCaresRead, currGroup;
extern int *minterms, *dontCares, *allTerms;
extern sMATCHGROUPS **reductions;


void read_equation(void);
void print_exit_instrs(void);
void tokenize(void);
// void allocateMemory(void);
void freeMemory(void);
void getMinterms(void);
void getDontCares(void);
void combineTerms(void);
int countSetBits(int n);
void binToStr(unsigned int n, char *dest, unsigned int size);

void selectionSort(int array[], int length);
void swap(int array[], int first, int second);

sREDUCTIONS *createNewReduction(void);
sREDUCTIONS *addNewReduction(sREDUCTIONS *mainHeadPtr, sREDUCTIONS *newReduction);
sMATCHGROUPS *createNewMatchGroup(void);
void addNewMatchGroup(unsigned int reduction, sMATCHGROUPS *newMatchGroup, sREDUCTIONS *mainHeadPtr);

sMATCHELEMS *createNewElement(unsigned int iteration);





/*******************************************************/
/******* LEGACY STRUCTURES AND CODE - DO NOT USE *******/
/*******************************************************/
typedef struct groupHeadPtrs{
    struct groups *headPtr;
    struct groupHeadPtrs *next;
} sHEADPTRS;

typedef struct groups{
    unsigned int id;    // iteration id / reduction id

    struct matchIndex *matches;
    struct groups *next;
} sGROUPS;

typedef struct matchIndex{
    int *match;
    unsigned int totalMatches;
    short int checkmark;
    char *pattern;
    // struct mintPatterns *next;
} sMATCH;

sGROUPS *createGroup(void);
sGROUPS *addGroup(sGROUPS *groupListHead, sGROUPS *newItem);

