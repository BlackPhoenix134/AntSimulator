#pragma once

#include<random>

int randomInt(int range_from, int range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution    distr(range_from, range_to);
    return distr(generator);
}

float randomFloat(float range_from, float range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_real_distribution    distr(range_from, range_to);
    return distr(generator);
}