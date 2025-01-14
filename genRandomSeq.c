#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

void shuffle(unsigned int *pSeq, unsigned int sortVal);

/*--------------------------------------
* Function: genRandSeq
* Description: Generate Random Sequence using generate random number and check is availability.
* Input: unsigned int seqlen: Number of non-repeated value to generate, 
* Output: unsigned int*: Random Sequence array pointer
--------------------------------------*/
unsigned int* genRandSeq(unsigned int seqlen)
{
    unsigned int* randomseq = (unsigned int*)malloc(seqlen * sizeof(unsigned int));
    if (seqlen!=0)
    {
        srand((unsigned)time(NULL));

        memset(randomseq,0,sizeof(randomseq));
        unsigned int i,j,cnt=0;
        unsigned int temp_randnum=0;
        for (i=0;i<seqlen;i++)
        {
            do{
                temp_randnum = rand() % seqlen;
                for (j=0;j<cnt;j++)
                {
                    if(randomseq[j] == temp_randnum)
                        break;
                }
            }while(j<cnt);
            randomseq[cnt++]=temp_randnum;
        }
        for (i=0;i<seqlen;i++)
        {
            randomseq[i]=randomseq[i]+1;
        }
        return randomseq;
    }
    else
    {
        return NULL;
    }
} 
/*----------------Generate Random Sequence--------------*/


/*--------------------------------------
* Function: shuffle
* Description: Using shuffle-card like method to disorganize a sequence
* Input: 
unsigned int *pSeq: Pointer for a ordered sequence
unsigned int sortVal: Position for this card to be shuffled in
* Output: unsigned int *pSeq: Shuffled sequence pointer
--------------------------------------*/
void shuffle(unsigned int *pSeq, unsigned int sortVal)
{
    unsigned int temp = pSeq[0]; // Store the left most val
    for (int i=0;i<sortVal;i++)
    {
        pSeq[i]=pSeq[i+1];  // LeftShift "sortVal" values;
    }
    pSeq[sortVal]=temp;
}

/*--------------------------------------
* Function: genShuffleSeq
* Description: Generate Random Sequence using shuffle-card like method
* Input: 
unsigned int seqlen: Number of non-repeated value to generate, 
unsigned int shuffleTime: Times to shuffle the card
* Output: unsigned int*: Random Sequence array pointer
--------------------------------------*/
unsigned int* genShuffleSeq(unsigned int seqlen,unsigned int shuffleTime)
{
    unsigned int* randomseq = (unsigned int*)malloc(seqlen * sizeof(unsigned int));
    if (seqlen!=0)
    {
        srand((unsigned)time(NULL));
        for(int i=0;i<seqlen;i++)
        {
            randomseq[i]=i+1; // Generate a ordered sequence
        }

        unsigned int sortVal=0;
        for (int i=0;i<shuffleTime;i++)
        {
            sortVal=rand() % seqlen;
            shuffle(randomseq,sortVal);
        }

        return randomseq;
    }
    else
    {
        return NULL;
    }
} 
/*----------------Generate Shuffled Sequence--------------*/