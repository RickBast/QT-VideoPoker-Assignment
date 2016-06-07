#include "Card.h"

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

std::string Card::toString() const
{
    return faceNames.at(face) + suitNames.at(suit);
}

const std::set<Suit> Card::suits
{
    Suit::CLUB,
            Suit::DIAMOND,
            Suit::HEART,
            Suit::SPADE
};

const std::set<Face> Card::faces
{
    Face::ACE,
    Face::TWO,
    Face::THREE,
    Face::FOUR,
    Face::FIVE,
    Face::SIX,
    Face::SEVEN,
    Face::EIGHT,
    Face::NINE,
    Face::TEN,
    Face::JACK,
    Face::QUEEN,
    Face::KING
};

const std::map<Face, std::string> Card::faceNames
{
    {Face::ACE, "A"},
    {Face::TWO, "2"},
    {Face::THREE, "3"},
    {Face::FOUR, "4"},
    {Face::FIVE, "5"},
    {Face::SIX, "6"},
    {Face::SEVEN, "7"},
    {Face::EIGHT, "8"},
    {Face::NINE, "9"},
    {Face::TEN,"10"},
    {Face::JACK, "J"},
    {Face::QUEEN, "Q"},
    {Face::KING, "K"}
};

// map to set the name of the suit
const std::map<Suit, std::string> Card::suitNames
{
    {Suit::HEART, "♥"},
    {Suit::DIAMOND, "♦"},
    {Suit::CLUB, "♣"},
    {Suit::SPADE, "♠"}
};

//operator overLoad for the cout
std::ostream & operator<<(std::ostream & os, Card & crd)
{
    os << crd.toString();
    return os;
}
