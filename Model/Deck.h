#ifndef DECK_H
#define DECK_H

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

#pragma once
#include <vector>
#include <memory>
#include "Card.h"

struct Card;
using CardPtr = std::shared_ptr<Card>;

class Deck
{
public:
    Deck();
    ~Deck();
    bool isEmpty() const;
    CardPtr draw();
    void shuffle();

private:
    std::vector<CardPtr> _deck;
    int _topOfDeck;

};

#endif // DECK_H
