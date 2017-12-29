#ifndef ANT_H
#define ANT_H

#include <QList>

#include "./datatypes.h"

class Ant
{
public:
    Ant(cityId position);

    path iteration();

private:
    cityId position;
    QList<cityId> visited;
};

#endif // ANT_H
