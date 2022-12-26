//
// Created by rishabh on 12/23/22.
//

#include <QGridLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>
#include <QPalette>
#include <QtConcurrent>
#include <utility>
#include "Board.h"
#include "Solver.h"

int Board::getSquare(QPair<int, int> loc)
{
    return (loc.first/3) + 3 * (loc.second/3);
}

Board::Board(QVector<QVector<char>> b, QWidget *parent)
{
    board_values = std::move(b);
    board_widget = drawBoard(board_values);

    auto *solver = new Solver();
    connect(solver, &Solver::solvedSquare, this, [solver, this]()
    {
        this->solved_board = solver->getBoard();
    });
    solver->solveSudoku(board_values);

    auto *solve_button = new QPushButton("Solve");
    connect(solve_button, &QPushButton::clicked, [this]()
    {
        QWidget *prev_widget = this->board_widget;
        QWidget *new_widget = this->drawBoard(solved_board);
        this->layout()->replaceWidget(prev_widget, new_widget);
        this->board_widget = new_widget;
    });
    solve_button->setFixedSize(board_widget->width() - 140, 60);

    this->setFixedSize(board_widget->width() - 120, board_widget->height() + solve_button->height());
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(board_widget);
    layout->addWidget(solve_button);
}

QWidget* Board::drawBoard(QVector<QVector<char>> board)
{
    auto *new_board_widget = new QWidget();
    auto *board_layout = new QGridLayout(new_board_widget);
    QValidator *validator = new QIntValidator('0', '9', this);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            boxes[i][j] = new QLineEdit();
            boxes[i][j]->setAlignment(Qt::AlignCenter);
            boxes[i][j]->setValidator(validator);
            boxes[i][j]->setFixedHeight(50);
            boxes[i][j]->setFixedWidth(50);

            if(board[i][j] != '.')
            {
                boxes[i][j]->setText(QString(board[i][j]));
                boxes[i][j]->setReadOnly(true);
            }

            board_layout->addWidget(boxes[i][j], i, j);
        }
    }

    return new_board_widget;
}

Board::~Board()
{
    future.waitForFinished();
}

Board::Board(QWidget *parent)
{
    board_values = QVector<QVector<char>>(9, QVector<char>(9, '.'));
    board_widget = drawBoard(board_values);

    QPushButton *solve_button = new QPushButton("Solve");
    connect(solve_button, &QPushButton::clicked, [this]()
    {
        getNewBoard();
        Solver *solver = new Solver();
        solver->solveSudoku(board_values);
        this->layout()->replaceWidget(board_widget, drawBoard(solver->getBoard()));

    });
    solve_button->setFixedSize(board_widget->width() - 140, 60);

    this->setFixedSize(board_widget->width() - 120, board_widget->height() + solve_button->height());
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(board_widget);
    layout->addWidget(solve_button);
}

void Board::getNewBoard()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(!boxes[i][j]->text().isEmpty())
            {
                board_values[i][j] = boxes[i][j]->text().toStdString()[0];
            }
            else
            {
                board_values[i][j] = '.';
            }
        }
    }
}
