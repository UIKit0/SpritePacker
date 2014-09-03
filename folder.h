#ifndef FOLDER_H
#define FOLDER_H

#include "item.h"

class Folder : public Item
{
public:
    typedef QList<Item *> Items;

public:
    Folder(QString name);
    ~Folder();

    void add(Item *item);

    Items items() {
        return m_items;
    }

    void process(QString path);
    void process(QString path, bool as_root);

private:
    Items m_items;

};

#endif // FOLDER_H
