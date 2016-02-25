#include "Odds.h"

/*Using this function:
-All of the helper functions will work if there are 5 or 6 cards in a players hand.
-The odds based on outs changes if you have 5 cards or 6 cards in hand.
-The number of outs does not change for 5 cards or 6 cards in had assumming no runner runner outs.
-Two calling functions will need used one for 5 cards held one for 6 cards held.
-This is because if a player has 2 cards to be dealt the odds are outs/47 and outs/46
	while if a player has only one card to be dealt the odds are outs/46.
-The decison to use the 5 card or 6 card odds call should be made dynamically by a function created
	here so the main GSM only needs to call a generic odds class regardless of number of cards held.
-When runner runner odds are implemented all runner runner calculations need placed in an if 
	statment specifying something like if (hand.size == 5) {} so the functions remain independant of 
	handsize with a large number of possabilities in the {}*/


Odds::Odds()
{
	hand.resize(6);
	hand[0].set(7,3);
	hand[1].set(6,0);
	hand[2].set(13,3);
	hand[3].set(6,2);
	hand[4].set(7,0);
	hand[5].set(14,2);

}


Odds::~Odds(void)
{
}



void Odds::cardOne()
{

	for(unsigned int i=0;i<hand.size();i++)
	{
		cout << hand[i].rank << "  " <<  hand[i].suit << endl;

	}
}

void Odds::HandSort ()
{
	std::sort(hand.begin(),hand.end());

}


//rankCount is an array from 0 to 15.  The value of each number of the array is the number of each rank in hand
//ex: if rankCount[2] = 3 that player has 3 twos in their hand
//this array will be used in checking pairs etc
void Odds::calcRanks()
{
	for(int i=0;i<15;i++)
		{
			rankCount[i] = 0;
		}
	for(unsigned int i=0;i<hand.size();i++) 
		{
			rankCount[hand[i].rank]+=1;
		}

	//debugging on screen output
	//cout << endl << endl;
	//for(int i=2;i<15;i++)
	//	{
	//		cout << "The number of" << i << "'s: "<< rankCount[i] << endl;
	//	}
	//end debugging

}

//suitCount is similar to rankCount to be used in the calculation of flushes.
void Odds::calcSuits()
{
	for(int i=0;i<4;i++)
		{
			suitCount[i] = 0;
		}
	for(unsigned int i=0;i<hand.size();i++) 
		{
			suitCount[hand[i].suit]+=1;
		}

	//debugging on screen output
	//cout << endl << endl;
	//for(int i=0;i<4;i++)
	//	{
	//		cout << "the number of suit";
	//		cout << i;
	//		cout << suitCount[i] << endl;
	//	}
	//end debugging

}


//Odds:: needed to put this function in the scope of the odds object
//be sure to declare in main
int Odds::onePairOdds ()
{
		int outs=hand.size()*3;
	for (int i=2;i<15;i++)
	{
		if (rankCount[i] > 1)
		{
			outs = 99;
		}
	}

	/*/for debugging
	cout << endl << "The number of outs for one pair:";
	cout << outs << endl;
	//end debugging*/
	return outs;
}

int Odds::twoPairOdds ()
{
	int outs = 0;
	/*int rankHold[15]; //this is a place holder for rankCount so the data can be edited
	for (int i=0;i<15;i++) //for loop to set rankHold to rankCount
	{
	rankHold[i]=rankCount[i];
	}*/

	int numPair = 0;
	int numThree = 0;
	int numFour = 0;

	for (int i = 0; i<15;i++)
	{
		if (rankCount[i] > 1)
		{
			numPair = numPair +1;
		}
		if (rankCount[i] > 2)
		{
			numThree = numThree + 1;
		}
		if (rankCount[i] > 3)
		{
			numFour = numFour + 1;
		}
	}
	if (numPair > 1)
	{
		outs = 99;
	}
	else if (numPair == 1 && numThree == 0 && numFour == 0)
	{
		outs = (hand.size()-2)*3;
	}
	else if (numPair == 1 && numThree == 1 && numFour == 0)
	{
		outs = (hand.size()-3)*3;
	}
	else if (numPair == 1 && numThree == 1 && numFour == 1)
	{
		outs = (hand.size()-4)*3;
	}

	/*/for debugging
	cout << endl << "The number of outs for two pair:";
	cout << outs << endl;
	//end debugging*/

	return outs;
}

int Odds::threeofaKind ()
{
		int outs = 0;
		int numPair = 0;
	for (int i=2;i<15;i++)
	{
		if (rankCount[i] > 2)
		{
			outs = 99;
		}
		else if (rankCount[i] == 2)
		{
			numPair = numPair + 1;
		}
	}
	//cout << endl << "The number of pairs in this hand is: " << numPair;
	if (numPair > 0)
	{
		outs = numPair * 2;
	}

	//for debugging
	//cout << endl << "The number of outs for three of a kind:";
	//cout << outs << endl;
	//end debugging
	return outs;
}

int Odds::fourofaKind ()
{
		int outs = 0;
		int numPair = 0;
		int numThree = 0;
	for (int i=2;i<15;i++)
	{
		if (rankCount[i] > 3)
		{
			outs = 99;
		}
		else if (rankCount[i] == 2)
		{
			numPair = numPair + 1;
		}
		else if (rankCount[i] == 3)
		{
			numThree = numThree + 1;
		}
	}
	if (numThree > 0)
	{
		outs = numThree;
	}

	//for debugging
	//cout << endl << "The number of outs for four of a kind:";
	//cout << outs << endl;
	//end debugging
	return outs;
}

int Odds::fullHouseOdds()
{
	int outs = 0;
	int numPair = 0;
	int numThree = 0;
	int numFour = 0;

	for (int i = 0; i<15;i++)
	{
		if (rankCount[i] == 2)
		{
			numPair = numPair +1;
		}
		if (rankCount[i] == 3)
		{
			numThree = numThree + 1;
		}
		if (rankCount[i] == 4)
		{
			numFour = numFour + 1;
		}
	}
	
	if (numPair == 1 && numThree == 1)
	{
		outs = 99;
	}
	else if (numPair == 2)
	{
		outs = 4;
	}
	else if (numThree == 1)
	{
		outs = (hand.size()-3)*3;
	}
	else if (numFour == 1)
	{
		outs = (hand.size()-4)*3;
	}

	//for debugging
	//cout << endl << "The number of outs for a full house:";
	//cout << outs << endl;
	//end debugging

	return outs;
}

int Odds::flushOdds ()
{
		int outs=0;
	for (int i=0;i<3;i++)
	{
		if (suitCount[i] > 4)
		{
			outs = 99;
		}
		else if (suitCount[i] == 4)
		{
			outs = 9;
		}
	}

	//for debugging
	//cout << endl << "The number of outs for a flush:";
	//cout << outs << endl;
	//end debugging
	return outs;
}


//this is a helper for the straight calculation
void Odds::xtraRanks()
{
	for(int i=0;i<15;i++)
		{
			rankXtra[i] = 0;
		}
	for(unsigned int i=0;i<hand.size() + 1;i++) 
		{
			rankXtra[reducedHand[i]]+=1;
		}
	//return (0);  //how do I return this array
	//origionally reducedHand was to be passed into this and rankXtra was to be returned
	//to simplify this both became global variables.
}


//The point of this function is to remove pairs, three of a kinds, and four of a kinds
//this is done by setting the repeated value equal to the next in line.
//The reducedHand array should always be at least one block larger then the hand.size
void Odds::reduceRanks()
{

	for(unsigned int i=1;i<hand.size() + 1;i++)
	{
		if (reducedHand[i] == reducedHand[i-1])
		{
			reducedHand[i] = reducedHand[i+1];
		}
	}

}

void Odds::straightHand()
{
	for (int i = 0; i < 9; i++)
	{
		reducedHand[i] = 0;
	}
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		reducedHand[i] = hand[i].rank;
	}

}


int Odds::fourCardZero(int outs)
{
	if (reducedHand[0] != 1 && reducedHand[0] + 1 == reducedHand[1] 
		&& reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] != 14)
		{
			outs = 8;
		}
		else if (reducedHand[0] + 2 == reducedHand[1] && reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3])
		{
			outs = 4;
		}
		else if (reducedHand[0] + 1 == reducedHand[1] && reducedHand[1] + 2 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3])
		{
			outs = 4;
		}
		else if (reducedHand[0] + 1 == reducedHand[1] && reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 2 == reducedHand[3])
		{
			outs = 4;
		}
		//if an ace is low there is only the high card of a straight that can give you a straight.
		else if (reducedHand[0] == 1 && reducedHand[0] + 1 == reducedHand[1] 
		&& reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3])
		{
			outs = 4;
		}
		/*This case should never happen because if reducedHand[3] == 14 it will be shifted up and a 1 will be inserted
		This case if for an Ace as the high card of a straight.*/
		else if (reducedHand[0] + 1 == reducedHand[1] && reducedHand[1] + 1 == reducedHand[2] 
		&& reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] == 14)
		{
			outs = 4;
		}
			/**/
	return(outs);
}


int Odds::fourCardOne(int outs)
{
	if (reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3]
		&& reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] != 14)
		{
			outs = 8;
		}
		else if (reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3]
		&& reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] == 14)
		{
			outs = 4;
		}
		else if (reducedHand[1] + 2 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4])
		{
			outs = 4;
		}
		else if (reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 2 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4])
		{
			outs = 4;
		}
		else if (reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 2 == reducedHand[4])
		{
			outs = 4;
		}
	return (outs);
}

int Odds::fourCardTwo(int outs)
{
	if (reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] + 1 == reducedHand[5] 
		&& reducedHand[5] != 14)
		{
			outs = 8;
		}
		else if (reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] + 1 == reducedHand[5])
		{
			outs = 4;
		}
		else if (reducedHand[2] + 2 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] +1 == reducedHand[5])
		{
			outs = 4;
		}
		else if (reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 2 == reducedHand[4] && reducedHand[4] +1 == reducedHand[5])
		{
			outs = 4;
		}
		else if (reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] +2 == reducedHand[5])
		{
			outs = 4;
		}
	return (outs);
}


int Odds::fourCardThree(int outs)
{
		if (reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] + 1 == reducedHand[5] && reducedHand[5] + 1 == reducedHand[6])
		{
			outs = 4;
		}
		if (reducedHand[3] + 2 == reducedHand[4] && reducedHand[4] + 1 == reducedHand[5] && reducedHand[5] + 1 == reducedHand[6])
		{
			outs = 4;
		}
		if (reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] + 2 == reducedHand[5] && reducedHand[5] + 1 == reducedHand[6])
		{
			outs = 4;
		}
		if (reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] + 1 == reducedHand[5] && reducedHand[5] + 2 == reducedHand[6])
		{
			outs = 4;
		}
	return (outs);
}


int Odds::straightOdds()
{
	int outs = 0;
	//first make reduced hand equal to hand.rank and zeros
	straightHand();
	//check to see if there is an ace
	xtraRanks();

	/*/debugging Ace not working
	cout << endl << "The number of Aces detected:";
	cout << rankXtra[14] << endl;
				for(int l=0;l<8;l++)
				{
					cout << endl <<"Card in straight:" << l <<":";
					cout << reducedHand[l] << endl;
				}
	//end debugging*/

	if (rankXtra[14] > 0)
	{
		for (int i = 7; i > 0 ; i--)
		{
			reducedHand[i] = reducedHand[i-1];
		}
		reducedHand[0] = 1;
		xtraRanks(); //recalculate xtraRanks with a 1 in the first holder
	}

	/*/debugging Ace not working
	cout << endl << "The number of Aces detected:";
	cout << rankXtra[14] << endl;
				for(int l=0;l<8;l++)
				{
					cout << endl <<"Card in straight:" << l <<":";
					cout << reducedHand[l] << endl;
				}
	//end debugging*/

	//remove all pairs and three of a kinds
	for (int i = 2 ;i < 15;i++)
	{
		if (rankXtra[i] > 1)
		{
			reduceRanks();//this shifts x of a kind to x-1 of a kind
			xtraRanks();
		}
	}
	for (int i = 2 ;i < 15;i++)
	{
		if (rankXtra[i] > 1)
		{
			reduceRanks();//this shifts x of a kind to x-1 of a kind
			xtraRanks();
		}
	}
	
	if (reducedHand[0] + 1 == reducedHand[1] && reducedHand[1] + 1 == reducedHand[2]
	&& reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4])
	{
		outs = 99;
	}
	else if (reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3]
	&& reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] + 1 == reducedHand[5])
	{
		outs = 99;
	}
	else if (reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4]
	&& reducedHand[4] + 1 == reducedHand[5] && reducedHand[5] + 1 == reducedHand[6])
	{
		outs = 99;
	}

	//this else if block checks 4 in a row starting with the low card.
	else 
	{
		outs = fourCardZero(outs);
		outs = fourCardOne(outs);
		outs = fourCardTwo(outs);
		outs = fourCardThree(outs);
	}

	//this else if block checks 4 in a row starting with reducedhand[1] card.
	/*This section is an attempt at optimization that is not working correct
	else if (reducedHand[5] != 0)
	{
		outs = fourCardTwo();
	}

	//Check starting at reducedHand[2]
	else if (reducedHand[4] != 0)
	{
		outs = fourCardOne();
	}
	 //Check starting at reducedHand[3] last one  This case will only happen if an ace is held and 6 cards have been dealt.

	else if (reducedHand[3] !=0)
	{
		outs = fourCardZero();
	}
	*/

	//for debugging
	//cout << endl << "The number of outs for a straight:";
	//cout << outs << endl;
	//end debugging

	return outs;
}

int Odds::straightFlushZeroRemover()
{
	for (int i = 1; i<7 ; i ++)
	{
		if (reducedHand[i] == 0)
		{
			reducedHand[i] = reducedHand[i+1];
		}
		if (reducedHand[i] == reducedHand[i-1])
		{
			reducedHand[i] = reducedHand[i+1];
		}
	}
	return 0;
}

int Odds::straightFlushOdds()
{
	int outs = 0;
	for (int i = 0; i < 9; i++)
	{
		reducedHand[i] = 0;
	}

	for (int j = 0 ; j < 4 ; j++)
	{
		if (suitCount[j] > 3)
		{
				/*/debugging
				cout << endl << "Current suit count (in straight flush):";
				cout << suitCount[j] << endl;
				//end debugging*/
			for (unsigned int i = 0 ; i < hand.size() ; i++)
			{
				if (hand[i].suit == j)
				{
					reducedHand[i] = hand[i].rank;
				}

			}

			
			straightFlushZeroRemover();
			straightFlushZeroRemover();
			/*/debugging
			for(int l=0;l<8;l++)
				{
					cout << endl <<"Card" << l <<":";
					cout << reducedHand[l] << endl;
				}
			//end debugging*/

			if (rankXtra[14] > 0)
			{
				for (int i = 7; i > 0 ; i--)
				{
					reducedHand[i] = reducedHand[i-1];
				}
				reducedHand[0] = 1;  //shift all values up one and put a one in at 0
			}
			//make all the nested if statments in the straight function into functions on their own and execute here
			if (reducedHand[0] + 1 == reducedHand[1] && reducedHand[1] + 1 == reducedHand[2]
			&& reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4])
			{
				outs = 99;
			}
			else if (reducedHand[1] + 1 == reducedHand[2] && reducedHand[2] + 1 == reducedHand[3]
			&& reducedHand[3] + 1 == reducedHand[4] && reducedHand[4] + 1 == reducedHand[5])
			{
				outs = 99;
			}
			else if (reducedHand[2] + 1 == reducedHand[3] && reducedHand[3] + 1 == reducedHand[4]
			&& reducedHand[4] + 1 == reducedHand[5] && reducedHand[5] + 1 == reducedHand[6])
			{
				outs = 99;
			}

			else 
			{
				outs = fourCardZero(outs);
				outs = fourCardOne(outs);
				outs = fourCardTwo(outs);
				outs = fourCardThree(outs);
			}
	
			/*This section is an attempt at optimization that is not working correct.
			//this else if block checks 4 in a row starting with the low card.
			else if (reducedHand[3] != 0)
			{
				outs = fourCardZero()/4;
			}
	
			//this else if block checks 4 in a row starting with reducedhand[1] card.
			else if (reducedHand[4] != 0)
			{
				outs = fourCardOne()/4;
			}
	
			//Check starting at reducedHand[2]
			else if (reducedHand[5] != 0)
			{
				outs = fourCardTwo()/4;
			}
			 //Check starting at reducedHand[3] last one  This case will only happen if an ace is held and 6 cards have been dealt.

			else if (reducedHand[6] !=0)
			{
				outs = fourCardThree()/4;
			}
			*/
		}
	}

	//for debugging
	//cout << endl << "The number of outs for a straight flush:";
	//cout << outs << endl;
	//end debugging
	return outs;
}

//runner runner odds are when two specific cards need pulled.
//straight runner runner will be 30-39, straight flush will be 40-49, flush will be 50-54
//four of a kind 55-59 three of a kind 60-69 and two pair 70-79
//these numbers are referances to a lookup only and have no bearing on the actual number of outs.
//runner runner will only show up when handsize is 5.
double Odds::outsToOdds (double outs)
{
	double odds = 0;
	if (hand.size() == 5)
	{
		if (outs == 1)
		{
			odds = 4.26;
		}
		else if (outs == 2)
		{
			odds = 8.42;
		}
		else if (outs == 3)
		{
			odds = 12.49;
		}
		else if (outs == 4)
		{
			odds = 16.47;
		}
		else if (outs == 5)
		{
			odds = 20.35;
		}
		else if (outs == 6)
		{
			odds = 24.14;
		}
		else if (outs == 7)
		{
			odds = 27.84;
		}
		else if (outs == 8)
		{
			odds = 31.45;
		}
		else if (outs == 9)
		{
			odds = 34.97;
		}
		else if (outs == 10)
		{
			odds = 38.39;
		}
		else if (outs == 11)
		{
			odds = 41.72;
		}
		else if (outs == 12)
		{
			odds = 44.96;
		}
		else if (outs == 13)
		{
			odds = 48.10;
		}
		else if (outs == 14)
		{
			odds = 51.16;
		}
		else if (outs == 15)
		{
			odds = 54.12;
		}
		else if (outs == 16)
		{
			odds = 56.98;
		}
		else if (outs == 17)
		{
			odds = 59.76;
		}
		else if (outs == 18)
		{
			odds = 62.44;
		}
		else if (outs == 99)
		{
			odds = 100;
		}
		else
		{
			odds = 999;
		}
	}	
	if (hand.size() == 6)
	{
		if (outs == 1)
		{
			odds = 2.17;
		}
		else if (outs == 2)
		{
			odds = 4.35;
		}
		else if (outs == 3)
		{
			odds = 6.52;
		}
		else if (outs == 4)
		{
			odds = 8.70;
		}
		else if (outs == 5)
		{
			odds = 10.87;
		}
		else if (outs == 6)
		{
			odds = 13.04;
		}
		else if (outs == 7)
		{
			odds = 15.22;
		}
		else if (outs == 8)
		{
			odds = 17.39;
		}
		else if (outs == 9)
		{
			odds = 19.57;
		}
		else if (outs == 10)
		{
			odds = 21.74;
		}
		else if (outs == 11)
		{
			odds = 23.91;
		}
		else if (outs == 12)
		{
			odds = 26.09;
		}
		else if (outs == 13)
		{
			odds = 28.26;
		}
		else if (outs == 14)
		{
			odds = 30.43;
		}
		else if (outs == 15)
		{
			odds = 32.61;
		}
		else if (outs == 16)
		{
			odds = 34.78;
		}
		else if (outs == 17)
		{
			odds = 36.96;
		}
		else if (outs == 18)
		{
			odds = 39.13;
		}
		else if (outs == 99)
		{
			odds = 100;
		}
		else
		{
			odds = 999;
		}
	}	
	return (odds);
	
}

double Odds::oddsCall()
{
	double odds[9];
	int outs[9];
	//double oddsReturn[3][3];  //the first part is the odds the second is the hand.
	for (int i =0; i < 9; i++)
	{
		outs[i] = 0;
		odds[i] = 0;
	}

	/*for (int i = 0, j = 0; i < 3; i++,j++)
	{
		oddsReturn[i][j] = 0;
	} */

	//display the current hand
	for (unsigned int i = 0 ; i < hand.size(); i++)
	{
		hand[i].printCard();
	}

	HandSort();		//sort the hand
	calcRanks();	//how many of each rank card are there
	calcSuits();	//how many of each suit are there
	outs[1] = onePairOdds();
	outs[2] = twoPairOdds();
	outs[3] = threeofaKind();
	outs[4] = straightOdds();
	outs[5] = flushOdds();
	outs[6] = fullHouseOdds();
	outs[7] = fourofaKind();
	outs[8] = straightFlushOdds();

	for (int i = 0; i<9; i++)
	{
		if (outs[i] != 0)
		{
			odds[i] =  outsToOdds(outs[i]);
		}
	}

	//debugging

	cout << endl << "The odds for a straight flush:";
	cout << odds[8] << "%" << endl;
	cout << endl << "The odds for a four of a kind:";
	cout << odds[7] << "%" << endl;
	cout << endl << "The odds for a full house:";
	cout << odds[6] << "%" << endl;
	cout << endl << "The odds for a flush:";
	cout << odds[5] << "%" << endl;
	cout << endl << "The odds for a straight:";
	cout << odds[4] << "%" << endl;
	cout << endl << "The odds for a three of a kind:";
	cout << odds[3] << "%" << endl;
	cout << endl << "The odds for two pair:";
	cout << odds[2] << "%" << endl;
	cout << endl << "The odds for a pair:";
	cout << odds[1] << "%" << endl;
	//end debugging  */


	oddsOut.bestHandRank = 0;
	oddsOut.nextHandRank = 0;
	oddsOut.thirdHandRank =0;
	oddsOut.bestHandOdds = 0;
	oddsOut.nextHandOdds = 0;
	oddsOut.thirdHandOdds =0;
	oddsOut.handHeld = 0;
	for (int i = 8 ; i > 0; i--)
	{
		if (odds[i] == 100)
		{
			oddsOut.handHeld = i;
			i = 0;
		}
	}

	for (int i = oddsOut.handHeld ; i < 8; i++) //starting at the next best hand 
	{
		if (odds[i] > 0 && odds[i] < 100)
		{
			oddsOut.nextHandRank = i;
			oddsOut.nextHandOdds = odds[i];
			i = 10;
		}
	}

	for (int i = 8 ; i > oddsOut.handHeld ; i--)
	{
		if (odds[i] > 0 && odds[i] < 100)
		{
			oddsOut.bestHandRank = i;
			oddsOut.bestHandOdds = odds[i];
			i = 0;
		}
	}

	if (odds[0] > 0 && odds[0] < 101)
	{
		//return one pair odds
	}
	if (odds[1] > 0 && odds[1] < 101)
	{
		//return two pair odds
	}
	if (odds[2] > 0 && odds[2] < 101)
	{
		//return three of a kind odds
	}
	if (odds[3] > 0 && odds[3] < 101)
	{
		//return straight odds
	}
	if (odds[4] > 0 && odds[4] < 101)
	{
		//return flush odds
	}
	if (odds[5] > 0 && odds[5] < 101)
	{
		//return full house odds
	}
	if (odds[6] > 0 && odds[6] < 101)
	{
		//return four of a kind odds
	}
	if (odds[7] > 0 && odds[7] < 101)
	{
		//return straight flush odds
	}


	
	cout << endl << "The rank of the hand held is: " << oddsOut.handHeld << endl;
	cout << "The next best hands rank is: " << oddsOut.nextHandRank << endl;
	cout << "The next best hands odds are: " << oddsOut.nextHandOdds << "%" << endl;
	cout << "The best hands rank is: " << oddsOut.bestHandRank << endl;
	cout << "The best hands odds are: " << oddsOut.bestHandOdds << "%" << endl;
	//return(oddsReturn);
	return(0);
}