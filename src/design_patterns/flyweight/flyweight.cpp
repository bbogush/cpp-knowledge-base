/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Character {
public:
    virtual ~Character() = default;
    virtual void draw(int x, int y) const = 0;
};

// Flyweight class representing a character with intrinsic state (symbol and font)
class ConcreteCharacter : public Character {
public:
    ConcreteCharacter(char symbol, const std::string &font, int size) :
        symbol(symbol), font(font), size(size)
    {
    }
    void draw(int x, int y) const override
    {
        std::cout << "Character: " << symbol << ", Font: " << font << ", Size: " << size
                  << ", Position: (" << x << ", " << y << ")" << std::endl;
    }

private:
    // Intrinsic state shared among characters
    char symbol;
    std::string font;
    int size;
};

class CharacterFactory {
public:
    std::shared_ptr<Character> get_character(char symbol, const std::string &font, int size)
    {
        std::string key = std::string(1, symbol) + font + std::to_string(size);

        if (pool.find(key) == pool.end()) {
            pool[key] = std::make_shared<ConcreteCharacter>(symbol, font, size);
            std::cout << "Creating new character: " << symbol << ", Font: " << font
                      << ", Size: " << size << std::endl;
        } else {
            std::cout << "Reusing existing character: " << symbol << ", Font: " << font
                      << ", Size: " << size << std::endl;
        }

        return pool[key];
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Character>> pool;
};

int main()
{
    CharacterFactory factory;

    auto char1 = factory.get_character('A', "Arial", 12);
    auto char2 = factory.get_character('B', "Times New Roman", 14);
    auto char3 = factory.get_character('A', "Arial", 12); // This will reuse the existing character

    char1->draw(10, 20);
    char2->draw(30, 40);
    char3->draw(50, 60);

    return 0;
}
