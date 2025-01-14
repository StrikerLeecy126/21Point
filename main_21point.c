#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "mainfunctions.h"


unsigned int* genRandSeq(unsigned int seqlen);
// The functions below seem faster when generate random sequence
void shuffle(unsigned int *pSeq, unsigned int sortVal);
unsigned int* genShuffleSeq(unsigned int seqlen,unsigned int shuffleTime);

void getCard_or_Pass(unsigned int *playerdeck, unsigned int *playerturn, unsigned int playerdraw,int drawcard);

int multiPlayer();
int singlePlayer(int aggre);

int main()
{

    char multiplayer = 0;   // Is multiplayer?
    char continueplay = 0;  // Will continue current mode?
    unsigned int aggre = 0; // AI aggressiveness
    char change_aggre_flg = 0; // Will change AI aggressiveness?
    char changed_aggre_flg = 0; // Changed Aggressiveness?

    while(1)
    {
        system("cls");
        printf("Enter \"S\" for single player, \"M\" for local multiplayer\nOther inputs will close the game\n");
        multiplayer=getch();
        if (multiplayer == 'S'|| multiplayer == 's' || multiplayer == 'M' || multiplayer == 'm')
        {
            // Game Mode
            int totalresult[2]={0,0};
            switch (multiplayer)
            {
                case 'S':
                case 's':
                do{
                    system("cls");
                    printf("Start SinglePlayer, Press \"A\" to change AI's aggressiveness.\nPress other Keys to Continue\n");
                    change_aggre_flg=getch();
                    system("cls");
                    // Set Aggressiveness
                    if(change_aggre_flg == 'A' || change_aggre_flg == 'a')
                    {
                        printf("Input AI's aggressiveness:\n1:More Conservative\n2:Less Conservative\n");
                        printf("3:Balanced (Default)\n4:Less Aggressive\n5:More Aggressive\n");
                        scanf("%u",&aggre);     // Input Aggressiveness
                        if (aggre<1 || aggre>5) // Value between 1 to 5
                        {
                            printf("Aggressiveness out of range, setting to default\n");
                            aggre = 3;
                        }
                        changed_aggre_flg=1; 
                        printf("AI's aggressiveness set to: %u\nPress Any Key to Continue\n",aggre);
                        getch();
                        system("cls");
                    }
                }while(change_aggre_flg == 'A' || change_aggre_flg == 'a');

                if (changed_aggre_flg == 0) // Did not change Aggressiveness
                {
                    aggre = 3;
                    printf("AI's aggressiveness set default\nPress Any Key to Continue\n");
                    getch();
                    system("cls");
                }

                memset(totalresult,0,sizeof(totalresult));

                int aggressiveness; // + Conservative, - Aggressive
                switch (aggre)
                {
                    case 1:
                        aggressiveness=200;
                        break;
                    case 2:
                        aggressiveness=100;
                        break;
                    case 3:
                        aggressiveness=0;
                        break;
                    case 4:
                        aggressiveness=-100;
                        break;
                    case 5:
                        aggressiveness=-200;
                        break;
                    default:
                        aggressiveness=0;
                        break;                                                   
                }


                do{
                    int result = singlePlayer(aggressiveness); // Play the game
                    if (result == 1)
                    {
                        totalresult[0]++;
                    }
                    else if (result == 2)
                    {
                        totalresult[1]++;
                    }
                    printf("\n\n");
                    printf("Player   win count:%u\nComputer win count:%u\n\n",totalresult[0],totalresult[1]);
                    printf("Press \"C\" to Continue, other inputs end current game\n");
                    continueplay=getch();
                }while(continueplay=='C' || continueplay=='c');
                break;


                case 'M':
                case 'm':
                system("cls");
                printf("Start Multiplayer, Press Any Key to Continue\n");
                getch();
                system("cls");
                memset(totalresult,0,sizeof(totalresult));
                do{
                    int result = multiPlayer(); // Play the game
                    if (result == 1)
                    {
                        totalresult[0]++;
                    }
                    else if (result == 2)
                    {
                        totalresult[1]++;
                    }
                    printf("\n\n");
                    printf("Player1 win count:%u\nPlayer2 win count:%u\n\n",totalresult[0],totalresult[1]);
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



