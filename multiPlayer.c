#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "mainfunctions.h"

/*--------------------------------------
* Function: multiPlayer
* Description: Main MultiPlayer function (Player vs Player Mode)
* Input: None, 
* Output: int: Round result
--------------------------------------*/
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