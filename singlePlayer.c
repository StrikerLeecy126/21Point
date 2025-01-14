#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "mainfunctions.h"

int aiMove(unsigned int* player1_deck, unsigned int* player2_deck, unsigned int player1_turn, unsigned int player2_turn, unsigned int seqlen, int aggressiveness);
//#define aidebug // Output AI decision, de-comment it to print AI's decision


/*--------------------------------------
* Function: singlePlayer
* Description: Main Single Player function (Player vs AI Mode)
* Input: int aggre: AI aggressiveness, 
* Output: int: Round result
--------------------------------------*/
int singlePlayer(int aggre)
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
        printf("Player's face-down card: %u\n",player1_deck[0]);
        printf("Enter \"C\" to continue, which will clear the screen\n");
        player1_ready=getch();
        system("cls");
    }while(player1_ready != 'C' && player1_ready != 'c');

    // AI's Turn
    // Player2's first Card;  
    getCard_or_Pass(player2_deck, &player2_turn, seq_addr[card_draw_cnt],1);
    card_draw_cnt++;
    char player2_ready=0;
    do{
        printf("Drawing a card for Computer!\nEnter \"C\" to continue, which will clear the screen\n");
        player2_ready=getch();
        system("cls");
    }while(player2_ready != 'C' && player2_ready != 'c');
    system("cls");
    // AI's Turn

    // Start Draw Cards
    system("cls");
    printf("Player's   Deck: %u, \nComputer's Deck: X, \n",player1_deck[0]);
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
            printf("Player Enter \"Y\" to draw a card, or other inputs to pass this turn\n");
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
        printf("Player's   Deck: %u, ",player1_deck[0]);
        for(int k=1;k<player1_turn;k++)
        {
            printf("%u, ",player1_deck[k]);
        }
        printf("\n");
        printf("Computer's Deck: X, ");
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
                int player2_decision=aiMove(player1_deck,player2_deck,player1_turn,player2_turn,seqlen,aggre);
                if (player2_decision==1)
                {
                    player2_draw='y';
                }
                else
                {
                    player2_draw='p';
                }

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
        printf("Player's   Deck: %u, ",player1_deck[0]);
        for(int k=1;k<player1_turn;k++)
        {
            printf("%u, ",player1_deck[k]);
        }
        printf("\n");
        printf("Computer's Deck: X, ");
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
        printf("Player:%u Computer:%u\n",player1_result,player2_result);
        printf("The winner is Player!\n");
        return 1; // 1 for player1 win
    }
    else if(player1_result > 21 && player2_result <= 21 )
    {
        printf("Player:%u Computer:%u\n",player1_result,player2_result);
        printf("The winner is Computer!\n");
        return 2; // 2 for player2 win
    }
    // Both players go beyond 21, the smaller one wins
    else if(player1_result>21 && player2_result>21 && player1_result<player2_result)
    {
        printf("Player:%u Computer:%u\n",player1_result,player2_result);
        printf("The winner is Player!\n");
        return 1; 
    }
    else if(player1_result>21 && player2_result>21 && player1_result>player2_result)
    {
        printf("Player:%u Computer:%u\n",player1_result,player2_result);
        printf("The winner is Computer!\n");
        return 2; 
    }
    // Both players are less than 21, the bigger one wins
    else if(player1_result<=21 && player2_result<=21 && player1_result>player2_result)
    {
        printf("Player:%u Computer:%u\n",player1_result,player2_result);
        printf("The winner is Player!\n");
        return 1; 
    }
    else if(player1_result<=21 && player2_result<=21 && player1_result<player2_result)
    {
        printf("Player:%u Computer:%u\n",player1_result,player2_result);
        printf("The winner is Computer!\n");
        return 2; 
    }
    else //Should only be equal case
    {
        printf("Player:%u Computer:%u\n",player1_result,player2_result);
        printf("It's a draw!");
        return 3;  // 3 for draw
    }
}


/*--------------------------------------
* Function: aiMove
* Description: 
Decide AI's move according to the known cards, AI calculate the 
probability of the remaining cards that do not go over 21, and decide
according to the probability and the random number.
* Input: 
unsigned int* player1_deck: player1_deck pointer
unsigned int* player2_deck: player2_deck(AI) pointer
unsigned int player1_turn: turn number for player1
unsigned int player2_turn: turn number for player2(AI)
unsigned int seqlen: number of cards in the deck
int aggressiveness: AI aggressiveness
* Output: int: AI move Flag
--------------------------------------*/

int aiMove(unsigned int* player1_deck, unsigned int* player2_deck, unsigned int player1_turn, unsigned int player2_turn, unsigned int seqlen, int aggressiveness)
{
    // First card is face-down card, AI doesn't know
    unsigned int* player1_faceup = player1_deck+1;
    // AI knows its face-down card
    unsigned int* player2_faceup = player2_deck;

    // Face-up card number for both players
    unsigned int player1_fu_num=player1_turn-1;
    unsigned int player2_fu_num=player2_turn;

    // If the card is available, the array is 0
    unsigned int possible_deck[seqlen];
    memset(possible_deck,0,sizeof(possible_deck));

    // If the card is taken, the location is 0
    for(int i=0;i<player1_fu_num;i++)
    {
        possible_deck[player1_faceup[i]-1]=1;   // Array Start with 0
    }
    for(int i=0;i<player2_fu_num;i++)
    {
        possible_deck[player2_faceup[i]-1]=1;   // Array Start with 0
    }

    // for (int i=0;i<seqlen;i++)
    // {
    //     printf("%u ",possible_deck[i]);
    // }
    // printf("\n");
    // getch();
    // Calculate AI's total card value
    unsigned int ai_total_val=0;
    for(int i=0;i<player2_turn;i++)
    {
        ai_total_val=ai_total_val+player2_faceup[i];
    }

    // Determine the result of each possible card draw
    unsigned int pos_card_cnt=0;
    unsigned int neg_card_cnt=0;
    for(int j=0;j<seqlen;j++)
    {
        unsigned int temp_val=0;
        if(possible_deck[j]==0)
        {
            temp_val=ai_total_val+j+1;  // Array Start with 0
            if (temp_val>21)
            {
                neg_card_cnt++;
            }
            else
            {
                pos_card_cnt++;
            }
        }
    }

    unsigned int thres = (unsigned int)((1000*pos_card_cnt)/(pos_card_cnt+neg_card_cnt));

    // Determine if to draw a card
    if(pos_card_cnt==0 || neg_card_cnt>pos_card_cnt+3)
    {
        #ifdef aidebug
            printf("pos_card_cnt=%u, neg_card_cnt=%u, thres=%u\n",pos_card_cnt,neg_card_cnt,thres);
            getch();
        #endif
        return 0; // No card available, or too few possible card
    }
    else
    {
        srand((unsigned)time(NULL));
        unsigned int aiDecision= (rand() % 1001)+aggressiveness; // Changing Aggressiveness, higher is more conservative, less is more aggressive
        if (aiDecision>1000)
        {
            aiDecision=1000; // decision no more than maximum probability
        }
        else if (aiDecision<0)
        {
            aiDecision=0; // decision larger than minimum probability
        }
        

        if(aiDecision<=thres)
        {
            #ifdef aidebug
                printf("pos_card_cnt=%u, neg_card_cnt=%u, thres=%u, aiDecision=%u, aggressiveness=%i\n",pos_card_cnt,neg_card_cnt,thres,aiDecision,aggressiveness);
                getch();
            #endif

            return 1;
        }
        else
        {
            #ifdef aidebug
                printf("pos_card_cnt=%u, neg_card_cnt=%u, thres=%u, aiDecision=%u, aggressiveness=%i\n",pos_card_cnt,neg_card_cnt,thres,aiDecision,aggressiveness);
                getch();
            #endif

            return 0;
        }
    }

}
