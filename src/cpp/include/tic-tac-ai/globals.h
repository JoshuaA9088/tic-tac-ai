#ifndef GLOBALS_H
#define GLOBALS_H

class Pt
{
public:
    Pt()
    {
        x = 0;
        y = 0;
    }

    Pt(int x_, int y_)
    {
        x = x_;
        y = y_;
    };

    int x;
    int y;
};

class Index
{

public:
    Index()
    {
        i = 0;
        j = 0;
    }

    Index(int i_, int j_)
    {
        i = i_;
        j = j_;
    }

    int i = 0;
    int j = 0;
};

class Score
{

public:
    Score()
    {
        score = 0;
    }

    Score(Index i, int s_)
    {
        index = i;
        score = s_;
    }

    Index index;
    int score;
};

namespace constants
{

    const char X = 'X';
    const char O = 'O';
    const int start_y = 2, start_x = 2, w = 4, h = 2;
} // namespace constants

namespace minimax
{
    const char MAX = 'X';
    const char MIN = 'O';

    const Index default_best_move(0, 0);
} // namespace minimax

#endif
