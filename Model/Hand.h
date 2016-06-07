#ifndef HAND_H
#define HAND_H

/////////////////////////////////////////////////////////////////////
// Project QT-VideoPoker
//
// Author: Ricky Bastarache
// This assignment represents my own work and is in accordance with the College Academic Policy
//
// Copyright (c) 2016 All Right Reserved by Dave Burchill
// Contributors: Michael Landry.
// Comment: i was having trouble with getting my Hand class with VideoPokerGame so i asked Micheal to help me with it
// we could notfind the problem and he just told me what he did and i used it in my code.
// Description:
//
// Date: May 2016
//
// Revisions:
//
/////////////////////////////////////////////////////////////////////

#pragma once
#include "Deck.h"
#include "Card.h"
#include <algorithm>
#include <sstream>
#include <utility>

using CardPtr = std::shared_ptr<Card>;

class Hand
{
public:
    Hand();
    ~Hand();
    void addCard(CardPtr);
    void clear();
    void changCard(int);
    void holdOrDraw(std::vector<bool>);
    void DrawCardForNewHand();
    bool isCardHold(int i);
    void toggleHold(int i);
    int size();

    bool isPair() const;
    bool isJacksOrBetter() const;
    bool isThreeOfakind()const;
    bool isFourOfaKind()const;
    bool isFullHouse()const;
    bool isTwoPair()const;
    bool isFlush()const;
    bool isStraight()const;
    bool isStraightFlush() const;
    bool isRoyalFlush() const;

    void fillVectorWithTrue();
    bool suitColor(int i);
    std::string cardToString(int i);

private:
    std::vector<CardPtr> _hand;
    std::vector<bool> _hold;
    std::set<int> _cardsToChange;
    std::map<Face, int> _face;
    std::map<Suit, int> _suit;
    std::set<Face> _checkIfStraight;
};


#endif // HAND_H
