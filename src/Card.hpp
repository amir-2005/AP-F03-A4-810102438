#ifndef CARD_HPP_INCLUDE
#define CARD_HPP_INCLUDE

#include <string>
using namespace std;

class Card
{
public:
    Card(string q, string a, int w = 0);
    string getQuestion();
    string getAnswer();
    void incWrongAns();
    int getWrongAns();
    void forgetWrongAns();
    bool operator==(const Card &other);
    bool is_reviewed = false;

private:
    string question;
    string answer;
    int wrong_answers;
};

#endif