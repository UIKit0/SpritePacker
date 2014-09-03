#ifndef RESOURCE_H
#define RESOURCE_H

#include "item.h"

class Resource : public Item
{
public:
    Resource(QString name);

    virtual int frameCount() const = 0;
    virtual QRect frameRect() const = 0;
    virtual QImage frameImage(int frame) const = 0;
    virtual bool isValid() const = 0;
};

#endif // RESOURCE_H
