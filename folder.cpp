#include "precompiled.h"

#include "folder.h"

Folder::Folder(QString name) :
    Item(name)
{
}

Folder::~Folder()
{
    foreach (Item *item, m_items) {
        delete item;
    }
    m_items.clear();
}

void Folder::add(Item *item)
{
    m_items.append(item);
}

void Folder::process(QString path)
{
    process(path, false);
}

void Folder::process(QString path, bool as_root)
{
    QDir dir(path);
    if (!as_root) {
        dir.mkdir(name());
        dir.cd(name());
    }

    foreach (Item *item, m_items) {
        item->process(dir.absolutePath());
    }
}
