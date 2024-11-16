/*  Lab 33: Toll Plaza
    Objective:
        1. Add multiple lanes into the management system to simulate an entire plaza of toll booths
        2. Add the capability for a car at the rear of a lane to switch lanes

    Requirements:
        1. These are the additional requirements for this lab. These assume you have completed Lab 32 and have a working tool booth simulation.
        2. Add More Lanes:
            a. There are now 4 toll booth lanes at play. Use an array to hold the lanes. The array will be of type deque<Car>. When the simulation starts, pre-populate the lanes with 1-3 cars like before.Each time period will now have operations happening on all lines.
            b. Add Switching Lanes
            c. Any car at the end of any queue can switch lanes to a random lane that's not their original lane.
        3. Probabilities:
            a. The three possible operations and their probabilities are:
                - 46% probability that the car at the head of the queue pays its toll and leaves the queue
                - 39% probability that another car joins the queue
                - 15% probability that the rear car will shift lanes
            b. All these probability values need to be stored as constants defined in your program, never in hard-coding.
            c. If a lane is currently empty but there is still more time in the simulation, those probabilities will be just 50/50 if a new car enters the queue or not.
                Of course another car might shift lanes into it, but that's a different lane's business.
        4. Termination Criteria: Run the simulation for 20 time periods.
*/

#include <iostream>
#include <string>
#include <deque>
#include <array>
#include "Car.h"
using namespace std;

// variables for starting number of cars, liklihood of car paying, liklihood of new car joining line
const int NUM_INITIAL_CARS = 2, CHANCE_CAR_PAYS = 46, CHANCE_NEW_CAR_JOINS = 39, CHANCE_REAR_CHANGES_LANE = 15, CHANCE_JOIN_IF_EMPTY = 50;

// for simulation where car pays and joins queue are separate events
bool FrontCarPaid();
bool NewCarJoinsQueue();
// prints current queue
void CurrentQueueToConsole(deque<Car> &);

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // seed current time to rand()
    deque<Car> tollBooth = {};                       // empty toll booth line
    array<deque<Car>, 4> tollPlaza = {};
    int randNumber = 0;
    int count = 0;
    Car tempCar;
    string output = "";
    // deque<Car> plaza[4] = {}; // alternative option

    // initialize toll plaza
    cout << "Initial queue:\n";
    for (auto it = tollPlaza.begin(); it != tollPlaza.end(); it++)
    {
        // for each toll booth, initialize toll booth with 2 vehicles and output to console
        for (int i = 0; i < NUM_INITIAL_CARS; i++)
        {
            it->push_back(Car());
        }
        cout << "Lane " << ++count << ":\n";
        CurrentQueueToConsole(*it);
    }

    // run simulation for 20 iterations
    for (int i = 0; i < 20; i++)
    {
        // timeperiod
        cout << "Time: " << i + 1 << " - ";

        // for each lane in the toll plaza
        for (auto it = tollPlaza.begin(); it != tollPlaza.end(); it++)
        {
            // get random number to check toll booth events
            randNumber = (rand() % 100) + 1;

            if (randNumber <= CHANCE_CAR_PAYS) // car pays
            {
                /* code */
            } else if (randNumber <= CHANCE_CAR_PAYS + CHANCE_NEW_CAR_JOINS) // car joins
            {
                /* code */
            } else { // car switches

            }
            
            

        }

        // assumes either car pays OR car joins queue
        if (((rand() % 100) + 1) <= CHANCE_CAR_PAYS)
        {
            // car paid, get from front and pop with console output
            tempCar = tollBooth.front();
            tollBooth.pop_front();
            cout << "Car paid: ";
        }
        else
        {
            // car didn't pay, so another car joined, push to back and output to console
            tempCar = Car();
            tollBooth.push_back(tempCar);
            cout << "Car joined: ";
        }
        tempCar.print(); // output car popped or pushed
        // output list at end of period
        CurrentQueueToConsole(tollBooth);
        cout << endl;
    }

    return 0;
}

// returns whether front car pays and leaves
bool FrontCarPaid()
{
    return ((rand() % 100) + 1) <= CHANCE_CAR_PAYS;
}

// returns whether a new car will join line
bool NewCarJoinsQueue()
{
    return ((rand() % 100) + 1) <= CHANCE_NEW_CAR_JOINS;
}

// outputs each element in toll booth
void CurrentQueueToConsole(deque<Car> &q)
{
    // guard statement
    if (q.empty())
    {
        cout << "\tEmpty\n";
        return;
    }

    int count = 0;
    for (auto it = q.begin(); it != q.end(); it++)
    {
        cout << "\t";
        it->print();
        count++;
    }
}