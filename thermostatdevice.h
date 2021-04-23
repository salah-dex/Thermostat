#ifndef THERMOSTATDEVICE_H
#define THERMOSTATDEVICE_H

#include <QObject>
#include <QSharedDataPointer>
#include "module/device.h"
#include "coreapi/core/core.h"


class ThermostatDevice:public Device
{
    Q_OBJECT
public:
    ThermostatDevice();
    ThermostatDevice(const ThermostatDevice &);
    ThermostatDevice &operator=(const ThermostatDevice &);
    ~ThermostatDevice();

private:


};



 REGISTER_DEVICE_CLASS(ThemostatDevice)


#endif // THERMOSTATDEVICE_H
