/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

class Transport {
public:
    virtual ~Transport() = default;
    virtual void deliver() const = 0;
};

class Truck : public Transport {
public:
    void deliver() const override
    {
        std::cout << "Delivering by truck\n";
    }
};

class Ship : public Transport {
public:
    void deliver() const override
    {
        std::cout << "Delivering by ship\n";
    }
};

class Logistics {
public:
    virtual ~Logistics() = default;

    // Factory Method
    virtual std::unique_ptr<Transport> create_transport() const = 0;

    void plan_delivery() const
    {
        auto transport = create_transport();
        transport->deliver();
    }
};

class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> create_transport() const override
    {
        return std::make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics {
public:
    std::unique_ptr<Transport> create_transport() const override
    {
        return std::make_unique<Ship>();
    }
};

int main()
{
    std::unique_ptr<Logistics> logistics;

    logistics = std::make_unique<RoadLogistics>();
    logistics->plan_delivery();

    logistics = std::make_unique<SeaLogistics>();
    logistics->plan_delivery();

    return 0;
}
