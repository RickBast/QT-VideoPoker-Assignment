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

#include "videoPokerGame.h"

videoPokerGame::videoPokerGame() //constructor
{
    _state=true;
    _deck.shuffle();
}

const std::map<HandRank, std::string> videoPokerGame::_handRank{// map of all hand rank with a string
    {HandRank::JACKS_OR_BETTER, "Jacks or better"},
    {HandRank::TWO_PAIR, "Two pair"},
    {HandRank::THREE_OF_KIND,"Three of a kind"},
    {HandRank::STRAIGHT,"Straight"},
    {HandRank::FLUSH,"Flush"},
    {HandRank::FULL_HOUSE,"Full House"},
    {HandRank::FOUR_OF_KIND,"Four Of A Kind"},
    {HandRank::STRAIGHT_FLUSH,"Straight Flush"},
    {HandRank::ROYAL_FLUSH,"Royal Flush"},
    {HandRank::NADA, "Nada"}
};

const std::map<HandRank, std::string> videoPokerGame::_payout{ // map of all payouts with a string
    {HandRank::NADA, "0"},
    {HandRank::JACKS_OR_BETTER, "1" },
    {HandRank::TWO_PAIR, "2" },
    {HandRank::THREE_OF_KIND,"3" },
    {HandRank::STRAIGHT,"4" },
    {HandRank::FLUSH,"6" },
    {HandRank::FULL_HOUSE,"9" },
    {HandRank::FOUR_OF_KIND, "25"},
    {HandRank::STRAIGHT_FLUSH,"50" },
    {HandRank::ROYAL_FLUSH,"250" }
};

bool videoPokerGame::isCardHold(int i)
{
    return _hand.isCardHold(i);
}

std::string videoPokerGame::cardToString(int i)
{
    return _hand.cardToString(i);
}

CardColor videoPokerGame::suitColor(int i)
{
    if (_hand.suitColor(i))
        return CardColor::Red;
    else
        return CardColor::Black;
}

bool videoPokerGame::isPlayedHand()
{
    if(_state)
        return true;
    else
        return false;
}

bool videoPokerGame::isNewHand()
{
    if(_state == false)
        return true;
    else
        return false;
}

void videoPokerGame::state(bool state)
{
    _state = state;
}

HandRank videoPokerGame::RankOfHand() const//gives the player the rank of his hand
{
    if (_hand.isRoyalFlush())
        return HandRank::ROYAL_FLUSH;
    else if (_hand.isStraightFlush())
        return HandRank::STRAIGHT_FLUSH;
    else if (_hand.isFourOfaKind())
        return HandRank::FOUR_OF_KIND;
    else if (_hand.isFullHouse())
        return HandRank::FULL_HOUSE;
    else if (_hand.isFlush())
        return HandRank::FLUSH;
    else if (_hand.isStraight())
        return HandRank::STRAIGHT;
    else if (_hand.isThreeOfakind())
        return HandRank::THREE_OF_KIND;
    else if (_hand.isTwoPair())
        return HandRank::TWO_PAIR;
    else if (_hand.isJacksOrBetter())
        return HandRank::JACKS_OR_BETTER;
    else
        return HandRank::NADA;
}

void videoPokerGame::fillVectorWithTrue()//function that calls function in hand
{
    _hand.fillVectorWithTrue();
}

void videoPokerGame::drawNewCards()//function that calls function in hand
{
    _hand.DrawCardForNewHand();
}

void videoPokerGame::changeHold(int i)// changes the card hold at the current index
{
    _hand.toggleHold(i);// switch between draaw and hold
}

void videoPokerGame::dealOrDraw()//if player changes cards give new cards else give new hand because it is a new game
{
    if(_state)
        while (_hand.size() < 5)
            _hand.addCard(_deck.draw());
    else
    {
        _hand.clear();
        _deck.shuffle();
        while (_hand.size() < 5)
            _hand.addCard(_deck.draw());
    }
}
