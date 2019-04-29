#pragma once

#include <iostream>

using namespace std;

#define SIZE 5
#define BLACK 'X'
#define WHITE 'O'

class Room
{
    private:
        uint32_t one;
        uint32_t two;
        uint32_t current;
        char piece[2];
        char board[SIZE][SIZE];
        char result;//X:第一个玩家赢  O:第二个玩家赢  E:平局  N:继续游戏

        pthread_mutex_t lock;
    public:
        Room(uint32_t &id1,uint32_t &id2)
        {
            piece[0] = 'X';
            piece[1] = 'O';
            memset(board,' ',sizeof(board));
            result = 'N';
            pthread_mutex_init(&lock,NULL);
        }
        void Board(string &_board)
        {
            for(auto i = 0; i < SIZE; i++)
            {
                for(auto j = 0; j < SIZE; j++)
                {
                    _board.push_back(board[i][j]);
                }
            }
        }
        ~Room()
        {
            pthread_mutex_destroy(&lock);
        }
};
