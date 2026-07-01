/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

class SupportHandler {
public:
    virtual ~SupportHandler() = default;
    void set_next(std::shared_ptr<SupportHandler> next_handler)
    {
        next = next_handler;
    }

    virtual void handle_request(const std::string &request) const
    {
        if (next) {
            next->handle_request(request);
        } else {
            std::cout << "No handler available for request: " << request << std::endl;
        }
    }

private:
    std::shared_ptr<SupportHandler> next;
};

class LevelOneSupport : public SupportHandler {
public:
    void handle_request(const std::string &request) const override
    {
        if (request == "Level 1") {
            std::cout << "Handled by Level One Support" << std::endl;
        } else {
            SupportHandler::handle_request(request);
        }
    }
};

class LevelTwoSupport : public SupportHandler {
public:
    void handle_request(const std::string &request) const override
    {
        if (request == "Level 2") {
            std::cout << "Handled by Level Two Support" << std::endl;
        } else {
            SupportHandler::handle_request(request);
        }
    }
};

class LevelThreeSupport : public SupportHandler {
public:
    void handle_request(const std::string &request) const override
    {
        if (request == "Level 3") {
            std::cout << "Handled by Level Three Support" << std::endl;
        } else {
            SupportHandler::handle_request(request);
        }
    }
};

int main()
{
    auto level_one = std::make_shared<LevelOneSupport>();
    auto level_two = std::make_shared<LevelTwoSupport>();
    auto level_three = std::make_shared<LevelThreeSupport>();

    level_one->set_next(level_two);
    level_two->set_next(level_three);

    level_one->handle_request("Level 1");
    level_one->handle_request("Level 2");
    level_one->handle_request("Level 3");

    return 0;
}
