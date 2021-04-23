#ifndef TARGETFUNCTIONALITIES_H
#define TARGETFUNCTIONALITIES_H

#include <QObject>
#include "moduleapi/functionalities/functionalities.h"
#include "fakethermostat.h"


class Targetfunctionalities:public Thermostat
{
    Q_OBJECT
public:
    static const QString functionalityType;
    Targetfunctionalities();
    Targetfunctionalities(const QString& nom);

    REGISTER_SPECIALIZED_FUNCTIONALITY_CLASS("Target",Targetfunctionalities,Thermostat)

    Fakethermostat*  fakeThermostat() const;

     virtual QJsonObject writeToDevice(const HandlerThermostat& datahandeler)  noexcept override;
     virtual QJsonObject requestDataUpdate() noexcept override ;
     void setThermostatFake(Fakethermostat* fakethermostat);



private:

    Fakethermostat* m_fakethermostat=nullptr
            ;


};

#endif // TARGETFUNCTIONALITIES_H
