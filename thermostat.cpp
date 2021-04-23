#include "thermostat.h"

ThermostatModule::ThermostatModule()
{

}

ThermostatModule::~ThermostatModule()
{

}

void ThermostatModule::initialize() noexcept
{
  /*  qDebug() << "Initialisation du Thermostat";
    m_Fakethermostat.reset(new Fakethermostat);

    m_Fakethermostat->show();

    if(!hasDevice(m_Fakethermostat->id()))
    {
        DevicePtr FakethermostatDevice = Device::make(Fakethermostat::iD_thermostat);
        if(!FakethermostatDevice)
        {qDebug()<<"device creation failed";}


        //setup the device

        FakethermostatDevice->setID(m_Fakethermostat->id());
        FakethermostatDevice->setDescription("Simulation d'un thermostat");
        FakethermostatDevice->setPowerType(Device::PowerType::Plugged);
        FakethermostatDevice->setStatus(Device::Status::Online);

        // temperature functionaliti

        FunctionalityPtr temperatureFunctionalityPtr(new Temperature);
        temperatureFunctionalityPtr->setID(Fakethermostat::temperatureID);

 // humidite functionaliti
        FunctionalityPtr humiditeFuncionalityPtr(new Concentration);
        humiditeFuncionalityPtr->setID(Fakethermostat::humiditeID);


           // config functionality

        Configfunctionalities* configFUNC= new Configfunctionalities();
        configFUNC->setID(Fakethermostat::configurationID);
        configFUNC->setThermostatFake(m_Fakethermostat.data()); // connection du fakethermostat
        FunctionalityPtr configFunctionalityPtr(configFUNC);
        Field* ConfigModeField = configFUNC->fieldByName(HandlerStateLiteral::field_name);
        ConstraintPtr ModeConstraints=SetConstraint::make(QStringList()
                                                          <<Fakethermostat::config_automatic
                                                          <<Fakethermostat::config_manual);
        ConfigModeField->addConstraint(ModeConstraints);


        // targetTemperature functionality

        Targetfunctionalities* targetFUNC= new Targetfunctionalities;
        targetFUNC->setID(Fakethermostat::targetID);
        targetFUNC->setThermostatFake(m_Fakethermostat.data());

        Field* HeatingSetPointField= targetFUNC->fieldByName(HandlerThermostat::field_name_heatingSetPoint);
        ConstraintPtr temperatureConstraint = IntervalConstraint::make(-20,40,false,false);
        HeatingSetPointField->addConstraint(temperatureConstraint);
        FunctionalityPtr targetFunctionalityPtr(targetFUNC);

         // configEnable functionalit

        ConfigEnablefunctionality* confEnableFUNC= new ConfigEnablefunctionality();
        confEnableFUNC->setID(Fakethermostat::enableConfigID);
        confEnableFUNC->setThermostatFake(m_Fakethermostat.data());

        Field* enableField = confEnableFUNC->fieldByName(HandlerConfigEnable::enable_name_field);
        ConstraintPtr enableConstraintes =IntervalConstraint::make(0,1,false,false);
        enableField->addConstraint(enableConstraintes);



        Field* configField =  confEnableFUNC->fieldByName(HandlerConfigEnable::config_name_field);
        ConstraintPtr configConstraints=SetConstraint::make(QStringList()
                                                          <<Fakethermostat::config_automatic
                                                          <<Fakethermostat::config_manual);
        configField->addConstraint(configConstraints);

         FunctionalityPtr configEnableFunctionalityPtr(confEnableFUNC);

        FunctionalitiesList()
                <<temperatureFunctionalityPtr
                <<humiditeFuncionalityPtr
                <<targetFunctionalityPtr
                <<configFunctionalityPtr
                <<configEnableFunctionalityPtr;


      bool ajoutFuncts;
    ajoutFuncts =  FakethermostatDevice->addFunctionalities(FunctionalitiesList()
                         <<temperatureFunctionalityPtr
                         <<humiditeFuncionalityPtr
                         <<targetFunctionalityPtr
                         <<configFunctionalityPtr
                         <<configEnableFunctionalityPtr);

  if(!ajoutFuncts) qDebug()<<"Fail to add functionalitities";

     addDevice(FakethermostatDevice);  // l'ajout du device

    }

   Device* FakethermostatDevice = device(m_Fakethermostat->id());

    // connect des functionalities du device avec et les stockers dans le module
   m_targetFunctionality       =   FakethermostatDevice->functionality(Fakethermostat::targetID);
   m_configFunctionality       =   FakethermostatDevice->functionality(Fakethermostat::configurationID);
   m_tempreratureFunctionality =   FakethermostatDevice->functionality(Fakethermostat::temperatureID);
   m_humiditeFunctionality     =   FakethermostatDevice->functionality(Fakethermostat::humiditeID);
   m_enableConfigFunctionality =   FakethermostatDevice->functionality(Fakethermostat::enableConfigID);

   // connexion des signaux et slots

   connect(m_Fakethermostat.data(),&Fakethermostat::temperatureChanged,
           [this]
          {
            Temperature* temperature= dynamic_cast<Temperature*>(m_tempreratureFunctionality);
            if(temperature==nullptr)
            {qDebug() <<"Temperature* allocation Failed"; return;}

            temperature->handler()->setTemperature(units::temperature::kelvin_t(m_Fakethermostat->temprerature()+273.5));

          });

   connect(m_Fakethermostat.data(),&Fakethermostat::targetChanged,
           [this]
         {
         Thermostat* target =dynamic_cast<Thermostat*>(m_targetFunctionality);
         if(target==nullptr)
         {qDebug() <<"Thermost* allocation Failed"; return;}

         target->handler()->setHeatingSetPoint(m_Fakethermostat->targetTemperature());

         });

    connect(m_Fakethermostat.data(),&Fakethermostat::humiditeChanged,
          [this]
         {
          Concentration* humidite= dynamic_cast<Concentration*>(m_humiditeFunctionality);
          if(humidite==nullptr)
          {qDebug() <<"humidity* allocation Failed"; return;}

          humidite->handler()->setConcentration(units::concentration::ppm_t(m_Fakethermostat->humidite()));

         });

    connect(m_Fakethermostat.data(),&Fakethermostat::configChanged,
            [this]
            {
             StateLiteral* config= dynamic_cast<StateLiteral*>(m_configFunctionality);
               if(config==nullptr)
              {qDebug() <<"config* allocation Failed"; return;}
               config->handler()->setState(m_Fakethermostat->config());
            });


   connect(m_Fakethermostat.data(),&Fakethermostat::enableChanged,
          [this]
           {
             ConfigEnablefunctionality* configenable=dynamic_cast<ConfigEnablefunctionality*>(m_enableConfigFunctionality);
            if(configenable==nullptr){qDebug()<<"configEnable* allocation failed";return;}
            configenable->handler()->setEnable(m_Fakethermostat->enable());
           });


   connect(m_Fakethermostat.data(),&Fakethermostat::configChanged,
          [this]
           {
             ConfigEnablefunctionality* configenable=dynamic_cast<ConfigEnablefunctionality*>(m_enableConfigFunctionality);
            if(configenable==nullptr){qDebug()<<"configEnable* allocation failed";return;}
            configenable->handler()->setConfig(m_Fakethermostat->config());
           });



     Configfunctionalities* configInit=dynamic_cast<Configfunctionalities*>(m_configFunctionality);
      configInit->handler()->setState(Fakethermostat::config_automatic);
      configInit->setThermostatFake(m_Fakethermostat.data());

      Targetfunctionalities* targetInit =dynamic_cast<Targetfunctionalities*>(m_targetFunctionality);
              targetInit->handler()->setHeatingSetPoint(25);
              targetInit->setThermostatFake(m_Fakethermostat.data());

      ConfigEnablefunctionality* configEnableInit = dynamic_cast<ConfigEnablefunctionality*>(m_enableConfigFunctionality);
       configEnableInit->handler()->setConfig(Fakethermostat::config_automatic);
       configEnableInit->handler()->setEnable(Fakethermostat::enable_mode);
       configEnableInit->setThermostatFake(m_Fakethermostat.data());

   */


    initFakethermostat();
    CreatModule();
    connectModuleToFakeThermostat();
    InitializeData();
}


void ThermostatModule::initFakethermostat()
{
    qDebug() << "Initialisation du Thermostat";
    m_Fakethermostat.reset(new Fakethermostat);
    if(m_Fakethermostat==nullptr)
     qFatal("Initialisation Of Thermostat GUI failed");
     m_Fakethermostat->show();
 }

void ThermostatModule::CreatModule()
{
     setName("Module thermostat");

     if(! hasDevice(m_Fakethermostat->id()))
     {AddThermostatDevice();}

     ConnectDeviceToFakeThermostat();

}


void ThermostatModule::AddThermostatDevice()
{
     DevicePtr MyDevice = creatBaseDevice();
     if(!MyDevice) qFatal("Initialisation Device Failed");

     if(!addFunctionalitiesToDevice(MyDevice)) qFatal("Functionalities init Failed");

     if(!addDevice(MyDevice))qFatal("Adding DeviceFailed");

}

DevicePtr ThermostatModule::creatBaseDevice()
{

    DevicePtr Device = Device::make(Fakethermostat::iD_thermostat,"Fake thermostat");
    if(!Device) {return nullptr;}

     Device->setPowerType(Device::Plugged);
     Device->setStatus(Device::Online);
     Device->setDescription("Ceci est une simulation d'un thermostat réel");
   return Device;
}

FunctionalityPtr ThermostatModule::CreatConfigFunctionality()
{
     Configfunctionalities* functionality(new Configfunctionalities);
     functionality->setID(Fakethermostat::configurationID);
     functionality->setThermostatFake(m_Fakethermostat.data());
     functionality->setName("Configuration Functionality");

     return FunctionalityPtr(functionality);
}


FunctionalityPtr ThermostatModule::CreatTargetFunctionality()
{

    Targetfunctionalities* functionality(new Targetfunctionalities);
    functionality->setID(Fakethermostat::targetID);
    functionality->setThermostatFake(m_Fakethermostat.data());

    Field* HeatingSetPointField= functionality->fieldByName(HandlerThermostat::field_name_heatingSetPoint);
    ConstraintPtr temperatureConstraint = IntervalConstraint::make(-20,40,false,false);
    HeatingSetPointField->addConstraint(temperatureConstraint);

    return FunctionalityPtr(functionality);
}

FunctionalityPtr ThermostatModule::CreatTemperatureFunctionality()
{
    FunctionalityPtr functionality(new Temperature);
    functionality->setID(Fakethermostat::temperatureID);
      return FunctionalityPtr(functionality);
}

FunctionalityPtr ThermostatModule::CreatHumiditeFunctionality()
{
    FunctionalityPtr functionality(new Concentration);
    functionality->setID(Fakethermostat::humiditeID);
    return FunctionalityPtr(functionality);

}


FunctionalityPtr ThermostatModule::CreatEnableConfigFunctionality()
{
    ConfigEnablefunctionality* confEnableFUNC= new ConfigEnablefunctionality();
    confEnableFUNC->setID(Fakethermostat::enableConfigID);
    confEnableFUNC->setThermostatFake(m_Fakethermostat.data());

    Field* enableField = confEnableFUNC->fieldByName(HandlerConfigEnable::enable_name_field);
    ConstraintPtr enableConstraintes =IntervalConstraint::make(0,1,false,false);
    enableField->addConstraint(enableConstraintes);


    Field* configField =  confEnableFUNC->fieldByName(HandlerConfigEnable::config_name_field);
    ConstraintPtr configConstraints=SetConstraint::make(QStringList()
                                                      <<Fakethermostat::config_automatic
                                                      <<Fakethermostat::config_manual);
    configField->addConstraint(configConstraints);

    return FunctionalityPtr(confEnableFUNC);

}
bool ThermostatModule::addFunctionalitiesToDevice(DevicePtr FakethermostatDevice)
{
    bool ajoutFuncts;

    FunctionalityPtr targetfunctionality   = CreatTargetFunctionality();
    FunctionalityPtr configfunctionality   = CreatConfigFunctionality();
    FunctionalityPtr humiditefunctionality = CreatHumiditeFunctionality();
    FunctionalityPtr Temperatfunctionality = CreatTemperatureFunctionality();
    FunctionalityPtr enableconfigfunctionaity = CreatEnableConfigFunctionality();
    if(!targetfunctionality ||!configfunctionality ||!humiditefunctionality ||!Temperatfunctionality ||!enableconfigfunctionaity)
        qFatal("functionalities creation failed null");


  ajoutFuncts =  FakethermostatDevice->addFunctionalities(FunctionalitiesList()
                       <<Temperatfunctionality
                       <<humiditefunctionality
                       <<targetfunctionality
                       <<configfunctionality
                       <<enableconfigfunctionaity);
    return ajoutFuncts;

}





 void ThermostatModule::ConnectDeviceToFakeThermostat()
 {
     Device* FakethermostatDevice = device(m_Fakethermostat->id());
     if(!FakethermostatDevice)
         qDebug()<<"Connection failed,Device is nullptr";

      // connect des functionalities du device avec et les stockers dans le module
     m_targetFunctionality       =   FakethermostatDevice->functionality(Fakethermostat::targetID);
     m_configFunctionality       =   FakethermostatDevice->functionality(Fakethermostat::configurationID);
     m_tempreratureFunctionality =   FakethermostatDevice->functionality(Fakethermostat::temperatureID);
     m_humiditeFunctionality     =   FakethermostatDevice->functionality(Fakethermostat::humiditeID);
     m_enableConfigFunctionality =   FakethermostatDevice->functionality(Fakethermostat::enableConfigID);

     // connexion des signaux et slots
     if(! m_enableConfigFunctionality)qFatal("enableConfigFunctionality is null");
 }



 bool ThermostatModule::connectModuleToFakeThermostat()
 {

    bool tempConnect =connect(m_Fakethermostat.data(),&Fakethermostat::temperatureChanged,
             [this]
            {
              Temperature* temperature= dynamic_cast<Temperature*>(m_tempreratureFunctionality);
              if(temperature==nullptr)
              {qDebug() <<"Temperature* allocation Failed"; return;}

              temperature->handler()->setTemperature(units::temperature::kelvin_t(m_Fakethermostat->temprerature()+273.5));

            });
     if(!tempConnect)qFatal("connection to Temperature Handler failed");


   bool  taregtConnect= connect(m_Fakethermostat.data(),&Fakethermostat::targetChanged,
             [this]
           {
           Thermostat* target =dynamic_cast<Thermostat*>(m_targetFunctionality);
           if(target==nullptr)
           {qDebug() <<"Thermost* allocation Failed"; return;}

           target->handler()->setHeatingSetPoint(m_Fakethermostat->targetTemperature());

           });
            if(!taregtConnect)qFatal("connection to target Handler failed");



     bool humiditeConnect = connect(m_Fakethermostat.data(),&Fakethermostat::humiditeChanged,
            [this]
           {
            Concentration* humidite= dynamic_cast<Concentration*>(m_humiditeFunctionality);
            if(humidite==nullptr)
            {qDebug() <<"humidity* allocation Failed"; return;}

            humidite->handler()->setConcentration(units::concentration::ppm_t(m_Fakethermostat->humidite()));

           });
     if(!humiditeConnect)qFatal("connection to humidite Handler failed");



      bool configConnect =   connect(m_Fakethermostat.data(),&Fakethermostat::configChanged,
              [this]
              {
               StateLiteral* config= dynamic_cast<StateLiteral*>(m_configFunctionality);
                 if(config==nullptr)
                {qDebug() <<"config* allocation Failed"; return;}
                 config->handler()->setState(m_Fakethermostat->config());
              });
      if(!configConnect)qFatal("connection to config Handler failed");



    bool  enableConnect=connect(m_Fakethermostat.data(),&Fakethermostat::enableChanged,
             [this]
              {
                ConfigEnablefunctionality* configenable=dynamic_cast<ConfigEnablefunctionality*>(m_enableConfigFunctionality);
               if(configenable==nullptr){qDebug()<<"configEnable* allocation failed";return;}
               configenable->handler()->setEnable(m_Fakethermostat->enable());
              });
    if(!enableConnect)qFatal("connection to enable Handler failed");


     bool configConnect2 =  connect(m_Fakethermostat.data(),&Fakethermostat::configChanged,
             [this]
              {
                ConfigEnablefunctionality* configenable=dynamic_cast<ConfigEnablefunctionality*>(m_enableConfigFunctionality);
               if(configenable==nullptr){qDebug()<<"configEnable* allocation failed";return;}
               configenable->handler()->setConfig(m_Fakethermostat->config());
              });

     if(!configConnect2 )qFatal("connection to config 2 Handler failed");

      if(configConnect && humiditeConnect && taregtConnect && tempConnect && enableConnect && configConnect2) return true;
      else
          return false;
 }

 void ThermostatModule::InitializeData()
 {
     Configfunctionalities* configInit=dynamic_cast<Configfunctionalities*>(m_configFunctionality);
      configInit->handler()->setState(Fakethermostat::config_automatic);
      configInit->setThermostatFake(m_Fakethermostat.data());



      Targetfunctionalities* targetInit =dynamic_cast<Targetfunctionalities*>(m_targetFunctionality);
              targetInit->handler()->setHeatingSetPoint(m_Fakethermostat->targetTemperature());
              targetInit->setThermostatFake(m_Fakethermostat.data());



     ConfigEnablefunctionality* configEnableInit = dynamic_cast<ConfigEnablefunctionality*>(m_enableConfigFunctionality);
          configEnableInit->handler()->setConfig(Fakethermostat::config_automatic);
          configEnableInit->handler()->setEnable(Fakethermostat::enable_mode);
          configEnableInit->setThermostatFake(m_Fakethermostat.data());


              if(!configInit || !targetInit || !configEnableInit)
                qFatal("Initiation of functionalities failed ");
 }
