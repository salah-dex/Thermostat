#include "targetfunctionalities.h"

const QString Targetfunctionalities::functionalityType{"Target"};


Targetfunctionalities::Targetfunctionalities()
{
 setType(Targetfunctionalities::functionalityType);
}

Targetfunctionalities::Targetfunctionalities(const QString& name):
 Thermostat(name)

{
    setType(Targetfunctionalities::functionalityType);

}

QJsonObject Targetfunctionalities::writeToDevice(const HandlerThermostat &handler) noexcept
{
  m_fakethermostat->setTargetTemperature(handler.heatingSetPoint());

  return QJsonObject
  {
      {"resultat","bon"}
  };
}

QJsonObject Targetfunctionalities::requestDataUpdate() noexcept
{
    m_fakethermostat->RefreshTargetData();

    return QJsonObject
    {
      {"refreshed","targed"}
    };
}




void Targetfunctionalities::setThermostatFake(Fakethermostat* fakethermostat)
{
    m_fakethermostat= fakethermostat;
}

Fakethermostat* Targetfunctionalities::fakeThermostat() const
{
    return m_fakethermostat;
}


