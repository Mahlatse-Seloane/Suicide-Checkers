#ifndef MOVE_H
#define MOVE_H

struct Move
{
    int moveFrom, moveTo, capture;

    bool checkEquality(Move checkMove) const
    {
        return (moveFrom == checkMove.moveFrom && moveTo == checkMove.moveTo && capture == checkMove.capture);
    }

    bool isCapture() const { return capture != 0; }
    void resetMove() { moveFrom = 0, moveTo = 0, capture = 0; }
};

#endif // MOVE_H
