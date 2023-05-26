#pragma once
#include <vector>
using std::vector;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void notify() {
        for (auto observer: observers) {
            observer->update();
        }
    }
    virtual ~Observable() = default;
};
