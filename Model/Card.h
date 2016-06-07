#ifndef CARD_H
#define CARD_H

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

#include <string>
#include <set>
#include <map>
#include <iostream>

enum class Suit { CLUB, DIAMOND, HEART, SPADE };
enum class Face { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

struct Card
{
    Card(Face f, Suit s) : face(f), suit(s){}

    const Suit suit;
    const Face face;

    std::string toString() const;

    static const std::set<Suit> suits;
    static const std::set<Face> faces;

    static const std::map<Face, std::string> faceNames;
    static const std::map<Suit, std::string> suitNames;
};

inline bool operator==(const Card& lhs, const Card& rhs)
{
    return ((lhs.face == rhs.face)&&(lhs.suit == rhs.suit));
}

inline bool operator < (const Card& lhs, const Card& rhs)
{
    if (lhs.face < rhs.face)
        return true;
    if ((lhs.face == rhs.face) && (lhs.suit < rhs.suit))
        return true;
    return false;
}

inline bool operator!=(const Card& lhs, const Card& rhs) { return !operator==(lhs, rhs); }
inline bool operator>(const Card& lhs, const Card& rhs) { return operator<(rhs, lhs); }
inline bool operator <=(const Card& lhs, const Card& rhs) { return !operator>(lhs, rhs); }
inline bool operator >=(const Card& lhs, const Card& rhs) { return !operator<(lhs, rhs); }

std::ostream& operator<<(std::ostream& os, Card& crd);

#endif // CARD_H
