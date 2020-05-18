
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "qm.h"

unsigned int inputsRead = 0, mintermsRead = 0, dontCaresRead = 0, currGroup = 0, iters = 0;

int *minterms, *dontCares, *allTerms;

// sGROUPS *groupListHead = NULL, *travPtr;
sMATCHGROUPS **reductions;

sREDUCTIONS *mainHeadPtr = NULL, *newReduction;
sMATCHGROUPS *matchTravPtr, *newMatch, *prevMatch;
sMATCHELEMS *newElem, *elemTravPtr;


int main(int argc, char **argv)
{
    int i, setBits;
    // sHEADPTRS *newGroupHead;




    /* read number of inputs, minterms, don't cares from file */  
    read_equation();
    tokenize();
    getMinterms();
    getDontCares();
    combineTerms();


    reductions = malloc(sizeof(sMATCHGROUPS*) * inputsRead);
    for(i = 0 ; i < inputsRead ; i++)
    {
        reductions[i] = NULL;
    }



    // first iteration, group by set bits
    for(i = 0 ; i < mintermsRead ; i++)
    {
        setBits = countSetBits(minterms[i]);

        matchTravPtr = reductions[iters];

        while(matchTravPtr != NULL)
        {
            /* traverse to appropriate maching group */
            if(matchTravPtr->index == setBits)
            {
                /* found the appropriate group */
                elemTravPtr = matchTravPtr->elemList;
                while(elemTravPtr != NULL)
                {
                    /* traverse to end element list */
                    elemTravPtr = elemTravPtr->next;
                }
                elemTravPtr = createNewElement(iters);
                *(elemTravPtr->element) = minterms[i];
                binToStr(minterms[i], elemTravPtr->pattern, inputsRead);
                break;
            }
            else
            {
                matchTravPtr = matchTravPtr->next;
            }
        }

        /* not found */
        if(matchTravPtr == NULL)
        {
            newMatch = createNewMatchGroup();
            newMatch->index = setBits;
            newMatch->totalMatchElements++;
            

            matchTravPtr = reductions[iters];
            prevMatch = matchTravPtr;
            while(matchTravPtr != NULL)
            {
                if(newMatch->index < matchTravPtr->index)
                {
                    /* new match group needs to be inserted */
                    newMatch->next = matchTravPtr;
                    prevMatch->next = newMatch;
                    break;
                }
                
                prevMatch = matchTravPtr;
                matchTravPtr = matchTravPtr->next;
            }


        }

    }
    


    freeMemory();

    return 0;
}



