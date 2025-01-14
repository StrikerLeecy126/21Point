extern unsigned int* genRandSeq(unsigned int seqlen);
// The functions below seem faster when generate random sequence
extern void shuffle(unsigned int *pSeq, unsigned int sortVal);
extern unsigned int* genShuffleSeq(unsigned int seqlen,unsigned int shuffleTime);
extern void getCard_or_Pass(unsigned int *playerdeck, unsigned int *playerturn, unsigned int playerdraw,int drawcard);

extern int multiPlayer();
extern int singlePlayer();
