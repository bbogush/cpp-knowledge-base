/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class User;

class ChatMediator {
public:
    virtual ~ChatMediator() = default;
    virtual void send_message(const std::string &message, User *user) = 0;
    virtual void add_user(const std::shared_ptr<User> &user) = 0;
};

class User {
public:
    User(std::string name, std::shared_ptr<ChatMediator> chat_mediator) :
        name(std::move(name)), mediator(chat_mediator)
    {
    }
    virtual ~User() = default;

    virtual void send(const std::string &msg)
    {
        if (auto locked_mediator = mediator.lock()) {
            locked_mediator->send_message(msg, this);
        } else {
            std::cerr << "Mediator is no longer available." << std::endl;
        }
    }

    virtual void receive(const std::string &msg)
    {
        std::cout << name << " received: " << msg << std::endl;
    }

protected:
    std::string name;
    std::weak_ptr<ChatMediator> mediator;
};

class ChatRoom : public ChatMediator {
public:
    void send_message(const std::string &message, User *user) override
    {
        for (const auto &u : users) {
            if (u.get() != user) {
                u->receive(message);
            }
        }
    }
    void add_user(const std::shared_ptr<User> &user) override
    {
        users.push_back(user);
    }

private:
    std::vector<std::shared_ptr<User>> users;
};

int main()
{
    auto mediator = std::make_shared<ChatRoom>();
    auto user1 = std::make_shared<User>("Alice", mediator);
    auto user2 = std::make_shared<User>("Bob", mediator);
    auto user3 = std::make_shared<User>("Charlie", mediator);

    mediator->add_user(user1);
    mediator->add_user(user2);
    mediator->add_user(user3);

    user1->send("Hello, everyone!");

    return 0;
}
