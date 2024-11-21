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

class Box
{
public:
    void addToCards(shared_ptr<Card> card)
    {
        card->forgetWrongAns();
        cards.push_back(card);
    }

    void sendToNext(shared_ptr<Card> card, Box *box)
    {
        cards.remove(card);
        if (box != nullptr) // it means that current box is monthly and cart will be discarded
            box->addToCards(card);
    }

    void sendToPerv(shared_ptr<Card> card, Box *box)
    {
        if (box != nullptr) // it means that current box is daily and cart cannot be removed
        {
            cards.remove(card);
            box->addToCards(card);
        }
    }

    int cardsNumber()
    {
        return cards.size();
    }

private:
    list<shared_ptr<Card>> cards;
};

int main()
{

    return 1;
}