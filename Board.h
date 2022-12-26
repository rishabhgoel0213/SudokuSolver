//
// Created by rishabh on 12/23/22.
//

#ifndef SUDOKUGAME_BOARD_H
#define SUDOKUGAME_BOARD_H


#include <QWidget>
#include <QLineEdit>
#include <QVector>
#include <QSet>
#include <QGridLayout>
#include <QFuture>

class Board: public QWidget
{
    Q_OBJECT

public:
    ~Board() override;
    explicit Board(QWidget *parent = nullptr);
    explicit Board(QVector<QVector<char>> b, QWidget *parent = nullptr);
    static int getSquare(QPair<int, int> loc);


private:
    QWidget* drawBoard(QVector<QVector<char>> board);
    void getNewBoard();

    QVector<QVector<char>> board_values;
    QVector<QVector<char>> solved_board;

    QFuture<void> future;

    QWidget *board_widget;
    QLineEdit *boxes[9][9]{};


};


#endif //SUDOKUGAME_BOARD_H
