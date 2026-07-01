/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

class RealImage : public Image {
public:
    explicit RealImage(const std::string &filename) : filename(filename)
    {
    }

    void display() override
    {
        if (!loaded) {
            load_from_disk();
            loaded = true;
        }
        std::cout << "Displaying " << filename << std::endl;
    }

private:
    void load_from_disk()
    {
        std::cout << "Loading " << filename << " from disk" << std::endl;
    }

    std::string filename;
    bool loaded = false;
};

class ProxyImage : public Image {
public:
    explicit ProxyImage(const std::string &file) : filename(file)
    {
    }

    void display() override
    {
        if (!real_image) {
            real_image = std::make_unique<RealImage>(filename);
        }
        real_image->display();
    }

private:
    std::string filename;
    std::unique_ptr<RealImage> real_image; // Lazy-loaded
};

int main()
{
    std::unique_ptr<Image> image = std::make_unique<ProxyImage>("test.jpg");
    image->display();

    return 0;
}
