#pragma once
#include "Card.h"
#include <vector>
#include <algorithm>
struct OddsOut
{
	int handHeld;
	int nextHandRank;
	int bestHandRank;
	double nextHandOdds;
	double bestHandOdds;
	int thirdHandRank;
	double thirdHandOdds;
};

class Odds
{
public:
	vector<Card> hand;
	int rankCount[15];
	int suitCount[4];
	int reducedHand[9]; //used in straight calculation
	int rankXtra[15]; //used in straight calculation
	int fourCardZero(int outs);
	int fourCardOne(int outs);
	int fourCardTwo(int outs);
	int fourCardThree(int outs);
	int runnerRunnerEdge(int outs);
	int runnerRunnerThreeRow(int outs);
	int runnerRunnerGapTwo(int outs);
	int runnerRunnerGapOne(int outs);
	int straightFlushZeroRemover();
	OddsOut oddsOut;
	Odds();
	~Odds(void);

	 void addCard(Card cardIn);
	 void cardOne();	 
	 void HandSort();
	 void calcRanks();
	 void calcSuits();
	 void xtraRanks();
	 void reduceRanks();
	 void straightHand();
	 int onePairOdds();
	 int twoPairOdds();
	 int threeofaKind();
	 int fourofaKind();
	 int fullHouseOdds();
	 int flushOdds();
	 int straightOdds();
	 int straightFlushOdds();
	 void oddsClear();

	 double oddsCall();
	 double outsToOdds(double outs);



};

