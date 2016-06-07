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

#include "Hand.h"

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::addCard(CardPtr p)
{
    _hand.push_back(p);
    _face[p->face]++;
    _suit[p->suit]++;
    _checkIfStraight.insert(p->face);
}

void Hand::clear()
{
    _hand.clear();
    _face.clear();
    _suit.clear();
    _checkIfStraight.clear();
}

int Hand::size()
{
    return static_cast<int>(_hand.size());
}


bool Hand::isPair() const
{
    auto itr = std::find_if(_face.begin(), _face.end(), [](std::pair<Face, int>e) {return e.second == 2; });
    if (itr != _face.end())
        return true;
    return false;
}

bool Hand::isJacksOrBetter() const
{
    auto itr = std::find_if(_face.begin(), _face.end(), [](std::pair<Face, int>e) {return e.second == 2; });
    if (itr != _face.end() && itr->first == Face::JACK || itr->first == Face::QUEEN || itr->first == Face::KING || itr->first == Face::ACE)
        return true;
    return false;
}


bool Hand::isThreeOfakind() const
{
    auto itr = std::find_if(_face.begin(), _face.end(), [](std::pair<Face, int>e) {return e.second == 3; });
    if (itr != _face.end())
        return true;
    return false;
}

bool Hand::isFourOfaKind() const
{
    auto itr = std::find_if(_face.begin(), _face.end(), [](std::pair<Face, int>e) {return e.second == 4; });
    if (itr != _face.end())
        return true;
    return false;
}

bool Hand::isFullHouse() const
{
    if (isPair() == true && isThreeOfakind() == true)
        return true;
    return false;
}

bool Hand::isTwoPair() const
{
    auto itr = std::count_if(_face.begin(), _face.end(), [](std::pair<Face, int>e) {return e.second == 2; });
    if (itr == 2)
        return true;
    return false;
}

bool Hand::isFlush() const
{
    auto itr = std::find_if(_suit.begin(), _suit.end(), [](std::pair<Suit, int>e) {return e.second == 5; });
    if (itr != _suit.end())
        return true;
    return false;
}

bool Hand::isStraight() const
{
    if (_checkIfStraight.size() == _hand.size())
    {
        int tmp = 0;
        int count = 0;
        int firstTurn = 0;
        int totalForHighStraight = 0;
        for (auto itr : _checkIfStraight)
        {
            totalForHighStraight += static_cast<int>(itr);
            if (firstTurn == 0)
            {
                tmp = static_cast<int>(itr);
                count++;
                firstTurn++;
                if(itr == Face::ACE)
                    totalForHighStraight += 13;
            }
            if (tmp + count == static_cast<int>(itr))
                count++;
            if (count == 5)
                return true;
            if (totalForHighStraight == 55)
                return true;
        }
    }
    return false;
}

bool Hand::isStraightFlush() const
{
    if (isFlush() == true && isStraight() == true)
        return true;
    return false;
}

bool Hand::isRoyalFlush() const
{
    if (isStraightFlush() == true)
    {
        int kingAndAs = 0;
        for (auto itr : _checkIfStraight)
        {
            if (itr == Face::ACE)
                kingAndAs++;
            if (itr == Face::KING)
                kingAndAs++;
            if (kingAndAs == 2)
                return true;
        }
    }
    return false;
}

void Hand::fillVectorWithTrue()
{
    _hold.clear();
    for(int i = 0 ; i < _hand.size();++i)
        _hold.push_back(false);
}

 bool Hand::suitColor(int idx)
{
    if (_hand.at(idx)->suit == Suit::DIAMOND || _hand.at(idx)->suit == Suit::HEART)
        return true;
    else
        return false;
}

std::string Hand::cardToString(int idx)
{
    std::string card=_hand.at(idx)->toString();
    return card;
}

void Hand::changCard(int cartToChange)
{
    _hold[cartToChange-1] = !_hold[cartToChange-1];
}

void Hand::holdOrDraw(std::vector<bool> hold)
{
    _hold = hold;
}

void Hand::DrawCardForNewHand()
{
    std::vector<CardPtr> tmp;
    for (int i = 0; i < _hand.size(); ++i)
        if (_hold.at(i))
            tmp.push_back(_hand.at(i));
    clear();
    _hand = tmp;

    for (auto itr : _hand)
    {
        _face[itr->face]++;
        _suit[itr->suit]++;
        _checkIfStraight.insert(itr->face);
    }
}

bool Hand::isCardHold(int i)
{
    if(_hold.at(i))
        return true;
    return false;
}

void Hand::toggleHold(int i)
{
    _hold[i] = !_hold[i];
}



