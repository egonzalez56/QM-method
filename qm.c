#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qm.h"

sGROUPS first;

void read_equation(void)
{
    FILE *eqFile;

    if((eqFile = fopen("equation.txt", "r")) == NULL)
    {
        printf("Failed to open file: equation.txt\n");
    }
    else
    {
        // read the equation from the file
        fscanf(eqFile, "%[^\n]", buffer);
        printf("%s\n", buffer);
    }

    fclose(eqFile);

    return;
}

void print_exit_instrs(void)
{
    printf("Please look at the formatting/structure of the input function.\n");
    printf("Make sure to follow the suggestions outlined in the readme on how to write the function.\n");
}

void tokenize(void)
{
    char *funcPtr, *mintermPtr, *dontCarePtr, *tokenPtr;
    char *inputs, *minterms, *dontCares, *temp, *subString;

    char func = 'F';
    char min = 'M';
    char dc = 'D';
    // char open = '(';
    // char close = ')';
    // char comma = ',';

    funcPtr = strchr(buffer, func);
    mintermPtr = strchr(buffer, min);
    dontCarePtr = strchr(buffer, dc);

    if(funcPtr != NULL)
    {
        tokenPtr = strtok(buffer, "(");
        tokenPtr = strtok(NULL, ")");

        temp = strtok(tokenPtr, ",");
        while(temp != NULL)
        {
            inputsRead++;
            temp = strtok(NULL, ",");
        }

        printf("Total inputs read = %d\n", inputsRead);
    }
    else
    {
        printf("Unable to read function inputs\n");
        print_exit_instrs();
        exit(0);
    }

    if(mintermPtr != NULL)
    {
        tokenPtr = strtok(mintermPtr, "(");
        tokenPtr = strtok(NULL, ")");

        // save substing for extracting minterms
        strcpy(mSubstring, tokenPtr);

        temp = strtok(tokenPtr, ",");
        while(temp != NULL)
        {
            mintermsRead++;
            temp = strtok(NULL, ",");
        }

        printf("Total minterms read = %d\n", mintermsRead);
    }
    else
    {
        printf("Unable to read function's minterms\n");
        print_exit_instrs();
        exit(0);
    }

    if(dontCarePtr != NULL)
    {
        tokenPtr = strtok(dontCarePtr, "(");
        tokenPtr = strtok(NULL, ")");

        // save substring for extracting don't cares
        strcpy(dSubstring, tokenPtr);

        temp = strtok(tokenPtr, ",");
        while(temp != NULL)
        {
            dontCaresRead++;
            temp = strtok(NULL, ",");
        }

        printf("Total dont cares read = %d\n", dontCaresRead);
    }
    else
    {
        printf("No don't cares read\n");
        dontCares = NULL;
    }

     return;
}

void getMinterms(void)
{
    char *tokenPtr, *ptr;
    int i = 0;

    // read_equation();
    minterms = malloc(sizeof(int) * mintermsRead);

    tokenPtr = strtok(mSubstring, ",");

    while(tokenPtr != NULL)
    {
        minterms[i++] = strtol(tokenPtr, &ptr, 0);
        tokenPtr = strtok(NULL, ",");
    }

    return;
}

void getDontCares(void)
{
    char *tokenPtr, *ptr;
    int i = 0;

    if(dontCaresRead == 0)
    {
        return; // no don't cares in equation
    }
    else
    {
        dontCares = malloc(sizeof(int) * dontCaresRead);

        tokenPtr = strtok(dSubstring, ",");
        
        while(tokenPtr != NULL)
        {
            dontCares[i++] = strtol(tokenPtr, &ptr, 0);
            tokenPtr = strtok(NULL, ",");
        }
    }
    
}

void combineTerms(void)
{
    int i;
    int totalTerms = mintermsRead + dontCaresRead;

    allTerms = malloc(sizeof(int) * totalTerms);

    for(i = 0 ; i < totalTerms ; i++)
    {

    }
    // copy minterms first
    for(i = 0 ; i < mintermsRead ; i++)
    {
        allTerms[i] = minterms[i];
    }
    // then copy dont cares
    for(i = 0 ; i < dontCaresRead ; i++)
    {
        allTerms[mintermsRead + i] = dontCares[i];
    }

    // sort the terms using selection sort algorithm
    selectionSort(allTerms, totalTerms);

    return;
}

int countSetBits(int n)
{
    int setBits;

    for(setBits = 0 ; n ; setBits++)
    {
        n = n & (n - 1);
    }

    return setBits;
}


sMATCHGROUPS *createNewMatchGroup(void)
{
    sMATCHGROUPS *newMatchGroup = malloc(sizeof(sMATCHGROUPS));
    // newMatchGroup->checkmark = 0;
    // newMatchGroup->matches = NULL;
    newMatchGroup->next = NULL;
    newMatchGroup->totalMatchElements = 0;
    newMatchGroup->elemList = NULL;
    return newMatchGroup;
}

sMATCHELEMS *createNewElement(unsigned int iteration)
{
    sMATCHELEMS *newElement = malloc(sizeof(sMATCHELEMS));
    newElement->checkmark = 0;
    newElement->element = malloc(sizeof(int) * (1 << iteration));
    newElement->pattern = malloc(sizeof(char) * inputsRead);
    newElement->next = NULL;

    return newElement;
}

// void addNewMatchGroup(unsigned int reduction, sMATCHGROUPS *newMatchGroup)
// {

// }

// void addNewMatchGroup(unsigned int reduction, sMATCHGROUPS *newMatchGroup, sREDUCTIONS *mainHeadPtr)
// {
//     int i = 0;
//     sREDUCTIONS *travPtr;
//     sMATCHGROUPS *groupTravPtr;

//     travPtr = mainHeadPtr;

//     while((i < reduction) && (travPtr->next != NULL))
//     {
//         travPtr = travPtr->next;
//         i++;
//     }

//     groupTravPtr = travPtr->groupHead;

//     /* group is empty */
//     if(groupTravPtr == NULL)
//     {
//         groupTravPtr = newMatchGroup;
//         // newMatchGroup->checkmark = 0;
//         // newMatchGroup->matches = NULL;
//         newMatchGroup->next = NULL;
//         // newMatchGroup->totalMatchElements = 0;
//     }
//     else
//     {
//         /* traverse the non-empty group list */
//         while(groupTravPtr->next != NULL)
//         {
//             groupTravPtr = groupTravPtr->next;
//         }

//         groupTravPtr = newMatchGroup;
//         // newMatchGroup->checkmark = 0;
//         // newMatchGroup->matches = NULL;
//         newMatchGroup->next = NULL;
//         // newMatchGroup->totalMatchElements = 0;
//     }

//     // add one new group to counter
//     travPtr->totalMatchGroups++;
    
// }

// void addElement(unsigned int reduction, unsigned int position, sREDUCTIONS *mainHeadPtr, sMATCHELEMS *newElement)//sMATCHGROUPS *currentGroup)
// {
//     int i;
//     sREDUCTIONS *travPtr;
//     sMATCHGROUPS *currGroup;
//     sMATCHELEMS *elemTravPtr;

//     travPtr = mainHeadPtr;

//     for(i = 0 ; i < reduction ; i++)
//     {
//         travPtr = travPtr->next;
//     }

//     currGroup = travPtr->groupHead;

//     if(position < travPtr->totalMatchGroups)
//     {
//         while(currGroup->index < position)
//         {
//             currGroup = currGroup->next;
//         }
        
//         elemTravPtr = currGroup->elemListHead;
//         while(elemTravPtr->next != NULL)
//         {
//             elemTravPtr = elemTravPtr->next;
//         }

//         elemTravPtr->next = newElement;
//         newElement->checkmark = 0;
//         newElement->pattern = malloc(sizeof(char) * inputsRead);
//         newElement->element = malloc(sizeof(int) * (1 << reduction));
//         newElement->next = NULL;
//     }
//     else
//     {
//         while((position < currGroup->index) || (currGroup != NULL))
//         {
//             // do something, continue here
//         }
//     }
//     // while(travPtr->groupHead->next != NULL)


//     // CONTINUE THIS
//     // for(i = 0 ; )
// }

// void populateElement(unsigned int reduction, sREDUCTIONS *mainHeadPtr, sMATCHELEMS)
// {

// }


void binToStr(unsigned int n, char *dest, unsigned int size)
{
    unsigned int i;

    for(i = size ; n > 0 ; i--)
    {
        dest[i] = n % 2;
        n = n / 2;
    }

    printf("Binary value is %s\n", dest);

    // for(i = 0 ; i < size ; i++)
    // {
    //     printf("Binary value is %s\n")
    // }

    return;
}

// void freeAll(sREDUCTIONS *mainHeadPtr)
// {
//     sMATCHGROUPS gTravPtr, gPrevPtr;
//     sREDUCTIONS rTravPtr, rPrevPtr;
//     sMATCHELEMS eTravPtr, ePrevPtr;
//     // mainHeadPtr->groupHead, next;
//     rTravPtr = mainHeadPtr;
//     // gTravPtr = mainHeadPtr->groupHead;

//     /* free all groups within reduction */
//     while(rTravPtr != NULL)
//     {
//         rPrevPtr = rTravPTr;
//         rTravPtr = rTravPtr->next;

//         gTravPtr = rPrevPtr->groupHead;

//         while(gTravPtr != NULL)
//         {
//             gPrevPtr = gTravPtr;
//             gTravPtr = gTravPtr->next;

//             eTravPtr = gPrevPtr->elemListHead;

//             while(eTravPtr != NULL)
//             {
//                 ePrevPtr = eTravPtr;
//                 eTravPtr = eTravPtr->next;
//                 free(ePrevPtr);
//             }

//             // gPrevPtr = gTravPtr;
//             // gTravPtr = gTravPtr->next;
//             free(gPrevPtr);
//         }

//         free(rPrevPtr);
//     }

//     free(minterms);
    
//     if(dontCares != NULL)
//     {
//         free(dontCares);
//     }
// }




// freeGroupsList(sGROUP *groupListHead)
// {
//     sGROUP *prevPtr, *travPtr;

//     travPtr = groupListHead;
//     // prevPtr = groupListHead;

//     while(travPtr != NULL)
//     {
//         prevPtr = travPtr;
//         travPtr = travPtr->next;
//         free(prevPtr);
//     }

// }


void freeMemory(void)
{
    free(minterms);
    free(dontCares);
}

void selectionSort(int array[], int length)
{
    int smallest;
    int i, j;

    for(i = 0 ; i < (length - 1) ; i++)
    {
        smallest = i;

        for(j = i + 1 ; j < length ; j++)
        {
            if(array[j] < array[smallest])
            {
                smallest = j;
            }

            swap(array, i, smallest);
        }
    }
    return;
}

void swap(int array[], int first, int second)
{
    int temp;
    temp = array[first];
    array[first] = array[second];
    array[second] = temp;
    return;
}