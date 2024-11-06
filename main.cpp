#include <iostream>
#include <queue>
#include <random>
#include <ctime>

struct Passenger {
    double arrivalTime;
};

struct Bus {
    double arrivalTime;
    int freeSeats;
};

double generateRandomTime(double mean) {
    std::default_random_engine generator(time(0));
    std::exponential_distribution<double> distribution(1.0 / mean);
    return distribution(generator);
}

int main() {
    double passengerArrivalMean, busArrivalMean;
    int maxPassengers;
    bool isTerminal;

    std::cout << "Enter average time between passenger arrivals: ";
    std::cin >> passengerArrivalMean;
    std::cout << "Enter average time between bus arrivals: ";
    std::cin >> busArrivalMean;
    std::cout << "Enter maximum number of passengers at the stop: ";
    std::cin >> maxPassengers;
    std::cout << "Is this a terminal stop? (1 for yes, 0 for no): ";
    std::cin >> isTerminal;

    std::queue<Passenger> passengerQueue;
    std::queue<Bus> busQueue;

    double currentTime = 0.0;
    double totalWaitTime = 0.0;
    int totalPassengers = 0;

    while (true) {
        double nextPassengerTime = generateRandomTime(passengerArrivalMean);
        double nextBusTime = generateRandomTime(busArrivalMean);

        currentTime += std::min(nextPassengerTime, nextBusTime);

        if (nextPassengerTime < nextBusTime) {
            Passenger newPassenger = {currentTime};
            passengerQueue.push(newPassenger);
            totalPassengers++;
        } else {
            Bus newBus = {currentTime, rand() % 20 + 1}; // Random free seats between 1 and 20
            busQueue.push(newBus);

            while (!passengerQueue.empty() && newBus.freeSeats > 0) {
                Passenger passenger = passengerQueue.front();
                passengerQueue.pop();
                totalWaitTime += currentTime - passenger.arrivalTime;
                newBus.freeSeats--;
            }
        }

        if (passengerQueue.size() > maxPassengers) {
            std::cout << "Too many passengers at the stop. Simulation ends." << std::endl;
            break;
        }
    }

    std::cout << "Average wait time: " << totalWaitTime / totalPassengers << " minutes" << std::endl;

    return 0;
}
