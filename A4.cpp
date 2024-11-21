#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Card
{
public:
    Card(string q, string a, int w = 0)
    {
        question = q;
        answer = a;
        wrong_answers = w;
    }

    string getQuestion() { return question; }

    string getAnswer() { return answer; }

    void incWrongAns() { wrong_answers += 1; }

    int getWrongAns() { return wrong_answers; }

    void forgetWrongAns() { wrong_answers = 0; }

private:
    string question;
    string answer;
    int wrong_answers;
};


int main()
{

    return 1;
}