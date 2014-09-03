#ifndef COMPOUNDRESOURCE_H
#define COMPOUNDRESOURCE_H

#include "item.h"

class Resource;

class CompoundResource : public Item
{
public:
    CompoundResource(QString name);
    ~CompoundResource();

    virtual void add(Resource *resource);

    void process(QString path);

private:
    typedef QList<Resource *> Resources;
    Resources m_resources;

    bool m_new_line_per_resource;
    int m_frame_count;
    int m_per_row;

    void generateInfo(QString path);
};

#endif // COMPOUNDRESOURCE_H
