#ifndef VIDEOPOKERGAME_H
#define VIDEOPOKERGAME_H

/////////////////////////////////////////////////////////////////////
// Project QT-VideoPoker
//
// Author: Ricky Bastarache
// This assignment represents my own work and is in accordance with the College Academic Policy
//
// Copyright (c) 2016 All Right Reserved by Dave Burchill
// Contributors:
// Description:
//
// Date: May 2016
//
// Revisions:
//
/////////////////////////////////////////////////////////////////////

#include "hand.h"


enum class CardColor {Black, Red};
enum class HandRank{JACKS_OR_BETTER, TWO_PAIR, THREE_OF_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH, NADA};

class videoPokerGame
{
public:
    videoPokerGame();

    bool isCardHold(int i);
    void dealOrDraw();
    void changeHold(int i);
    std::string cardToString(int i);
    CardColor suitColor(int i);
    bool isPlayedHand();
    bool isNewHand();
    void state(bool);
    HandRank RankOfHand() const;

    void fillVectorWithTrue();
    void drawNewCards();

    static const std::map<HandRank,std::string> _handRank;
    static const std::map<HandRank, std::string> _payout;

private:
    void drawCard();
    void dealCard();
    std::vector<bool> _hold;
    Deck _deck;
    Hand _hand;
    bool _state;
};

#endif // VIDEOPOKERGAME_H
