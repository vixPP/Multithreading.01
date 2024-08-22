#include <iostream>
#include <thread>
#include <chrono>

using namespace std;


const int MAX_CLIENTS = 10; 
int clientCount = 0; 

void Add1() 
{
    while (clientCount < MAX_CLIENTS)
    {
        this_thread::sleep_for(chrono::seconds(1)); 
        if (clientCount < MAX_CLIENTS) 
        {
            clientCount++; 
            cout << clientCount << endl;
        }
    }
}

void sub1() 
{
    while (clientCount < MAX_CLIENTS)
    {
        this_thread::sleep_for(chrono::seconds(2));
        if (clientCount < MAX_CLIENTS)
        {
            clientCount--; 
            cout << clientCount << endl;
        }
    }
}

int main() 
{
    thread addThread(Add1);
    thread subThread(sub1);

    addThread.join();
    subThread.join();

    return 0;
}
