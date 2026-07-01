/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <string>

// Subsystem 1
class Player {
public:
    void on() const
    {
        std::cout << "Player ON\n";
    }
    void play(const std::string &movie) const
    {
        std::cout << "Playing movie: " << movie << "\n";
    }
    void off() const
    {
        std::cout << "Player OFF\n";
    }
};

// Subsystem 2
class SoundSystem {
public:
    void on() const
    {
        std::cout << "Sound System ON\n";
    }
    void set_volume(int level) const
    {
        std::cout << "Setting volume to: " << level << "\n";
    }
    void off() const
    {
        std::cout << "Sound System OFF\n";
    }
};

// Facade
class HomeTheaterFacade {
public:
    HomeTheaterFacade(Player &player, SoundSystem &sound_system) :
        player(player), sound_system(sound_system)
    {
    }

    void watch_movie(const std::string &movie)
    {
        std::cout << "Get ready to watch a movie...\n";
        player.on();
        sound_system.on();
        sound_system.set_volume(5);
        player.play(movie);
    }

    void end_movie()
    {
        std::cout << "Shutting down the home theater...\n";
        player.off();
        sound_system.off();
    }

private:
    Player &player;
    SoundSystem &sound_system;
};

int main()
{
    Player player;
    SoundSystem sound_system;
    HomeTheaterFacade home_theater(player, sound_system);

    home_theater.watch_movie("Inception");
    home_theater.end_movie();

    return 0;
}
