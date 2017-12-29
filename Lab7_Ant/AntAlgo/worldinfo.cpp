#include "worldinfo.h"

WorldInfo::WorldInfo():alpha(1), betta(1), elightFactor(0), Q(0), evapFactor(.5), visibility(nullptr),
    distance(nullptr), pheromones(nullptr)
{
}

unsigned int WorldInfo::getCitiesCount() const
{
    return citiesCount;
}

void WorldInfo::evaporate()
{
    pheromones->operator*=(1 - evapFactor);
}

float WorldInfo::getEvaporateFactor() const
{
    return evapFactor;
}

void WorldInfo::setCitiesCount(unsigned int value)
{
    citiesCount = value;
}

void WorldInfo::setEvaporateFactor(float factor)
{
    evapFactor = factor > 0 ? (factor < 1 ? factor : 1) : 0;
}

unsigned int WorldInfo::getCount() const
{
    return count;
}

void WorldInfo::setCount(unsigned int value)
{
    count = value;
}

unsigned int WorldInfo::getLifetime() const
{
    return lifetime;
}

void WorldInfo::setLifetime(unsigned int value)
{
    lifetime = value;
}

WorldInfo::~WorldInfo()
{
    if(visibility)
        delete visibility;
    if(distance)
        delete distance;
    if(pheromones)
        delete pheromones;
}

float WorldInfo::getAlpha() const
{
    return alpha;
}

void WorldInfo::setAlpha(float value)
{
    alpha = value;
}

float WorldInfo::getBetta() const
{
    return betta;
}

void WorldInfo::setBetta(float value)
{
    betta = value;
}

float WorldInfo::getElightFactor() const
{
    return elightFactor;
}

void WorldInfo::setElightFactor(float value)
{
    elightFactor = value;
}

float WorldInfo::getQ() const
{
    return Q;
}

void WorldInfo::setQ(float value)
{
    Q = value;
}

void WorldInfo::createMatrix(size_t rows, size_t cols)
{
    visibility = new Matrix(cols, rows);
    distance = new Matrix(cols, rows);
    pheromones = new Matrix(cols, rows);
}

void WorldInfo::setDistance(cityId from, cityId to, float _distance)
{
    visibility->at(to, from) = 1.f/_distance;
    distance->at(to, from) = _distance;
}

void WorldInfo::setPheromones(cityId from, cityId to, float value)
{
    pheromones->at(to, from) = value;
}

float WorldInfo::getDistance(cityId from, cityId to) const
{
    return distance->at(to, from);
}

float WorldInfo::getPheromones(cityId from, cityId to) const
{
    return pheromones->at(to, from);
}

float WorldInfo::getVisibility(cityId from, cityId to) const
{
    return visibility->at(to, from);
}

WorldInfo &WorldInfo::getInstance()
{
    static WorldInfo instance;

    return instance;
}
