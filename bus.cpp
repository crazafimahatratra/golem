#include "bus.h"
Bus* Bus::_instance = nullptr;

Bus::Bus(QObject *parent) : QObject(parent)
{

}

Bus *Bus::instance()
{
    if(_instance)
        return _instance;
    _instance = new Bus();
    return _instance;
}
