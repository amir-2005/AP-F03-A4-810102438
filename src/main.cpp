#include "Leitner.hpp"
#include "constants.hpp"
#include <sstream>

int main()
{
    Leitner main;
    string input;

    while (getline(cin, input))
    {
        if (input.find(ADD_COMMAND) != string::npos)
        {
            int n = stoi(input.substr(ADD_COMMAND.size() + 1));
            main.getFlashcards(n);
        }
        if (input.find(REVIEW_COMMAND) != string::npos)
        {
            int n = stoi(input.substr(REVIEW_COMMAND.size() + 1));
            main.reviewToday(n);
        }
        if (input.find(STREAK_COMMAND) != string::npos)
        {
            main.showStreak();
        }
        if (input.find(NEXTDAY_COMMAND) != string::npos)
        {
            main.nextDay();
        }
        if (input.find(REPORT_COMMAND) != string::npos)
        {
            istringstream stream(input.substr(REPORT_COMMAND.length()));
            int start, end;
            stream >> start >> end;
            main.printReport(start, end);
        }
        if (input.find(PROGRESS_COMMAND) != string::npos)
        {
            main.printProgressReport();
        }
    }

    return 1;
}