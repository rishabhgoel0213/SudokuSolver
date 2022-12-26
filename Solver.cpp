//
// Created by rishabh on 12/23/22.
//

#include "Solver.h"
#include <iostream>
#include <QDebug>
#include <QQueue>
#include <QMutex>
#include <iterator>
#include <utility>

bool Solver::solveSudoku(QVector<QVector<char>> board_values)
{
    board = new QVector<QVector<char>>(std::move(board_values));

    QVector<QSet<char>> squares(9);
    QVector<QSet<char>> columns(9);
    QVector<QSet<char>> rows(9);

    QVector<QPair<int, int>> empty_spots;

    QVector<QSet<char>> candidates;

    for(int j = 0; j < 9; j++)
    {
        for(int i = 0; i < 9; i++)
        {
            if(board->data()[i][j] != '.')
            {
                rows[i].insert(board->data()[i][j]);
                columns[j].insert(board->data()[i][j]);
                squares[Board::getSquare(qMakePair(i, j))].insert(board->data()[i][j]);
            }
            else
            {
                empty_spots.push_back(qMakePair(i, j));
            }
        }
    }

    QQueue<int> remove_indexes;

    while(!isFull(*board))
    {
        bool check = true;
        bool check2 = false;
        bool check3 = false;

        for(int i = 0; i < remove_indexes.size(); i++)
        {
            empty_spots.remove(remove_indexes.front());
            candidates.remove(remove_indexes.front());
            remove_indexes.pop_front();
        }

        size_t empty_spots_size = empty_spots.size();
        candidates.resize(empty_spots_size);

        //One Candidate Possibility
        for(int i = 0; i < empty_spots_size; i++)
        {
            QSet<char> candidate_list;
            for(int n = 1; n < 10; n++)
            {
                if(count(rows[empty_spots[i].first].begin(), rows[empty_spots[i].first].end(), char('0' + n)) == 0 && count(columns[empty_spots[i].second].begin(), columns[empty_spots[i].second].end(), char('0' + n)) == 0 && count(squares[Board::getSquare(empty_spots[i])].begin(), squares[Board::getSquare(empty_spots[i])].end(), char('0' + n)) == 0)
                {
                    candidate_list.insert(char('0' + n));
                }
            }
            qDebug() << candidate_list;
            candidates[i] = candidate_list;

            if(candidate_list.isEmpty())
            {
                qDebug() << i;
                return false;
            }

            if(candidate_list.size() == 1)
            {
                char val = *candidate_list.begin();
                board->data()[empty_spots[i].first][empty_spots[i].second] = val;
                rows[empty_spots[i].first].insert(val);
                columns[empty_spots[i].second].insert(val);
                squares[Board::getSquare(empty_spots[i])].insert(val);
                remove_indexes.push_back(i);
                check = false;
                printBoard(*board);
                emit solvedSquare();
                break;
            }
        }


        //Only option in row, column, or square for candidate
        if(check)
        {
            check2 = true;
            for (int i = 0; i < empty_spots_size; i++)
            {
                QSet<char> candidate_list_row = candidates[i];
                QSet<char> candidate_list_column = candidates[i];
                QSet<char> candidate_list_square = candidates[i];
                for (int j = 0; j < empty_spots_size; j++)
                {
                    if (i != j)
                    {
                        if (empty_spots[j].first == empty_spots[i].first)
                        {
                            candidate_list_row.subtract(candidates[j]);
                        }
                        if (empty_spots[j].second == empty_spots[i].second)
                        {
                            candidate_list_column.subtract(candidates[j]);
                        }

                        if (Board::getSquare(empty_spots[j]) == Board::getSquare(empty_spots[i]))
                        {
                            candidate_list_square.subtract(candidates[j]);
                        }
                    }
                }

                if (!candidate_list_row.empty())
                {
                    char val = *candidate_list_row.begin();
                    check2 = false;
                    board->data()[empty_spots[i].first][empty_spots[i].second] = val;
                    rows[empty_spots[i].first].insert(val);
                    columns[empty_spots[i].second].insert(val);
                    squares[Board::getSquare(empty_spots[i])].insert(val);
                    remove_indexes.push_back(i);
                    printBoard(*board);
                    emit solvedSquare();
                    break;
                }
                else if (!candidate_list_column.empty())
                {
                    char val = *candidate_list_column.begin();
                    check2 = false;
                    board->data()[empty_spots[i].first][empty_spots[i].second] = val;
                    rows[empty_spots[i].first].insert(val);
                    columns[empty_spots[i].second].insert(val);
                    squares[Board::getSquare(empty_spots[i])].insert(val);
                    remove_indexes.push_back(i);
                    printBoard(*board);
                    emit solvedSquare();
                    break;
                }
                else if (!candidate_list_square.empty())
                {
                    char val = *candidate_list_square.begin();
                    check2 = false;
                    board->data()[empty_spots[i].first][empty_spots[i].second] = val;
                    rows[empty_spots[i].first].insert(val);
                    columns[empty_spots[i].second].insert(val);
                    squares[Board::getSquare(empty_spots[i])].insert(val);
                    remove_indexes.push_back(i);
                    printBoard(*board);
                    emit solvedSquare();
                    break;
                }
            }
        }

        if(check2)
        {
            for(int i = 0; i < empty_spots_size; i++)
            {
                if(candidates[i].size() == 2)
                {
                    char val = *candidates[i].begin();
                    QVector<QVector<char>> board_copy = *board;
                    board_copy[empty_spots[i].first][empty_spots[i].second] = val;
                    qDebug() << val;
                    printBoard(board_copy);
                    auto *new_solve = new Solver();
                    if (new_solve->solveSudoku(board_copy))
                    {
                        board = new QVector<QVector<char>>(new_solve->getBoard());
                        printBoard(*board);
                        return true;
                    }
                    else
                    {
                        val = *std::next(candidates[i].begin(), 1);
                        board->data()[empty_spots[i].first][empty_spots[i].second] = val;
                        rows[empty_spots[i].first].insert(val);
                        columns[empty_spots[i].second].insert(val);
                        squares[Board::getSquare(empty_spots[i])].insert(val);
                        remove_indexes.push_back(i);
                        printBoard(*board);
                        emit solvedSquare();
                        break;
                    }

                }

            }
        }

    }
    return true;
}

bool Solver::isFull(QVector<QVector<char>> board)
{
    for(auto& b: board)
    {
        if(count(b.begin(), b.end(), '.') != 0)
        {
            return false;
        }
    }
    return true;
}

void Solver::printBoard(QVector<QVector<char>> board)
{
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

