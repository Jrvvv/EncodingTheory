#include "HaffmanFuncs.h"

static bool compareMessages(Message msg1, Message msg2);
static void printComb(Message msg);

static void printCode();
static void printMsgs(const std::vector<Message> msg_v);

static std::vector<int> code;

void haffmanCode(const std::vector<double> &probabilities)
{
    auto msgArray = initMessages(probabilities);
    msgArray = doubleSizeCoding(msgArray);
    Message topMsg = buildTree(msgArray);
    print(&topMsg, 0, NONE);
}

std::vector<Message> initMessages(const std::vector<double> &probabilities)
{
    std::vector<Message> mssgs;
    long cntr_id = 1;
    for (auto probability : probabilities) {
        mssgs.push_back(Message(probability, cntr_id));
        cntr_id++;
    }
    return mssgs;
}

std::vector<Message> doubleSizeCoding(const std::vector<Message>& messages)
{
    std::vector<Message> mssgs;
    int N = messages.size();

    for (int i = 0; i < N; i++) {
        int cntr_id  = messages[i].id();
        Message msg;
        for (int j = 0; j < N; j++) {
            cntr_id &= ~(0xFFFF << 16);
            cntr_id |= (messages[j].id() << 16);
            msg = Message(messages[i].probability() * messages[j].probability(), cntr_id);
            mssgs.push_back(msg);
        }
    }

    return mssgs;
}

Message buildTree(std::vector<Message> &messages)
{
    while (messages.size() > 1) {
        sort(messages.begin(), messages.end(), compareMessages);
        printMsgs(messages);
        Message* msg1 = new Message(messages.back());
        messages.pop_back();
        Message* msg2 = new Message(messages.back());
        messages.pop_back();
        messages.push_back(Message(msg1, msg2));
    }

    return messages.back();
}

void print(Message *n, int u, eDrctn rl)
{

    if (!n) {
        printCode();
        code.pop_back();
        return;
    }

    if (rl == LEFT) {
        code.push_back(1);
    } else if (rl == RIGHT) {
        code.push_back(0);
    }

    if (!n->left()) {
        printComb(*n);
    }

    u--;
    print(n->left(), ++u, LEFT);
    if (n->right()) {
        print(n->right(), ++u, RIGHT);
        if (u != 0) {
            code.pop_back();
        }
    }

}


// --------------------------- S T A T I C ---------------------------
static bool compareMessages(Message msg1, Message msg2)
{
    return (msg1.probability() > msg2.probability());
}

static void printComb(Message msg) {
    std::cout << "y { ";
    for (int i = 0; i < 2; i++) {
        std::cout << ((msg.id() >> 16*i) & 0xFFFFL) << " ";
    }
    std::cout << "}: " << msg.probability() << " | ";
}

static void printMsgs(const std::vector<Message> msg_v) {
    for (auto msg : msg_v) {
        printComb(msg);
        std::cout << std::endl;
    }
    std::cout << " ______________________ ";
    std::cout << std::endl;
}

static void printCode() {        
    for (auto dig : code)
    {
        std::cout << dig;
    }
    std::cout << std::endl;
}
