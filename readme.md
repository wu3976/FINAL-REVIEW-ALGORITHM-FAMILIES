# DIFFERENT ALGORITHMS ON COIN CHANGE PROBLEM
This demo contains 4 algorithms: Dynamic Programming, Branch & Bound, Greedy and Brute force. 
Compile: 
```
g++ -std=c++11 coin_change_problem.cpp -o coin
```
Run:
```
./coin [CHANGE_TARGET] <[COINS_SEQ]>
```
CHANGE_TARGET: the amount of change to make
COINS_SEQ: a set of coins available

## Update: added a bottom-top demo of knight-move problem
Compile: 
```
g++ -std=c++11 knight_move.cpp -o knight
```
Run:
```
./knight [BOARDSIZE] [STEPS] (optional)[PRINT]
```
BOARDSIZE: side length of chessboard
STEPS: step to proceed
PRINT: optional, set to non-zero to enable printing partial results
