#include "Box.hpp"

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

int Box::cardsNumber() { return cards.size(); }