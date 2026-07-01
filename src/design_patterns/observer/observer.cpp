/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <algorithm>
#include <iostream>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Publisher {
public:
    void subscribe(Observer *observer)
    {
        observers.push_back(observer);
    }
    void unsubscribe(Observer *observer)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void publish()
    {
        std::cout << "Publishing an event\n";
        notify();
    }

private:
    void notify()
    {
        for (Observer *observer : observers) {
            observer->update();
        }
    }

    std::vector<Observer *> observers;
};

class ConcreteObserver : public Observer {
public:
    void update() override
    {
        std::cout << "Observer received an update\n";
    }
};

int main()
{
    Publisher publisher;
    ConcreteObserver observer1;
    ConcreteObserver observer2;
    publisher.subscribe(&observer1);
    publisher.subscribe(&observer2);
    publisher.publish();

    return 0;
}
