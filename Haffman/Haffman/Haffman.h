#ifndef HAFFMAN_H
#define HAFFMAN_H

#include <vector>
#include <algorithm>
#include <string>

class Message {
public:
    Message(double probability = 0, long id = 0);
    Message(Message* msg1, Message* msg2);
    Message(const Message&msg);

    std::pair<Message*, Message*>   childrensPair() const;
    void                            setChildrens(Message* msg1 = nullptr, Message* msg2 = nullptr);
    double                          probability() const;
    void                            setProbability(double newProbability);

    Message *left() const;
    void setLeft(Message *newLeft);
    Message *right() const;
    void setRight(Message *newRight);
    long id() const;
    void setId(long newId);

private:
    Message*    m_left;
    Message*    m_right;
    double      m_probability;
    long        m_id;
};

#endif // HAFFMAN_H
