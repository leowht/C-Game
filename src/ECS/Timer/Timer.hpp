/*
** EPITECH PROJECT, 2024
** Timer
** File description:
** Timer
*/

#ifndef TIMER
#define TIMER

#include <iostream>
#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    bool running = false;

public:
    // Start the timer
    void start() {
        startTime = std::chrono::steady_clock::now();
        running = true;
    }

    // Stop the timer
    void stop() {
        if (running) {
            endTime = std::chrono::steady_clock::now();
            running = false;
        }
    }

    // Reset the timer (set time to 0 and stop the timer)
    void reset() {
        running = false;
        startTime = std::chrono::steady_clock::now();
        endTime = startTime;
    }

    // Get the time elapsed in milliseconds
    double getTimeElapsed() {
        std::chrono::time_point<std::chrono::steady_clock> end;
        if (running) {
            end = std::chrono::steady_clock::now();
        } else {
            end = endTime;
        }
        return std::chrono::duration<double, std::milli>(end - startTime).count();
    }

    double getSecondsElapsed() {
        std::chrono::time_point<std::chrono::steady_clock> end;
        if (running) {
            end = std::chrono::steady_clock::now();
        } else {
            end = endTime;
        }
        return std::chrono::duration<double>(end - startTime).count();
    }
};

#endif /* !TIMER */
