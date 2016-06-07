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

#include "controller/mainwindow.h"
#include "ui_mainwindow.h"
#include "../model/videoPokerGame.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QSignalMapper>
#include <QDebug>
#include <memory>
#include <QSpacerItem>

static const int NUMBER_OF_CARDS = 5;//global const for game

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _game = std::unique_ptr<videoPokerGame>(new videoPokerGame);
    _game->dealOrDraw();
    _game->fillVectorWithTrue();

    QSignalMapper * signalMapper = new QSignalMapper(this);

    auto vlMain = new QHBoxLayout(ui->centralWidget);

    ui->centralWidget->setStyleSheet("background: blue;");

    auto vlPayTable = new QVBoxLayout();
    auto hlCards = new QHBoxLayout();

    QPixmap logo(":/media/media/banner.png");
    auto lblLogo = new  QLabel;
    lblLogo->setMinimumSize(1000,250);
    lblLogo->setMaximumSize(1000,250);
    lblLogo->setPixmap( QPixmap( logo) );
    lblLogo->setScaledContents( true );
    lblLogo->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    vlPayTable->addWidget(lblLogo);

    QPixmap payTable(":/media/media/paysheet1.png");
    auto lblPayTable = new  QLabel;
    lblPayTable->setMinimumSize(1000,250);
    lblPayTable->setMaximumSize(1000,250);
    lblPayTable->setPixmap( QPixmap( payTable) );
    lblPayTable->setScaledContents( true );
    lblPayTable->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    vlPayTable->addWidget(lblPayTable);

    for (int i = 0; i<NUMBER_OF_CARDS;++i)
    {
        auto CardBtn = new QPushButton(this);
        CardBtn->setMinimumSize(150,250);
        CardBtn->setMaximumSize(150,250);
        CardBtn->setFlat( true );
        CardBtn->setCheckable( true );
        QFont cardFont( "Times New Roman", 30, QFont::Bold);
        CardBtn->setFont(cardFont);
        CardBtn->setStyleSheet("border-image:url(:/media/media/cardback)");
        hlCards->addWidget(CardBtn);

        _cardBtn.push_back(CardBtn);

        connect(CardBtn, &QPushButton::clicked, signalMapper, static_cast<void(QSignalMapper:: *)()>(&QSignalMapper::map));

        signalMapper->setMapping(CardBtn,i);
    }
    connect(signalMapper, static_cast<void(QSignalMapper::*)(int)>(&QSignalMapper::mapped), this, &MainWindow::onButtonCardClick);

    vlPayTable->addLayout(hlCards);

    auto hlbtn = new QHBoxLayout();

    _btnDrawOrDeal = new QPushButton(this);
    _btnDrawOrDeal->setText("DRAW");
    _btnDrawOrDeal->setMinimumSize(150,75);
    _btnDrawOrDeal->setMaximumSize(150,75);
    _btnDrawOrDeal->setStyleSheet("background: white;");

    connect (_btnDrawOrDeal , &QPushButton::clicked, this, &MainWindow::onDrawOrDealClick);

    _playBtn = new QPushButton(this);
    _playBtn->setText("PLAY");
    _playBtn->setMinimumSize(150,75);
    _playBtn->setMaximumSize(150,75);
    _playBtn->setStyleSheet("background:white;");
    connect (_playBtn , &QPushButton::clicked, this, &MainWindow::onPlayClick);

    _handResultLbl = new QLabel(this);
    _handResultLbl->setMinimumSize(800,40);
    _handResultLbl->setMaximumSize(800,40);

    hlbtn->addWidget(_btnDrawOrDeal);
    hlbtn->addWidget(_playBtn);
    hlbtn->addWidget(_handResultLbl);
    QSpacerItem *hSpacer = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    hlbtn->addSpacerItem(hSpacer);
    vlPayTable->addLayout(hlbtn);
    hlbtn->addSpacerItem(hSpacer);

    vlMain->addLayout(vlPayTable);

    _btnDrawOrDeal->setEnabled(false);
    for(int i = 0 ; i < NUMBER_OF_CARDS; ++i)
        _cardBtn.at(i)->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    for(int i = 0 ; i < NUMBER_OF_CARDS;++i)
    {
        QString styleSheet = QString ("border-image:url(:/media/media/%1.png); color: %2;");

        QString cardValue = QString::fromStdString(_game->cardToString(i));
        QString suitColor = "black";
        QString design = "cardfront";

        if(_game->suitColor(i)== CardColor::Red)//if a card is diamond or heart set the text to color red else suit is black
            suitColor = "red";
        else
            suitColor = "black";

        if(_game->isCardHold(i))//if card is being held by player display hold on card else show card front
            design = "cardfrontHold";
        else
            design = "cardfront";

        _cardBtn.at(i)->setText(cardValue);//gets a card from index and converts it from std::string to Qstring and sets it as the current text for the card
        _cardBtn.at(i)->setStyleSheet(styleSheet.arg(design).arg(suitColor));
    }
}

void MainWindow::onButtonCardClick(int i)//if the player is playing the first hand he is dealt he can click a card to toggle between draw and hold
{
    if(_game->isPlayedHand())
    {
        _game->changeHold(i);
        draw();
    }
    else
        return;
}

void MainWindow::onDrawOrDealClick()// lets players toggle between hold and draw and diplays if the player wins the amount he won
{
    if (_game->isPlayedHand())
    {
        _game->drawNewCards();
        _game->dealOrDraw();
        _game->fillVectorWithTrue();
        _btnDrawOrDeal->setText("DEAL");
        HandRank rank = _game->RankOfHand();
        QString rankCard = QString::fromStdString(_game->_handRank.at(rank));
        QString rankPay = QString::fromStdString(_game->_payout.at(rank));
        _handResultLbl->setText(rankCard+" pays "+rankPay+" times your bet");
    }

    if(_game->isNewHand())
    {
        _btnDrawOrDeal->setText("DEAL");
        _game->dealOrDraw();
        _handResultLbl->setText("");
    }
    if(_game->isPlayedHand())
        _game->state(false);
    else
        _game->state(true);
    draw();
}

void MainWindow::onPlayClick()// when the player clicks play it shows the cards and sets them to be holdable and drawable
{
    for(int i = 0 ; i < NUMBER_OF_CARDS;++i)
        _cardBtn.at(i)->setEnabled(true);
    _btnDrawOrDeal->setEnabled(true);
    _playBtn->setEnabled(false);// set play button off because the game as already started
    draw();
}
