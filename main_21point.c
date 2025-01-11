#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
// #include "mainstruct.h"
// #include "genRandSeq.h"


unsigned int* genRandSeq(unsigned int seqlen);
// The functions below seem faster when generate random sequence
void shuffle(unsigned int *pSeq, unsigned int sortVal);
unsigned int* genShuffleSeq(unsigned int seqlen,unsigned int shuffleTime);

void getCard_or_Pass(unsigned int *playerdeck, unsigned int *playerturn, unsigned int playerdraw,int drawcard);

int multiPlayer();

int main()
{

    char multiplayer = 0;
    char continueplay = 0;

    while(1)
    {
        system("cls");
        printf("Enter \"S\" for single player, \"M\" for local multiplayer\nOther inputs will close the game\n");
        multiplayer=getch();
        if (multiplayer == 'S'|| multiplayer == 's' || multiplayer == 'M' || multiplayer == 'm')
        {
            // Game Mode
            switch (multiplayer)
            {
                case 'S':
                case 's':
                    break;

                case 'M':
                case 'm':
                printf("Start Multiplayer, Press Any Key to Continue\n");
                getch();
                system("cls");
                int totalresult[2]={0,0};
                do{
                    int result = multiPlayer();
                    if (result == 1)
                    {
                        totalresult[0]++;
                    }
                    else if (result == 2)
                    {
                        totalresult[1]++;
                    }
                    printf("\n\n");
                    printf("Player1 win count:%u\nPlayer2 win count:%u\n",totalresult[0],totalresult[1]);
                    printf("Press \"C\" to Continue, other inputs end current game\n");
                    continueplay=getch();
                }while(continueplay=='C' || continueplay=='c');
                break;

                default:
                    break;
            }
        }
        else
        {
            break;
        }
    }
    printf(" Press Any Key to Close the game\n");
    getch();
}

int multiPlayer()
{
    unsigned int seqlen=11;                          // 1-11 in the deck
    unsigned int* seq_addr=genShuffleSeq(seqlen,50); // Generate a random card sequence
    unsigned int player1_deck[seqlen];               // Player 1
    unsigned int player1_turn=0;
    char player1_pass_flag=0;
    memset(player1_deck,0,sizeof(player1_deck));
    unsigned int player2_deck[seqlen];               // Player 2
    unsigned int player2_turn=0;
    char player2_pass_flag=0;
    memset(player2_deck,0,sizeof(player2_deck));

    // Print Generated Sequence
    if(seqlen!=0)
    {
        for (int i=0;i<seqlen;i++)
            printf("%d ",seq_addr[i]);
        printf("\r\n ");
    }
    system("cls");
    unsigned int card_draw_cnt=0;

    // Player1's first Card;
    getCard_or_Pass(player1_deck, &player1_turn, seq_addr[card_draw_cnt],1);
    card_draw_cnt++;
    char player1_ready=0;
    do{
        printf("Player1's face-down card: %u\n",player1_deck[0]);
        printf("Enter \"C\" to continue, which will clear the screen\n");
        player1_ready=getch();
        system("cls");
    }while(player1_ready != 'C' && player1_ready != 'c');


    // Player2's first Card;
    getCard_or_Pass(player2_deck, &player2_turn, seq_addr[card_draw_cnt],1);
    card_draw_cnt++;
    char player2_ready=0;
    do{
        printf("Player2's face-down card: %u\n",player2_deck[0]);
        printf("Enter \"C\" to continue, which will clear the screen\n");
        player2_ready=getch();
        system("cls");
    }while(player2_ready != 'C' && player2_ready != 'c');
    
    // Start Draw Cards
    system("cls");
    printf("Player1's Deck: X, \nPlayer2's Deck: X, \n");
    char player2_last_pass = 0;
    do{
        // Player1's Turn
        printf("\n\n");
        if(card_draw_cnt>=seqlen)
        {
            player1_pass_flag=1;
        }
        else
        {
            char player1_draw=0;
            printf("Player1: Enter \"Y\" to draw a card, or other inputs to pass this turn\n");
            player1_draw=getch();
            if (player1_draw=='Y' || player1_draw=='y')
            {
                getCard_or_Pass(player1_deck, &player1_turn, seq_addr[card_draw_cnt],1);
                card_draw_cnt++;
                player1_pass_flag=0;
            }
            else
            {
                getCard_or_Pass(player1_deck, &player1_turn, seq_addr[card_draw_cnt],0);
                player1_pass_flag=1;
            }
        }
        // Print Result
        system("cls");
        printf("Player1's Deck: X, ");
        for(int k=1;k<player1_turn;k++)
        {
            printf("%u, ",player1_deck[k]);
        }
        printf("\n");
        printf("Player2's Deck: X, ");
        for(int k=1;k<player2_turn;k++)
        {
            printf("%u, ",player2_deck[k]);
        }

        // Player2's Turn
        if (player2_pass_flag !=1 || player1_pass_flag !=1)
        {
            printf("\n\n");
            if(card_draw_cnt>=seqlen)
            {
                player2_pass_flag=1;
            }
            else
            {
                char player2_draw=0;
                printf("Player2: Enter \"Y\" to draw a card, or other inputs to pass this turn\n");
                player2_draw=getch();
                if (player2_draw=='Y' || player2_draw=='y')
                {
                    getCard_or_Pass(player2_deck, &player2_turn, seq_addr[card_draw_cnt],1);
                    card_draw_cnt++;
                    player2_pass_flag=0;
                }
                else 
                {
                    getCard_or_Pass(player2_deck, &player2_turn, seq_addr[card_draw_cnt],0);
                    player2_pass_flag=1;
                }
            }
        }

        

        // Print Result
        system("cls");
        printf("Player1's Deck: X, ");
        for(int k=1;k<player1_turn;k++)
        {
            printf("%u, ",player1_deck[k]);
        }
        printf("\n");
        printf("Player2's Deck: X, ");
        for(int k=1;k<player2_turn;k++)
        {
            printf("%u, ",player2_deck[k]);
        }

    }while((player1_pass_flag == 0 || player2_pass_flag == 0) && card_draw_cnt<seqlen);


    // Game Complete
    unsigned int player1_result = 0;
    unsigned int player2_result = 0;
    system("cls");
    printf("The result is:\n");

    printf("Player1:");
    for(int k=0;k<player1_turn;k++)
    {
        player1_result=player1_result+player1_deck[k];
        printf("%u, ",player1_deck[k]);
    }
    printf("\n");
    printf("Player2:");
    for(int k=0;k<player2_turn;k++)
    {
        player2_result=player2_result+player2_deck[k];
        printf("%u, ",player2_deck[k]);
    }
    printf("\n");

    // One player goes beyond 21, that player loses
    if(player1_result <= 21 && player2_result > 21 )  
    {
        printf("Player1:%u Player2:%u\n",player1_result,player2_result);
        printf("The winner is Player1!\n");
        return 1; // 1 for player1 win
    }
    else if(player1_result > 21 && player2_result <= 21 )
    {
        printf("Player1:%u Player2:%u\n",player1_result,player2_result);
        printf("The winner is Player2!\n");
        return 2; // 2 for player2 win
    }
    // Both players go beyond 21, the smaller one wins
    else if(player1_result>21 && player2_result>21 && player1_result<player2_result)
    {
        printf("Player1:%u Player2:%u\n",player1_result,player2_result);
        printf("The winner is Player1!\n");
        return 1; 
    }
    else if(player1_result>21 && player2_result>21 && player1_result>player2_result)
    {
        printf("Player1:%u Player2:%u\n",player1_result,player2_result);
        printf("The winner is Player2!\n");
        return 2; 
    }
    // Both players are less than 21, the bigger one wins
    else if(player1_result<=21 && player2_result<=21 && player1_result>player2_result)
    {
        printf("Player1:%u Player2:%u\n",player1_result,player2_result);
        printf("The winner is Player1!\n");
        return 1; 
    }
    else if(player1_result<=21 && player2_result<=21 && player1_result<player2_result)
    {
        printf("Player1:%u Player2:%u\n",player1_result,player2_result);
        printf("The winner is Player2!\n");
        return 2; 
    }
    else //Should only be equal case
    {
        printf("Player1:%u Player2:%u\n",player1_result,player2_result);
        printf("It's a draw!");
        return 3;  // 3 for draw
    }
}


/*----------------Draw Card--------------*/
// if drawcard !=0 then add card "playerdraw" to "playerdeck" at "playerturn"'s location
void getCard_or_Pass(unsigned int *playerdeck, unsigned int *playerturn, unsigned int playerdraw,int drawcard)
{
    unsigned int tempturn=*playerturn;
    if (drawcard!=0)
    {
        playerdeck[tempturn]=playerdraw;
        tempturn++;
    }
    *playerturn=tempturn;
        
}
/*----------------Draw Card--------------*/



/*----------------Generate Random Sequence--------------*/
// generate random numbers and check if it's already available
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


/*----------------Generate Shuffled Sequence--------------*/
// use random shuffle value to shuffle a sequence
void shuffle(unsigned int *pSeq, unsigned int sortVal)
{
    unsigned int temp = pSeq[0]; // Store the left most val
    for (int i=0;i<sortVal;i++)
    {
        pSeq[i]=pSeq[i+1];  // LeftShift "sortVal" values;
    }
    pSeq[sortVal]=temp;
}


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