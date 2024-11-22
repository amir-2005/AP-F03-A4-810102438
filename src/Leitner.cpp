#include "Leitner.hpp"

void Box::addToCards(shared_ptr<Card> card)
{
    card->forgetWrongAns();
    cards.push_back(card);
}

void Box::sendToNext(shared_ptr<Card> card, Box *box)
{
    cards.remove(card);
    if (box != nullptr) // it means that current box is monthly and cart will be discarded
        box->addToCards(card);
}

void Box::sendToPerv(shared_ptr<Card> card, Box *box)
{
    if (box != nullptr) // it means that current box is daily and cart cannot be removed
    {
        cards.remove(card);
        box->addToCards(card);
    }
}

list<shared_ptr<Card>> Box::getCards(int n)
{
    list<shared_ptr<Card>> sublist(cards.begin(), next(cards.begin(), n));
    return sublist;
}

void Leitner::showStreak()
{
    cout << "Your current streak is: " << streak << endl;
    cout << "Keep going!" << endl;
}

void Leitner::getFlashcards(int n)
{
    string question, answer;

    for (int i = 0; i < n; i++)
    {
        getline(cin, question);
        getline(cin, answer);
        addNewCard(question, answer);
    }
    cout << "flashcards added to the daily box" << endl;
}

void Leitner::reviewToday(int number)
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

    finishReviewMessage();
    been_reviewed = true;
    streak++;
}

void Leitner::nextDay()
{
    moveUnrevieweds();
    day++;
    if (!been_reviewed)
        streak = 0;
    been_reviewed = false;
    correct_wrong_number.emplace_back(0, 0);
    nextDayMessage();
}

void Leitner::printReport(int start, int end)
{
    if (start == end)
        cout << "Day: " << start << endl;
    else
        cout << "Day: " << start << " to " << end << endl;

    int total_correct = 0;
    int total_wrong = 0;

    for (int i = start - 1; i < end; i++)
    {
        total_correct += correct_wrong_number[i].first;
        total_wrong += correct_wrong_number[i].second;
    }

    cout << "Correct Answers: " << total_correct << endl;
    cout << "Incorrect Answers: " << total_wrong << endl;
    cout << "Total: " << total_correct + total_wrong << endl;
}

void Leitner::printProgressReport()
{
    int total_participate = 0;
    for (auto i : correct_wrong_number)
    {
        if (i.first != 0 || i.second != 0)
            total_participate++;
    }

    cout << "Challenge Progress Report:" << endl
         << endl;
    cout << "Day of the Challenge: " << day << endl;
    cout << "Streak: " << streak << endl;
    cout << "Total Days Participated: " << total_participate << endl;
    cout << "Mastered Flashcards: " << mastered_number << endl;
    cout << endl
         << "Keep up the great work! You're making steady progress toward mastering your flashcards." << endl;
}

void Leitner::addNewCard(string question, string answer)
{
    shared_ptr<Card> card_ptr = make_shared<Card>(question, answer);
    daily.addToCards(card_ptr);
}

void Leitner::askQuestions(list<shared_ptr<Card>> cards, Box *box, Box *next, Box *perv)
{
    string answer;
    for (auto card : cards)
    {
        if (card->is_reviewed == true)
            continue;
        card->is_reviewed = true;

        cout << "Flashcard: " << card->getQuestion() << endl
             << "Your answer: ";

        getline(cin, answer);

        if (answer == card->getAnswer())
        {
            correct_wrong_number.back().first += 1;
            cout << endl
                 << "Your answer was correct! Well done, keep it up!" << endl;
            box->sendToNext(card, next);
            if (next == nullptr) // it means the card is going out from monthly box
                mastered_number += 1;
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

void Leitner::finishReviewMessage()
{
    cout << "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!" << endl;
}

void Leitner::nextDayMessage()
{
    cout << "Good morning! Today is day " << day << " of our journey." << endl;
    cout << "Your current streak is: " << streak << endl;
    cout << "Start reviewing to keep your streak!" << endl;
}

void Leitner::moveUnrevieweds()
{
    if (day % 3 == 0)
        for (auto card : three_day.getCards(three_day.cardsNumber()))
        {
            if (day % 3 == 0 && card->is_reviewed == false)
                three_day.sendToPerv(card, &daily);
        }

    if (day % 7 == 0)
        for (auto card : weekly.getCards(weekly.cardsNumber()))
        {
            if (card->is_reviewed == false)
                weekly.sendToPerv(card, &three_day);
        }

    if (day % 30 == 0)
        for (auto card : monthly.getCards(monthly.cardsNumber()))
        {
            if (card->is_reviewed == false)
                monthly.sendToPerv(card, &weekly);
        }

    for (auto card : daily.getCards(daily.cardsNumber()))
        card->is_reviewed = false;
    for (auto card : three_day.getCards(three_day.cardsNumber()))
        card->is_reviewed = false;
    for (auto card : weekly.getCards(weekly.cardsNumber()))
        card->is_reviewed = false;
    for (auto card : monthly.getCards(monthly.cardsNumber()))
        card->is_reviewed = false;
}