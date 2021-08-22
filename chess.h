#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class Chess {
public:

    Chess() {
        chessBoard.resize(8);
        for (int i = 0; i < 8; i++)
            chessBoard[i].resize(8);

        chessBoard = { {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
                       {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                       {'.', '.', '.', '.', '.', '.', '.', '.'},
                       {'.', '.', '.', '.', '.', '.', '.', '.'},
                       {'.', '.', '.', '.', '.', '.', '.', '.'},
                       {'.', '.', '.', '.', '.', '.', '.', '.'},
                       {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                       {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'} };

        lastMove = '\0';
        isWhiteMove = true;

        blackLeftRookMoved = false;
        blackRightRookMoved = false;
        whiteLeftRookMoved = false;
        whiteRightRookMoved = false;
        blackKingMoved = false;
        whiteKingMoved = false;
        isCheckAllMove = false;

        moveNum = 0;

        history.push_back(*this);
    }

    // method
    bool checkStalemate();
    bool checkMate();
    void undoMove();
    void printBoard();
    void makeMove(const std::string& move);
    std::vector <std::string> getAllMove();

    //var 
    std::vector <std::vector<char>> chessBoard;
    bool isWhiteMove;

private:
    // method
    bool checkStraight(const std::string& move);
    bool checkMove(const std::string& move, const bool& isWhiteMove);
    std::vector <std::string> getSomeMove(const bool& isWhiteMove);
    bool checkCheck();

    // var
    int moveNum;

    std::vector <Chess> history;
    std::string lastMove;

    bool blackLeftRookMoved;
    bool isCheckAllMove;
    bool blackRightRookMoved;
    bool whiteLeftRookMoved;
    bool whiteRightRookMoved;
    bool blackKingMoved;
    bool whiteKingMoved;

    int kingMove[16] = { 1, 0, 1, -1, -1, 0, -1, 1, 0, 1, 0, -1, 1, 1, -1, -1 };
    int knightMove[16] = { 1, -2, 1, 2, -1, -2, -1, 2, 2, -1, 2, 1, -2, -1, -2, 1 };
    int pawnMove[16] = { +1, 0, +2, 0, +1, +1, +1, -1, -1, 0, -2, 0, -1, +1, -1, -1 };
};

// unvisible method


bool Chess::checkStraight(const std::string& move) {
    int diff_x = 0;
    int diff_y = 0;
    int x = (move[0] - 96);
    int y = (move[1] - '0');

    if ((move[2] - 96) - (move[0] - 96) < 0)
        diff_x = -1;
    if ((move[2] - 96) - (move[0] - 96) > 0)
        diff_x = 1;
    if ((move[3] - '0') - (move[1] - '0') < 0)
        diff_y = -1;
    if ((move[3] - '0') - (move[1] - '0') > 0)
        diff_y = 1;

    do {
        x += diff_x;
        y += diff_y;

        if (x == (move[2] - 96) && y == (move[3] - '0'))
            return true;
    } while (chessBoard[8 - y][x - 1] == '.');

    return false;
}

bool Chess::checkStalemate() {
    std::vector <std::string> allMove = getAllMove();

    if (allMove.size() == 0 && !checkCheck())
        return true;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard[i][j] != 'K' && chessBoard[i][j] != 'k' && chessBoard[i][j] != '.')
                return false;
        }
    }

    return true;
}

bool Chess::checkMove(const std::string& move, const bool& isWhiteMove) {
    if ((move[0] - 96) > 8 || (move[0] - 96) <= 0)
        return false;
    else if ((move[1] - '0') > 8 || (move[1] - '0') <= 0)
        return false;
    else if ((move[2] - 96) > 8 || (move[2] - 96) <= 0)
        return false;
    else if ((move[3] - '0') > 8 || (move[3] - '0') <= 0)
        return false;

    else if ((move[0] - 96) == (move[2] - 96) && (move[1] - '0') == (move[3] - '0'))
        return false;
    else if (isWhiteMove == 0 && chessBoard['8' - move[1]][move[0] - 'a'] > 'A' && chessBoard['8' - move[1]][move[0] - 'a'] < 'Z')
        return false;
    else if (isWhiteMove == 1 && chessBoard['8' - move[1]][move[0] - 'a'] > 'a' && chessBoard['8' - move[1]][move[0] - 'a'] < 'z')
        return false;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] < 'Z' && chessBoard['8' - move[1]][move[0] - 'a'] > 'A' && chessBoard['8' - move[3]][move[2] - 'a'] < 'Z' && chessBoard['8' - move[3]][move[2] - 'a'] > 'A')
        return false;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] < 'z' && chessBoard['8' - move[1]][move[0] - 'a'] > 'a' && chessBoard['8' - move[3]][move[2] - 'a'] < 'z' && chessBoard['8' - move[3]][move[2] - 'a'] > 'a')
        return false;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] == '.')
        return false;

    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'K' || chessBoard['8' - move[1]][move[0] - 'a'] == 'k') {
        if (abs((move[0] - 96) - ((move[2] - 96))) <= 1 && abs((move[1] - '0') - ((move[3] - '0'))) <= 1)
            return true;
    }

    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'n' || chessBoard['8' - move[1]][move[0] - 'a'] == 'N') {
        if (abs((move[0] - 96) - ((move[2] - 96))) == 1 && abs((move[1] - '0') - ((move[3] - '0'))) == 2)
            return true;
        else if (abs((move[0] - 96) - ((move[2] - 96))) == 2 && abs((move[1] - '0') - ((move[3] - '0'))) == 1)
            return true;
    }

    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'r' || chessBoard['8' - move[1]][move[0] - 'a'] == 'R') {
        if (((move[0] - 96) - ((move[2] - 96)) == 0 || (move[1] - '0') - ((move[3] - '0')) == 0)) {
            if (checkStraight(move))
                return true;
        }
    }

    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'b' || chessBoard['8' - move[1]][move[0] - 'a'] == 'B') {
        if (((move[1] - '0') - ((move[3] - '0')) != 0 && (move[0] - 96) - ((move[2] - 96)) != 0))
            return checkStraight(move);
    }

    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'q' || chessBoard['8' - move[1]][move[0] - 'a'] == 'Q')
        return checkStraight(move);

    if (chessBoard['8' - move[1]][move[0] - 'a'] == 'p' || chessBoard['8' - move[1]][move[0] - 'a'] == 'P') {
        if (chessBoard['8' - move[3]][move[2] - 'a'] == '.' && (move[0] - 96) - ((move[2] - 96)) == 0 && (isWhiteMove == 1 && (move[1] - '0') - ((move[3] - '0')) == -1 || isWhiteMove == 0 && (move[1] - '0') - ((move[3] - '0')) == 1))
            return true;
        else if (chessBoard['8' - move[3]][move[2] - 'a'] == '.' && (move[0] - 96) - ((move[2] - 96)) == 0 && ((move[1] - '0') == 2 || (move[1] - '0') == 7) && ((isWhiteMove == 1 && (move[1] - '0') - ((move[3] - '0')) == -2 && chessBoard[8 - (move[1] - '0') - 1][(move[0] - 96) - 1] == '.') || (isWhiteMove == 0 && (move[1] - '0') - ((move[3] - '0')) == 2 && chessBoard[8 - (move[1] - '0') + 1][(move[0] - 96) - 1] == '.')))
            return true;
        else if (chessBoard['8' - move[3]][move[2] - 'a'] != '.' && abs((move[0] - 96) - ((move[2] - 96))) == 1 && (isWhiteMove == 1 && (move[1] - '0') - ((move[3] - '0')) == -1 || isWhiteMove == 0 && (move[1] - '0') - ((move[3] - '0')) == 1))
            return true;
        if (moveNum > 0) {
            if (chessBoard[8 - (lastMove[3] - '0')][lastMove[2] - 'a'] == 'p' && (lastMove[3] - '0') - (lastMove[1] - '0') == -2 && abs((move[0] - 96) - (lastMove[2] - 96)) == 1 && (move[1] - '0') == lastMove[3] - '0' && (move[2] - 96) == lastMove[2] - 96 && (move[3] - '0') == lastMove[1] - '0' - 1)
                return true;
            else if (chessBoard[8 - (lastMove[3] - '0')][lastMove[2] - 'a'] == 'P' && (lastMove[3] - '0') - (lastMove[1] - '0') == 2 && abs((move[0] - 96) - (lastMove[2] - 96)) == 1 && (move[1] - '0') == lastMove[3] - '0' && (move[2] - 96) == lastMove[2] - 96 && (move[3] - '0') == lastMove[1] - '0' + 1)
                return true;
        }
    }

    return false;
}

bool Chess::checkCheck() {
    std::vector <std::string> someEnemyMove;
    std::string currentMove;

    if (isCheckAllMove)
        someEnemyMove = getSomeMove(isWhiteMove);
    else
        someEnemyMove = getSomeMove(!isWhiteMove);

    for (int i = 0; i < someEnemyMove.size(); i++) {
        currentMove = someEnemyMove[i];

        if (chessBoard[8 - currentMove[3] + '0'][currentMove[2] - 97] == 'k')
            return true;

        if (chessBoard[8 - currentMove[3] + '0'][currentMove[2] - 97] == 'K')
            return true;
    }

    return false;
}

bool Chess::checkMate() {
    std::vector <std::string> allMove = getAllMove();

    if (allMove.size() == 0 && checkCheck())
        return true;
    return false;
}

std::vector <std::string> Chess::getSomeMove(const bool& isWhiteMove) {

    std::vector <std::string> someMove;
    std::string move = "xxxx";

    for (int x_from = 1; x_from <= 8; x_from++) {
        for (int y_from = 1; y_from <= 8; y_from++) {
            move[0] = char(y_from + 'a' - 1);
            move[1] = char(x_from + '0');

            if (chessBoard[8 - x_from][y_from - 1] == 'P') {
                for (int i = 0; i < 8; i = i + 2) {
                    move[2] = char(y_from + 'a' - 1 + pawnMove[i + 1]);
                    move[3] = char(x_from + '0' + pawnMove[i]);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
            }

            if (chessBoard[8 - x_from][y_from - 1] == 'p') {
                for (int i = 8; i < 16; i = i + 2) {
                    move[2] = char(y_from + 'a' - 1 + pawnMove[i + 1]);
                    move[3] = char(x_from + '0' + pawnMove[i]);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
            }

            if (chessBoard[8 - x_from][y_from - 1] == 'K' || chessBoard[8 - x_from][y_from - 1] == 'k') {
                for (int i = 0; i < 16; i = i + 2) {
                    move[2] = char(y_from + 'a' - 1 + kingMove[i]);
                    move[3] = char(x_from + '0' + kingMove[i + 1]);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
            }

            if (chessBoard[8 - x_from][y_from - 1] == 'N' || chessBoard[8 - x_from][y_from - 1] == 'n') {
                for (int i = 0; i < 16; i = i + 2) {
                    move[2] = char(y_from + 'a' - 1 + knightMove[i]);
                    move[3] = char(x_from + '0' + knightMove[i + 1]);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
            }

            if (chessBoard[8 - x_from][y_from - 1] == 'R' || chessBoard[8 - x_from][y_from - 1] == 'r') {
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 + i);
                    move[3] = char(x_from + '0');
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 - i);
                    move[3] = char(x_from + '0');
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1);
                    move[3] = char(x_from + '0' + i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1);
                    move[3] = char(x_from + '0' - i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
            }

            if (chessBoard[8 - x_from][y_from - 1] == 'B' || chessBoard[8 - x_from][y_from - 1] == 'b') {
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 + i);
                    move[3] = char(x_from + '0' + i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 - i);
                    move[3] = char(x_from + '0' - i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 - i);
                    move[3] = char(x_from + '0' + i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 + i);
                    move[3] = char(x_from + '0' - i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
            }

            if (chessBoard[8 - x_from][y_from - 1] == 'Q' || chessBoard[8 - x_from][y_from - 1] == 'q') {
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 + i);
                    move[3] = char(x_from + '0' + i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 - i);
                    move[3] = char(x_from + '0' - i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 - i);
                    move[3] = char(x_from + '0' + i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 + i);
                    move[3] = char(x_from + '0' - i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 + i);
                    move[3] = char(x_from + '0');
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1 - i);
                    move[3] = char(x_from + '0');
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1);
                    move[3] = char(x_from + '0' + i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
                for (int i = 1; i < 8; i++) {
                    move[2] = char(y_from + 'a' - 1);
                    move[3] = char(x_from + '0' - i);
                    if (checkMove(move, isWhiteMove))
                        someMove.push_back(move);
                }
            }
        }
    }

    return someMove;
}

// visible method

void Chess::printBoard() {
    std::cout << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << "  ";
        for (int j = 0; j < 8; j++) {
            std::cout << chessBoard[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << " " << std::endl << "   a b c d e f g h " << std::endl;
}

void Chess::undoMove() {

    Chess old_game = history[history.size() - 1];

    this->blackKingMoved = old_game.blackKingMoved;
    this->blackLeftRookMoved = old_game.blackLeftRookMoved;
    this->blackRightRookMoved = old_game.blackRightRookMoved;
    this->chessBoard = old_game.chessBoard;
    this->isWhiteMove = old_game.isWhiteMove;
    this->lastMove = old_game.lastMove;
    this->moveNum = old_game.moveNum;
    this->whiteKingMoved = old_game.whiteKingMoved;
    this->whiteLeftRookMoved = old_game.whiteLeftRookMoved;
    this->whiteRightRookMoved = old_game.whiteRightRookMoved;
    this->isCheckAllMove = old_game.isCheckAllMove;

}

std::vector <std::string> Chess::getAllMove() {
    std::vector <std::string> someMove = getSomeMove(isWhiteMove);
    std::vector <std::string> someEnemyMove = getSomeMove(!isWhiteMove);
    std::vector <std::string> allMove;

    bool isPointCheck[10] = { };
    std::string currentMove;

    for (int i = 0; i < someEnemyMove.size(); i++) {
        currentMove = someEnemyMove[i];
        if (currentMove[2] == 'b' && currentMove[3] == '8')
            isPointCheck[0] = true;
        if (currentMove[2] == 'c' && currentMove[3] == '8')
            isPointCheck[1] = true;
        if (currentMove[2] == 'd' && currentMove[3] == '8')
            isPointCheck[2] = true;

        if (currentMove[2] == 'g' && currentMove[3] == '8')
            isPointCheck[3] = true;
        if (currentMove[2] == 'f' && currentMove[3] == '8')
            isPointCheck[4] = true;

        if (currentMove[2] == 'b' && currentMove[3] == '1')
            isPointCheck[5] = true;
        if (currentMove[2] == 'c' && currentMove[3] == '1')
            isPointCheck[6] = true;
        if (currentMove[2] == 'd' && currentMove[3] == '1')
            isPointCheck[7] = true;

        if (currentMove[2] == 'g' && currentMove[3] == '1')
            isPointCheck[8] = true;
        if (currentMove[2] == 'f' && currentMove[3] == '1')
            isPointCheck[9] = true;
    }

    if (!isWhiteMove) {
        if (!blackKingMoved && !blackLeftRookMoved && chessBoard[0][1] == '.' && chessBoard[0][2] == '.' && chessBoard[0][3] == '.' && !isPointCheck[0] && !isPointCheck[1] && !isPointCheck[2] && chessBoard[0][4] == 'k' && chessBoard[0][0] == 'r')
            allMove.push_back("e8c8");
        if (!blackKingMoved && !blackRightRookMoved && chessBoard[0][6] == '.' && chessBoard[0][5] == '.' && !isPointCheck[3] && !isPointCheck[4] && chessBoard[0][4] == 'k' && chessBoard[0][7] == 'r')
            allMove.push_back("e8g8");
    }
    else {
        if (!whiteKingMoved && !whiteLeftRookMoved && chessBoard[7][1] == '.' && chessBoard[7][2] == '.' && chessBoard[7][3] == '.' && !isPointCheck[5] && !isPointCheck[6] && !isPointCheck[7] && chessBoard[7][4] == 'K' && chessBoard[7][0] == 'R')
            allMove.push_back("e1c1");
        if (!whiteKingMoved && !whiteRightRookMoved && chessBoard[7][6] == '.' && chessBoard[7][5] == '.' && !isPointCheck[8] && !isPointCheck[9] && chessBoard[7][4] == 'K' && chessBoard[7][7] == 'R')
            allMove.push_back("e1g1");
    }

    isCheckAllMove = true;
    for (int i = 0; i < someMove.size(); i++) {
        currentMove = someMove[i];

        makeMove(currentMove);
        if (!checkCheck())
            allMove.push_back(currentMove);
        undoMove();
    }
    isCheckAllMove = false;

    return allMove;
}

void Chess::makeMove(const std::string& move) {
    history.pop_back();
    history.push_back(*this);

    if (!isCheckAllMove) {
        std::vector <std::string> allMove = getAllMove();

        for (int i = 0; i < allMove.size(); i++) {
            if (move == allMove[i])
                break;
            if (i == allMove.size() - 1)
                throw std::exception("Wrong Move");
        } // check player's move
    }

    if ((move[1] - '0') == 1 && (move[0] - 96) == 5 && (move[2] - 96) == 7 && (move[3] - '0') == 1 && move == "e1g1" && chessBoard['8' - move[1]][move[0] - 'a'] == 'K') {
        chessBoard[7][5] = 'R';
        chessBoard[7][7] = '.';
        whiteKingMoved = true;
    }

    else if ((move[1] - '0') == 1 && (move[0] - 96) == 5 && (move[2] - 96) == 3 && (move[3] - '0') == 1 && move == "e1c1" && chessBoard['8' - move[1]][move[0] - 'a'] == 'K') {
        chessBoard[7][3] = 'R';
        chessBoard[7][0] = '.';
        whiteKingMoved = true;
    }

    else if ((move[1] - '0') == 8 && (move[0] - 96) == 5 && (move[2] - 96) == 7 && (move[3] - '0') == 8 && move == "e8g8" && chessBoard['8' - move[1]][move[0] - 'a'] == 'k') {
        chessBoard[0][5] = 'r';
        chessBoard[0][7] = '.';
        blackKingMoved = true;
    }
    else if ((move[1] - '0') == 8 && (move[0] - 96) == 5 && (move[2] - 96) == 3 && (move[3] - '0') == 8 && move == "e8c8" && chessBoard['8' - move[1]][move[0] - 'a'] == 'k') {
        chessBoard[0][3] = 'r';
        chessBoard[0][0] = '.';
        blackKingMoved = true;
    }
    // move rook in castling

    if (chessBoard['8' - move[1]][move[0] - 'a'] == 'r' && (move[0] - 96) == 1)
        blackLeftRookMoved = true;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'r' && (move[0] - 96) == 8)
        blackRightRookMoved = true;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'R' && (move[0] - 96) == 1)
        whiteLeftRookMoved = true;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'R' && (move[0] - 96) == 8)
        whiteRightRookMoved = true;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'k')
        blackKingMoved = true;
    else if (chessBoard['8' - move[1]][move[0] - 'a'] == 'K')
        whiteKingMoved = true;
    // check for castling

    if (moveNum > 0) {
        if ((chessBoard['8' - move[1]][move[0] - 'a'] == 'P' || chessBoard['8' - move[1]][move[0] - 'a'] == 'p') && (abs(move[1] - move[3]) == 1) && (abs(move[0] - move[2]) == 1) && (chessBoard[8 - (lastMove[3] - '0')][(lastMove[2] - 'a')] == 'p' || chessBoard[8 - (lastMove[3] - '0')][(lastMove[2] - 'a')] == 'P') && (abs(lastMove[3] - lastMove[1]) == 2) && abs(move[3] - lastMove[3]) == 1)
            chessBoard[8 - (lastMove[3] - '0')][(lastMove[2] - 'a')] = '.';
    }

    chessBoard['8' - move[3]][move[2] - 'a'] = chessBoard['8' - move[1]][move[0] - 'a'];
    chessBoard['8' - move[1]][move[0] - 'a'] = '.';

    if (chessBoard['8' - move[3]][move[2] - 'a'] == 'P' && (move[3] - '0') == 8)
        chessBoard['8' - move[3]][move[2] - 'a'] = 'Q';

    if (chessBoard['8' - move[3]][move[2] - 'a'] == 'p' && (move[3] - '0') == 1)
        chessBoard['8' - move[3]][move[2] - 'a'] = 'q';

    // move piece

    lastMove = move;
    isWhiteMove = !isWhiteMove;
    moveNum++;
}
