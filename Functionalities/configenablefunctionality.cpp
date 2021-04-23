#include "configenablefunctionality.h"

const QString ConfigEnablefunctionality::functionalityType("configEnable_Functionality");







ConfigEnablefunctionality::ConfigEnablefunctionality():
    Functionality(Fakethermostat::enableConfigID, QString(),QString(), ConfigEnablefunctionality::functionalityType,Functionality::Usage,
                  DataHandler::make(ConfigEnablefunctionality::functionalityType), defaultFields(), FunctionalitiesOptionList())
{
setOption("enable","bool");
setOption("Config","QString");

}

ConfigEnablefunctionality::ConfigEnablefunctionality(const QString& id, const QString& name) :
    Functionality(Fakethermostat::enableConfigID, name,QString(), ConfigEnablefunctionality::functionalityType,Functionality::Usage,
                  DataHandler::make(ConfigEnablefunctionality::functionalityType), defaultFields(), FunctionalitiesOptionList())

{

    setID(id);

}

FieldsList ConfigEnablefunctionality::defaultFields()
{
    FieldPtr enable   (new Field(HandlerConfigEnable::enable_name_field, Field::Type::Binary, true, false));
    FieldPtr config      (new Field(HandlerConfigEnable::config_name_field, Field::Type::StateLitteral, true, false));

    return FieldsList () << enable << config;
}

FunctionalityPtr ConfigEnablefunctionality::make(const QString& id, const QString& name,const QString& description, Functionality::Role role,FunctionalitiesOptionList options) noexcept

{
    return Functionality::make(Fakethermostat::enableConfigID, name, description, ConfigEnablefunctionality::functionalityType,
                               role, DataHandler::make(ConfigEnablefunctionality::functionalityType,
                                                       HandlerConfigEnable::defaultFields()),FieldsList(), options);
}


QJsonObject ConfigEnablefunctionality::writeToDevice(const HandlerConfigEnable &dataHandlerce) noexcept

{
     m_fakethermostat->setConfig(dataHandlerce.config());
     m_fakethermostat->setEnable(dataHandlerce.enable());

    return QJsonObject
                    {
                     {"Config_Enable"," updated"}
                    };
}

void ConfigEnablefunctionality::setThermostatFake(Fakethermostat* fakethermostat)
{
    m_fakethermostat=fakethermostat;
}



Fakethermostat* ConfigEnablefunctionality:: thermostatFake() const
{
    return m_fakethermostat;
}


