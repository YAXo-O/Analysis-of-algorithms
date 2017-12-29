#include <QVector>
#include "simulation.h"

#include "worldinfo.h"
#include "ant.h"

#include <QDebug>

path Simulation::start()
{
    WorldInfo &instance = WorldInfo::getInstance();
    QVector<Ant *> ants;

    const unsigned int citiesCount = instance.getCitiesCount();
    const float Q = instance.getQ();
    const float e = instance.getElightFactor();

    for(unsigned int i = 0; i < instance.getCount(); i++)
    {
        Ant *ant = new Ant(i%citiesCount);
        ants.append(ant);
    }

    path shortest;
    shortest.length = 0;
    for(unsigned int i = 0; i < citiesCount; i++)
        for(unsigned int j = 0; j < citiesCount; j++)
        shortest.length += instance.getDistance(i, j);

    for(unsigned int lifetime = instance.getLifetime(); lifetime > 0; lifetime--)
    {
        QVector<path> paths;
        for(auto i : ants)
        {
            path res = i->iteration();
            if(res.length < shortest.length)
                shortest = res;
            paths.append(res);
        }

        // Обновить феромон
        instance.evaporate();

        for(auto path : paths)
        {
            cityId prev = path.route.first();
            path.route.pop_front();
            const float pher = Q/path.length;

            for(auto to : path.route)
            {
                instance.setPheromones(prev, to, pher);
                prev = to;
            }
        }

        // Запустить элитного муравья
        path L = shortest;
        cityId prev = L.route.first();
        L.route.pop_front();
        const float pherElite = e*Q/L.length;

        for(auto to : L.route)
        {
            instance.setPheromones(prev, to, pherElite);
            prev = to;
        }

    }

    return shortest;
}
