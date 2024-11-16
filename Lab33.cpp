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
const int NUM_INITIAL_CARS = 2, NUM_PLAZA_LANES = 4, CHANCE_CAR_PAYS = 46, CHANCE_NEW_CAR_JOINS = 39, CHANCE_REAR_CHANGES_LANE = 15, CHANCE_JOIN_IF_EMPTY = 50;

// for simulation where car pays and joins queue are separate events
bool FrontCarPaid();
bool NewCarJoinsQueue();
// prints current queue
void CurrentQueueToConsole(deque<Car> &);

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // seed current time to rand()
    deque<Car> tollBooth = {};                       // empty toll booth line
    array<deque<Car>, NUM_PLAZA_LANES> tollPlaza = {};
    int randNumber = 0;
    int count = 0;
    Car tempCar;
    string output = "";
    // deque<Car> tollPlaza[4] = {}; // alternative option

    // initialize toll plaza
    cout << "Initial queue:\n";
    for (int i = 0; i < tollPlaza.size(); i++)
    {
        // for each toll booth, initialize toll booth with 2 vehicles and output to console
        for (int j = 0; j < NUM_INITIAL_CARS; j++)
        {
            tollPlaza.at(i).push_back(Car());
        }
        cout << "Lane " << ++count << ":\n";
        CurrentQueueToConsole(tollPlaza.at(i));
    }

    // run simulation for 20 iterations
    for (int i = 0; i < 3; i++)
    {
        // timeperiod
        cout << "\nTime: " << i + 1 << endl;

        // for each lane in the toll plaza
        for (int j = 0; j < tollPlaza.size(); j++)
        {
            // output lane to console
            cout << "Lane " << j << ": ";

            // get random number to check toll booth events
            randNumber = (rand() % 100) + 1;

            // check if toll booth lane is empty
            if (tollPlaza.at(j).empty())
            {
                // lane empty: check if car joins empty lane
                if (randNumber <= CHANCE_JOIN_IF_EMPTY)
                {
                    tempCar = Car();
                    tollPlaza.at(j).push_back(tempCar);
                    cout << "Car joined: ";
                }
            }
            else
            {
                // if toll booth lane not empty
                if (randNumber <= CHANCE_CAR_PAYS) // car pays
                {
                    tempCar = tollPlaza.at(j).front();
                    tollPlaza.at(j).pop_front();
                    cout << "Car paid: ";
                }
                else if (randNumber <= CHANCE_CAR_PAYS + CHANCE_NEW_CAR_JOINS) // car joins
                {
                    tempCar = Car();
                    tollPlaza.at(j).push_back(tempCar);
                    cout << "Car joined: ";
                }
                else
                { // car switches
                    // get new lane to switch to
                    int newLane = (j + (rand() % (NUM_PLAZA_LANES - 1)) + 1) % NUM_PLAZA_LANES;
                    // get car, remove from current lane, switch to new lane
                    tempCar = tollPlaza.at(j).back();
                    tollPlaza.at(j).pop_back();
                    tollPlaza.at(newLane).push_back(tempCar);
                }
            }
            // output car to console
            tempCar.print();
        }
        // output each queue to console
        for (int j = 0; j < tollPlaza.size(); j++)
        {
            cout << "Queue:\n";
            CurrentQueueToConsole(tollPlaza.at(j));
        }
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