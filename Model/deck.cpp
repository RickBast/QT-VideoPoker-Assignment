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

#include "Deck.h"
#include <time.h>

Deck::Deck()
{
    for (auto f : Card::faces)
        for (auto s : Card::suits)
            _deck.push_back(std::make_shared<Card>(Card(f,s)));
    _topOfDeck = _deck.size() - 1;
}

Deck::~Deck()
{
}

bool Deck::isEmpty() const
{
    return (_topOfDeck < 0);
}

void Deck::shuffle()
{
    srand(unsigned(time(0)));
    for (int i = 0; i < _deck.size(); ++i)
        swap(_deck[i], _deck[rand() % _deck.size()]);
    _topOfDeck = _deck.size() - 1;
}
CardPtr Deck::draw()
{
    return _deck.at(_topOfDeck--);
}
