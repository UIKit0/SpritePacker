#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
    Item(QString name);

    QString name() const
    { return m_name; }

    virtual void process(QString path) = 0;

private:
    QString m_name;
};

#endif // ITEM_H
