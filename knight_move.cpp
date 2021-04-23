#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
// knight move problem
void getNextPos(size_t boardSize_in, size_t i_in, size_t j_in, vector<vector<int>> &nextPos){
    int boardSize = static_cast<int>(boardSize_in), i = static_cast<int>(i_in),
                j = static_cast<int>(j_in);
    int temp[8][2] = {{1, 2}, {2, 1}, {-1, 2}, {-2, 1},
                    {1, -2}, {2, -1}, {-1, -2}, {-2, -1}};
    for (int n = 0; n < 8; n++){
        int x = i + temp[n][0], y = j + temp[n][1];
        if (0 <= x && x < boardSize && 0 <= y && y < boardSize){
            nextPos.push_back(vector<int>{x, y});
        }
    }
}

void printBoard(vector<vector<uint32_t>> &board, size_t count){
    cout << "Step " << count << ":\n";
    for (auto &arr : board){
        for (auto ele : arr){
            cout << ele << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

uint32_t knightMoveBottomTop(size_t boardSize, uint32_t moves, bool p){
    vector<vector<uint32_t>> board(boardSize);
    for (size_t i = 0; i < board.size(); i++){
        board[i].resize(board.size());
        fill(board[i].begin(), board[i].end(), 0);
    }
    if (p){
        printBoard(board, 0);
    }
    vector<vector<uint32_t>> newBoard = board;
    board[0][0] = 1;
    for (uint32_t mvCount = 0; mvCount < moves; mvCount++){
        for (size_t i = 0; i < board.size(); i++){
            for (size_t j = 0; j < board[0].size(); j++){
                if (board[i][j]){
                    vector<vector<int>> nextPos;
                    getNextPos(boardSize, i, j, nextPos);
                    for (size_t idx = 0; idx < nextPos.size(); idx++){
                        size_t newX = static_cast<size_t>(nextPos[idx][0]),
                                newY = static_cast<size_t>(nextPos[idx][1]);
                        newBoard[newX][newY] += board[i][j];
                    }
                }
            }
        }
        board = newBoard;
        for (size_t i = 0; i < newBoard.size(); i++){
            fill(newBoard[i].begin(), newBoard[i].end(), 0);
        }
        if (p){
            printBoard(board, mvCount);
        }
    }
    return board[board.size() - 1][board.size() - 1];
}

int main(int argc, char **argv){
    if (argc != 3 && argc != 4){
        cerr << "cmd error. type -h to get help\n";
        exit(1);
    }
    for (int i = 0; i < argc; i++){
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
            cout << "usage: ./knight [BOARDSIZE] [STEPS] (optional)[PRINT]\n";
            return 0;
        }
    }
    bool print = false;
    if (argc == 4 && atoi(argv[3])){
        print = true;
    }
    if (atoi(argv[1]) <= 0 || atoi(argv[2]) < 0){
        cerr << "Invalid parameters\n";
        exit(1);
    }
    cout << knightMoveBottomTop(static_cast<size_t>(atoi(argv[1])),  static_cast<size_t>(atoi(argv[2])), print) << "\n";
}
