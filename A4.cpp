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

    list<shared_ptr<Card>> getCards(int n)
    {
        list<shared_ptr<Card>> sublist(cards.begin(), next(cards.begin(), n));
        return sublist;     
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

    void reviewToday(int number)
    {
        if (number != 0 && day % 30 == 0)
        {
            int n = monthly.cardsNumber();
            if (number <= n)
            {
                askQuestions(monthly.getCards(number), &monthly, nullptr, &weekly);
                number = 0;
            }
            else
            {
                askQuestions(monthly.getCards(n), &monthly, nullptr, &weekly);
                number -= n;
            }
        }
        if (number != 0 && day % 7 == 0)
        {
            int n = weekly.cardsNumber();
            if (number <= n)
            {
                askQuestions(weekly.getCards(number), &weekly, &monthly, &three_day);
                number = 0;
            }
            else
            {
                askQuestions(weekly.getCards(n), &weekly, &monthly, &three_day);
                number -= n;
            }
        }
        if (number != 0 && day % 3 == 0)
        {
            int n = three_day.cardsNumber();
            if (number <= n)
            {
                askQuestions(three_day.getCards(number), &three_day, &weekly, &daily);
                number = 0;
            }
            else
            {
                askQuestions(three_day.getCards(n), &three_day, &weekly, &daily);
                number -= n;
            }
        }
        if (number != 0)
            askQuestions(daily.getCards(number), &daily, &three_day, nullptr);

        cout << "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!" << endl;
        streak++;
    }

private:
    Box daily;
    Box three_day;
    Box weekly;
    Box monthly;
    int day = 1;
    int streak = 0;
    vector<pair<int, int>> correct_wrong_number = {{0, 0}};

    void addNewCard(string question, string answer)
    {
        shared_ptr<Card> card_ptr = make_shared<Card>(question, answer);
        daily.addToCards(card_ptr);
    }

    void askQuestions(list<shared_ptr<Card>> cards, Box *box, Box *next, Box *perv)
    {
        string answer;
        for (auto card : cards)
        {
            cout << "Flashcard: " << card->getQuestion() << endl
                 << "Your answer: ";
            getline(cin, answer);
            if (answer == card->getAnswer())
            {
                correct_wrong_number.back().first += 1;
                cout << endl
                     << "Your answer was correct! Well done, keep it up!" << endl;
                box->sendToNext(card, next);
            }
            else
            {
                correct_wrong_number.back().second += 1;
                cout << endl
                     << "Your answer was incorrect. Don't worry! The correct answer is: ";
                cout << card->getAnswer() << ". Keep practicing!" << endl;
                card->incWrongAns();
                if (card->getWrongAns() == 2)
                {
                    box->sendToPerv(card, perv);
                }
            }
        }
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