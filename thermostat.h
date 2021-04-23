#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <moduleapi/module/module.h>
#include "fakethermostat.h"
#include "configfunctionalities.h"
#include <moduleapi/module/device.h>
#include "targetfunctionalities.h"
#include <functionalities/field/field.h>
#include <constraints/constraints.h>
#include "configenablefunctionality.h"






class ThermostatModule : public Module
{
    Q_OBJECT
public:
    ThermostatModule();
    virtual ~ThermostatModule();

    virtual void initialize() noexcept override;

    void initFakethermostat();
    void CreatModule();
    void ConnectDeviceToFakeThermostat();
    void InitializeData();
    void ReloadModule();
    void AddThermostatDevice();

    DevicePtr creatBaseDevice();

    bool connectModuleToFakeThermostat();

    FunctionalityPtr CreatTargetFunctionality();
    FunctionalityPtr CreatTemperatureFunctionality();
    FunctionalityPtr CreatConfigFunctionality();
    FunctionalityPtr CreatHumiditeFunctionality();
    FunctionalityPtr CreatEnableConfigFunctionality();


    bool addFunctionalitiesToDevice(DevicePtr ThermostatDevice);



private:
    QSharedPointer<Fakethermostat> m_Fakethermostat;

    Functionality* m_tempreratureFunctionality  =nullptr;
    Functionality* m_configFunctionality        =nullptr;
    Functionality* m_targetFunctionality        =nullptr;
    Functionality* m_humiditeFunctionality      =nullptr;
    Functionality* m_enableConfigFunctionality  =nullptr;
};

#endif // THERMOSTAT_H
