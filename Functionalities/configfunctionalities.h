#ifndef CONFIGFUNCTIONALITIES_H
#define CONFIGFUNCTIONALITIES_H

#include <QObject>
#include "functionalities/functionalities.h"
#include "fakethermostat.h"



class Configfunctionalities:public StateLiteral
{
    Q_OBJECT
public:
    static const QString functionalityType;
    Configfunctionalities(const QString& name);
    Configfunctionalities();

    REGISTER_SPECIALIZED_FUNCTIONALITY_CLASS("Config",Configfunctionalities,StateLiteral)

    Fakethermostat*  fakeThermostat() const;

virtual   QJsonObject writeToDevice(const HandlerStateLiteral& datahandler) noexcept override;

virtual   QJsonObject requestDataUpdate() noexcept override;


    void setThermostatFake(Fakethermostat* fakethermostat);

    Fakethermostat* fakethermostat() const;

private:

    Fakethermostat* m_fakethermostat=nullptr;


};

#endif // CONFIGFUNCTIONALITIES_H
