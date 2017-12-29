#ifndef DATATYPES_H
#define DATATYPES_H

#include <QList>

typedef unsigned int cityId;

struct path
{
    QList<cityId> route;
    float length;
};

#endif // DATATYPES_H
