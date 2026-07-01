/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

class TcpConnection;

class TcpState {
public:
    virtual ~TcpState() = default;
    virtual void open(TcpConnection &connection)
    {
        (void)connection;
        std::cout << "Invalid operation" << std::endl;
    }
    virtual void close(TcpConnection &connection)
    {
        (void)connection;
        std::cout << "Invalid operation" << std::endl;
    }
    virtual void send(TcpConnection &connection, const std::string &data)
    {
        (void)connection;
        (void)data;
        std::cout << "Invalid operation" << std::endl;
    }
    virtual const char *name() const = 0;
};

class TcpConnection {
public:
    explicit TcpConnection(std::unique_ptr<TcpState> state) : state(std::move(state))
    {
    }

    void set_state(std::unique_ptr<TcpState> new_state)
    {
        state = std::move(new_state);
    }

    void open()
    {
        state->open(*this);
    }
    void close()
    {
        state->close(*this);
    }
    void send(const std::string &data)
    {
        state->send(*this, data);
    }

    void print_state() const
    {
        std::cout << "Current state: " << state->name() << std::endl;
    }

private:
    std::unique_ptr<TcpState> state;
};

class ClosedState : public TcpState {
public:
    void open(TcpConnection &connection) override;
    const char *name() const override
    {
        return "Closed";
    }
};

class OpenState : public TcpState {
public:
    void close(TcpConnection &connection) override;
    void send(TcpConnection &connection, const std::string &data) override;
    const char *name() const override
    {
        return "Open";
    }
};

void ClosedState::open(TcpConnection &connection)
{
    std::cout << "Opening connection..." << std::endl;
    connection.set_state(std::make_unique<OpenState>());
}

void OpenState::close(TcpConnection &connection)
{
    std::cout << "Closing connection..." << std::endl;
    connection.set_state(std::make_unique<ClosedState>());
}

void OpenState::send(TcpConnection &connection, const std::string &data)
{
    (void)connection;
    std::cout << "Sending data: " << data << std::endl;
}

int main()
{
    TcpConnection connection(std::make_unique<ClosedState>());
    connection.print_state();
    connection.open();
    connection.print_state();
    connection.send("Hello, World!");
    connection.close();
    connection.print_state();

    return 0;
}
