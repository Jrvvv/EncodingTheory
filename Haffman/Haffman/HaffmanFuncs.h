#ifndef HAFFMANFUNCS_H
#define HAFFMANFUNCS_H

#include "Haffman.h"
#include <iostream>

typedef enum eDrctn {
    LEFT = -1,
    NONE = 0,
    RIGHT = 1
} eDrctn;

class Message;

void haffmanCode(const std::vector<double> &probabilities);
std::vector<Message>    doubleSizeCoding (const std::vector<Message>& messages);
std::vector<Message>    initMessages     (const std::vector<double>& probabilities);
Message                 buildTree        (std::vector<Message>& messages);

void print(Message *n, int u, eDrctn rl);

#endif // HAFFMANFUNCS_H
