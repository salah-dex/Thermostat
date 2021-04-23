#include <moduleapi/managers/modulemanager.h>
#include "thermostat.h"
#include <QApplication>
#include "fakethermostat.h"


int main(int argc, char *argv[])
{
  QSharedPointer<ThermostatModule> thermostatModule(new ThermostatModule);


  return ModuleManager::instance()->start(thermostatModule, argc, argv);

}
