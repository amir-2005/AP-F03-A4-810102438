#ifndef BOX_HPP_INCLUDE
#define BOX_HPP_INCLUDE

#include "Card.hpp"
#include <memory>
#include <list>

class Box
{
public:
    void addToCards(shared_ptr<Card> card);
    void sendToNext(shared_ptr<Card> card, Box *box);
    void sendToPerv(shared_ptr<Card> card, Box *box);
    list<shared_ptr<Card>> getCards(int n);
    int cardsNumber();

private:
    list<shared_ptr<Card>> cards;
};

#endif