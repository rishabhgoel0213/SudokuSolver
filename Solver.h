//
// Created by rishabh on 12/23/22.
//

#ifndef SUDOKUGAME_SOLVER_H
#define SUDOKUGAME_SOLVER_H

#include <QVector>
#include <QSet>
#include <algorithm>
#include "Board.h"

using namespace std;

class Solver: public QObject
{
    Q_OBJECT

public:
    bool solveSudoku(QVector<QVector<char>> board_values);
    QVector<QVector<char>> getBoard(){return *board;}

signals:
    void solvedSquare();

private:
    static bool isFull(QVector<QVector<char>> board);
    static void printBoard(QVector<QVector<char>> board);

    QVector<QVector<char>> *board;




};


#endif //SUDOKUGAME_SOLVER_H
