#ifndef LEITNER_HPP_INCLUDE
#define LEITNER_HPP_INCLUDE

#include <iostream>
#include <string>
#include <vector>
#include "Box.hpp"

class Leitner
{
public:
    void showStreak();                // IO
    void getFlashcards(int n); // IO
    void reviewToday(int number);
    void nextDay();
    void printReport(int start, int end); // IO
    void printProgressReport();           // IO

private:
    Box daily;
    Box three_day;
    Box weekly;
    Box monthly;
    int day = 1;
    int streak = 0;
    bool been_reviewed = false;
    int mastered_number = 0;
    vector<pair<int, int>> correct_wrong_number = {{0, 0}};

    void addNewCard(string question, string answer);
    void askQuestions(list<shared_ptr<Card>> cards, Box *box, Box *next, Box *perv);    //IO
    void finishReviewMessage();     //IO
    void nextDayMessage();      //IO
    void moveUnrevieweds();
};


#endif