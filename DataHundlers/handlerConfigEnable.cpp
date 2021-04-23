#include "handlerConfigEnable.h"
#include "configenablefunctionality.h"

const QString HandlerConfigEnable::enable_name_field ("Enable_Option");
const QString HandlerConfigEnable::config_name_field ("Config_Option");


HandlerConfigEnable::HandlerConfigEnable(const QString& id,const DataHandlersFieldList&  fields) :

    DataHandler(id,ConfigEnablefunctionality::functionalityType, fields)
{


}

HandlerConfigEnable::HandlerConfigEnable(const DataHandler& copie) :
    DataHandler(copie.id(),ConfigEnablefunctionality::functionalityType,copie.cloneData())
{


}

DataHandlersFieldList HandlerConfigEnable::defaultFields()
{
    DataHandlerFieldPtr Enable = DataHandlerField::make(enable_name_field,QVariant(Fakethermostat::enable_mode));
    DataHandlerFieldPtr Config = DataHandlerField::make(config_name_field,QVariant(Fakethermostat::config_automatic));

    return DataHandlersFieldList () <<Enable << Config;
}

bool HandlerConfigEnable::enable() const noexcept
{
    return value(enable_name_field).toBool();
}

QString HandlerConfigEnable::config() const noexcept
{
    return value(config_name_field).toString();
}


void HandlerConfigEnable::setEnable(const bool &newEnable)
{
    setField(enable_name_field,QVariant::fromValue(newEnable));
}


void HandlerConfigEnable::setConfig(const QString &newconfig)
{
    setField(config_name_field,QVariant::fromValue(newconfig));
}
