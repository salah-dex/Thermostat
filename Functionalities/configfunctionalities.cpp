#include "configfunctionalities.h"

const QString Configfunctionalities::functionalityType{"Config"};


Configfunctionalities::Configfunctionalities()
{
  setType(Configfunctionalities::functionalityType);
}




Configfunctionalities::Configfunctionalities(const QString& name)
    :StateLiteral(name)
{
  setType(Configfunctionalities::functionalityType);
}



QJsonObject Configfunctionalities::writeToDevice(const HandlerStateLiteral& handler) noexcept
{
     m_fakethermostat->setConfig(handler.state());

     return QJsonObject
     {
       {"resultat","bon"}
     };
}


QJsonObject Configfunctionalities::requestDataUpdate() noexcept
{
   m_fakethermostat->RefreshConfigData();

    return QJsonObject
    {
      {"resultat","bon"}
    };
}


void Configfunctionalities::setThermostatFake(Fakethermostat* fakethermostat)
{
    m_fakethermostat=fakethermostat;
}



Fakethermostat* Configfunctionalities:: fakeThermostat() const
{
    return m_fakethermostat;
}
