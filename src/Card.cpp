#include "Card.hpp"

Card::Card(string q, string a, int w)
{
    question = q;
    answer = a;
    wrong_answers = w;
}

string Card::getQuestion() { return question; }

string Card::getAnswer() { return answer; }

void Card::incWrongAns() { wrong_answers += 1; }

int Card::getWrongAns() { return wrong_answers; }

void Card::forgetWrongAns() { wrong_answers = 0; }

bool Card::operator==(const Card &other)
{
    if (question == other.question && answer == other.answer)
        return true;
    return false;
}
