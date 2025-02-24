/******************************************************************************
 * main.cpp
 *
 *  Created on: Feb 07 2025
 *  Updated on: Feb 13 2025
 *      Author: OCdt Syed
 *
 *
 ******************************************************************************/

#include <iostream>
#include <string>
#include <random>
#include "Test.h"
#include "Queue.h"
#include "PostFixCalculator.h"

#define QUEUE_MAX_SIZE 15

using namespace std;

/** 
 * Prints the state of the queue along with a description.
 * @param queue The queue to print.
 * @param description A description of the current step.
 */
void printQueueStep(const Queue &queue, const string &description) {
    static int step = 0;
    cout << "Step #" << step << " " << description << "\n";
    queue.PrintQueue();
    step++;
}

/** 
 * Runs a simulation of arrivals and departures using a Queue.
 */
void simulation() {
    cout << "Creating a queue of size " << QUEUE_MAX_SIZE << "\n";
    Queue queue(QUEUE_MAX_SIZE);
    constexpr int targetArrivalDepartures = QUEUE_MAX_SIZE * 3;
    int member = 1;
    for (; member < 6; member++) {
        queue.Enqueue(member);
        printQueueStep(queue, "Initial Arrival #" + to_string(member));
    }

    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution dist(0., 1.);

    for (int i = 0; i <= targetArrivalDepartures; i++) {
        if (dist(mt) > 0.5) {
            if (queue.Enqueue(member)) {
                printQueueStep(queue, "Arrival #" + to_string(member) + " Inserted");
            } else {
                printQueueStep(queue, "Queue Full; " + to_string(member) + " Left");
            }
            member++;
        } else {
            if (int removedMember; queue.Dequeue(removedMember)) {
                printQueueStep(queue, "Processing #" + to_string(removedMember) + " successfully");
            } else {
                printQueueStep(queue, "Queue Empty; Processing Failed");
            }
        }
    }
}

/** 
 * Main function.
 */
int main() {
    cout << "-------------------------- Question 1 --------------------------\n";
    cout << "Queue Implemented\n";
    cout << "-------------------------- Question 2 --------------------------\n";
    cout << "Testing Queue:\n";
    Test::testQueue();
    cout << "-------------------------- Question 3 --------------------------\n";
    simulation();
    cout << "-------------------------- Question 4 --------------------------\n";
    cout << "Linked List Implemented\n";
    cout << "-------------------------- Question 5 --------------------------\n";
    cout << "Testing Linked List:\n";
    Test::testLinkedList();
    cout << "-------------------------- Question 6 --------------------------\n";
    cout << "Stack Implemented\n";
    cout << "-------------------------- Question 7 --------------------------\n";
    cout << "Testing Stack:\n";
    Test::testStack();
    cout << "-------------------------- Question 8 --------------------------\n";
    cout << "Postfix Calculator Implemented\n";
    cout << "Testing PostFixCalculator:\n";
    Test::testPostFixCalculator();
    cout << "--------------------------\n";
    cout << "Test PostFixCalculator Manually\n";
    for (;;) {
        try {
            string equation;
            cout << "Enter an equation:" << endl;
            cin >> equation;
            if (equation == "exit") {
                break;
            }
            cout << "Result: " << PostFixCalculator(equation) << endl;
        } catch (std::runtime_error &e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
