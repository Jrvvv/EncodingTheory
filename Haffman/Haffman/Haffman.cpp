#include "Haffman.h"

Message::Message(double probability, long id) : m_probability(probability), m_id(id)
{
    setChildrens();
}

Message::Message(Message *msg1, Message *msg2)
{
    m_probability = msg1->m_probability + msg2->probability();
    setChildrens(msg1, msg2);
    m_id = 0;
}

Message::Message(const Message& msg) : m_left(msg.left()),
                                       m_right(msg.right()),
                                       m_probability(msg.probability()),
                                       m_id(msg.id())
{}

std::pair<Message*, Message*> Message::childrensPair() const
{
    return std::pair<Message*, Message*>(m_left, m_right);
}

void Message::setChildrens(Message *msg1, Message *msg2)
{
    if (msg1 && msg2) {
        if (msg1->m_probability < msg2->m_probability) {
            Message* temp = msg1;
            msg1 = msg2;
            msg2 = temp;
        }
    }

    m_left = msg1;
    m_right = msg2;
}

double Message::probability() const
{
    return m_probability;
}

void Message::setProbability(double newProbability)
{
    m_probability = newProbability;
}

Message *Message::left() const
{
    return m_left;
}

void Message::setLeft(Message *newLeft)
{
    m_left = newLeft;
}

Message *Message::right() const
{
    return m_right;
}

void Message::setRight(Message *newRight)
{
    m_right = newRight;
}

long Message::id() const
{
    return m_id;
}

void Message::setId(long newId)
{
    m_id = newId;
}
