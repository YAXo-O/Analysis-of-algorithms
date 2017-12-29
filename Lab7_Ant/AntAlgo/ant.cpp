#include <random>

#include "ant.h"

#include "worldinfo.h"

struct possibilityStripe
{
    double start;
    double end;
    cityId city;
};

Ant::Ant(cityId _position): position(_position)
{
}

path Ant::iteration()
{
    visited.clear();

    WorldInfo &info = WorldInfo::getInstance();
    cityId curPosition = position;
    const unsigned int citiesCount = info.getCitiesCount();

    path antPath;

    for(int i = citiesCount; i > 0; i--)
    {
        visited.append(curPosition);
        QList<cityId> toVisit;
        for(unsigned int j = 0; j < citiesCount; j++)
            if(info.getDistance(curPosition, j) > 0 && !visited.contains(j))
                toVisit.append(j);

        /* Определить следующий город и перейти в него */

        // Задать полосы
        QList<possibilityStripe> stripes;
        double currentStart = 0;
        for(auto to : toVisit)
        {
            possibilityStripe currentStripe;
            currentStripe.start = currentStart;

            currentStart += pow(info.getPheromones(curPosition, to),
                                info.getAlpha())*pow(info.getVisibility(curPosition, to), info.getBetta());
            currentStripe.end = currentStart;
            currentStripe.city = to;
            stripes.append(currentStripe);
        }

        // Задать случайное число [0;currentStart]
        static std::mt19937_64 generator;
        std::uniform_real_distribution<double> distributor(0, currentStart);

        double randValue = distributor(generator);

        // Определить выпавший город
        for(auto stripe : stripes)
        {
            if(randValue >= stripe.start && randValue < stripe.end)
            {
                // Переход в новый город
                curPosition = stripe.city;
                break;
            }
        }
    }

    /* Посчитать результирующий путь */
    cityId prev = position;
    antPath.length = 0;
    for(auto city: visited)
    {
        antPath.route.append(city);
        antPath.length += info.getDistance(prev, city);
        prev = city;
    }

    return antPath;
}
