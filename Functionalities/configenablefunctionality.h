#ifndef CONFIGENABLEFUNCTIONALITY_H
#define CONFIGENABLEFUNCTIONALITY_H

#include<moduleapi/functionalities/functionality.h>
#include "handlerConfigEnable.h"
#include "datahandlers/datahandlerfield.h"
#include <moduleapi/module/device.h>
#include <moduleapi/common/option.h>
#include <moduleapi/functionalities/field/field.h>
#include<functionalities/functionality.h>
#include<fakethermostat.h>
class ConfigEnablefunctionality: public Functionality
{
 Q_OBJECT

public:

    ConfigEnablefunctionality();


    ConfigEnablefunctionality(const QString& id, const QString& name);

     REGISTER_FUNCTIONALITY_CLASS("configEnable_Functionality",ConfigEnablefunctionality)
     SET_HANDLER_TYPE_NO_OVERLOAD(HandlerConfigEnable)

    FieldsList defaultFields() override final;

    static FunctionalityPtr make(const QString& id                  = QString(),
                                 const QString& name                = QString(),
                                 const QString& description         = QString(),
                                 Functionality::Role role           = Functionality::Role::Configuration,
                                 FunctionalitiesOptionList options  = FunctionalitiesOptionList()) noexcept;

    QJsonObject writeToDevice(const HandlerConfigEnable& dataHandler) noexcept;

     static const QString functionalityType;

     void setThermostatFake(Fakethermostat* fakethermostat);

     Fakethermostat* thermostatFake() const;



    private:
      Fakethermostat* m_fakethermostat=nullptr;
};

#endif // CONFIGENABLEFUNCTIONALITY_H
