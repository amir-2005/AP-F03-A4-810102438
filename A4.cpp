#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const std::string ADD_COMMAND = "add_flashcard";
const std::string REVIEW_COMMAND = "review_today";
const std::string STREAK_COMMAND = "streak";
const std::string NEXTDAY_COMMAND = "next_day";
const std::string REPORT_COMMAND = "get_report";
const std::string PROGRESS_COMMAND = "get_progress_report";

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

class Leitner
{
public:

    void getFlashcards(string input)
    {
        int n = stoi(input.substr(ADD_COMMAND.size() + 1));
        string question, answer;

        for (int i = 0; i < n; i++)
        {
            getline(cin, question);
            getline(cin, answer);
            addNewCard(question, answer);
        }
        cout << "flashcards added to the daily box" << endl;
    }

private:
    Box daily;
    Box three_day;
    Box weekly;
    Box monthly;
    int day = 1;
    int streak = 0;

    void addNewCard(string question, string answer)
    {
        shared_ptr<Card> card_ptr = make_shared<Card>(question, answer);
        daily.addToCards(card_ptr);
    }

};

int main()
{
    Leitner main;
    string input;

    while (getline(cin, input))
    {
        if (input.find(ADD_COMMAND) != string::npos)
        {
            main.getFlashcards(input);
        }
        if (input.find(REVIEW_COMMAND) != string::npos)
        {

        }
        if (input.find(STREAK_COMMAND) != string::npos)
        {

        }
        if (input.find(NEXTDAY_COMMAND) != string::npos)
        {

        }
        if (input.find(REPORT_COMMAND) != string::npos)
        {

        }
        if (input.find(PROGRESS_COMMAND) != string::npos)
        {
            
        }
    }

    return 1;
}