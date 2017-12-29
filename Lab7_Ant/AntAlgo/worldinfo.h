#ifndef WORLDINFO_H
#define WORLDINFO_H

#include "matrix.h"
#include "datatypes.h"

class WorldInfo
{
public:
    ~WorldInfo();

    void setAlpha(float value);
    void setBetta(float value);
    void setElightFactor(float value);
    void setQ(float value);
    void setLifetime(unsigned int value);
    void setCount(unsigned int value);
    void setCitiesCount(unsigned int value);
    void setEvaporateFactor(float factor);
    float getAlpha() const;
    float getBetta() const;
    float getElightFactor() const;
    float getQ() const;
    float getEvaporateFactor() const;
    unsigned int getLifetime() const;
    unsigned int getCount() const;
    unsigned int getCitiesCount() const;
    void evaporate();

    void createMatrix(size_t rows, size_t cols);
    void setDistance(cityId from, cityId to, float distance);
    void setPheromones(cityId from, cityId to, float value);
    float getVisibility(cityId from, cityId to) const;
    float getDistance(cityId from, cityId to) const;
    float getPheromones(cityId from, cityId to) const;

    static WorldInfo &getInstance();

protected:
    WorldInfo();

private:
    float alpha;
    float betta;
    float elightFactor;
    float Q;
    float evapFactor;
    unsigned int lifetime;
    unsigned int count;
    unsigned int citiesCount;
    Matrix *visibility;
    Matrix *distance;
    Matrix *pheromones;

};

#endif // WORLDINFO_H
