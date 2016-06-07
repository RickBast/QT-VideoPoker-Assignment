#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include <memory>

class videoPokerGame;
class Hand;
class Deck;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    void draw();//draws cards for the players hand

private slots:
    void onButtonCardClick(int);//switch between draw and hold
    void onDrawOrDealClick();// lets you start game and switch cards
    void onPlayClick();// starts the game

private:
    Ui::MainWindow *ui;
    std::unique_ptr<videoPokerGame> _game;
    QPushButton * _playBtn;
    QPushButton * _btnDrawOrDeal;
    QLabel * _handResultLbl;
    std::unique_ptr<Hand> _hand;
    std::unique_ptr<Deck> _deck;
    std::vector<QPushButton *> _cardBtn;
};

#endif // MAINWINDOW_H
