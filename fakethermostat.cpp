#include "fakethermostat.h"
#include "ui_fakethermostat.h"
#include <iostream>
#include <stdlib.h>

 const QString Fakethermostat::config_manual="Manual";
 const QString Fakethermostat::config_automatic="Automatic";

 const bool Fakethermostat::enable_mode =true;
 const bool Fakethermostat::disable_mode =false;

 const QString Fakethermostat::temperatureID   = "hfgr-heg5-58ik-vf47";
 const QString Fakethermostat::targetID        = "hfgr-poiu-58ik-vf47";
 const QString Fakethermostat::humiditeID      = "hfgr-wxcv-58ik-vf47";
 const QString Fakethermostat::configurationID = "hfgr-sao4-58ik-vf47";
 const QString Fakethermostat::iD_thermostat   =  "Thermostat_35_1F";
 const QString Fakethermostat::enableConfigID  = "cie5-jhi12-lopm-vf47";



Fakethermostat::Fakethermostat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fakethermostat)
{
    ui->setupUi(this);

    ui->tempRatureDoubleSpinBox->setValue(m_temprerature);
    ui->targetTempRatureDoubleSpinBox->setValue(m_targetTemperature);
    ui->humiditeSpinBox->setValue(m_humidite);
    ui->modeConfigurationComboBox->setCurrentText(m_config);

     //connectiques pour température


    connect( ui->tempRatureDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged),
            [this](double temp)
    { if (m_config == config_automatic) setTemprerature(temp);
        qDebug()<<"temperature="<<QString::number(this->temprerature())<<"C";});

    connect(this,&Fakethermostat::temperatureChanged,
            [this]  {ui->tempRatureDoubleSpinBox->setValue(temprerature());});

  // connectique pour target température

    connect (ui->targetTempRatureDoubleSpinBox,qOverload<double>(&QDoubleSpinBox::valueChanged),
             [this](double target)
    { if (m_config == config_automatic) setTargetTemperature(target);
        qDebug()<<"Target ="<<QString::number(this->targetTemperature())<<"C"; });

    connect(this,&Fakethermostat::targetChanged,
            [this] {ui->targetTempRatureDoubleSpinBox->setValue(targetTemperature());});

  // connectique pour humidite

    connect(ui->humiditeSpinBox,qOverload<int>(&QSpinBox::valueChanged),
            [this](int humid)
    { if (m_config == config_automatic) setHumidite(humid);
        qDebug()<<"humidite="<<QString::number(this->humidite())<<"%"; });

    connect(this,&Fakethermostat ::humiditeChanged,
            [this]{ui->humiditeSpinBox->setValue(humidite());});

    // connectique pour Mode Configuration

      connect(ui->modeConfigurationComboBox,&QComboBox::currentTextChanged,
              [this](const QString& currentText)
      {setConfig(currentText); qDebug()<<"Config"<<currentText; });

      connect(this,&Fakethermostat::configChanged,
              [this]{ui-> modeConfigurationComboBox->setCurrentText(config());});

    // connectique pour enable

      connect(this,&Fakethermostat::enableChanged,
              [this]{ui->modeConfigurationComboBox->setEnabled(enable());
                     ui->targetTempRatureDoubleSpinBox->setEnabled(enable());});


      // initialisation
      setId(Fakethermostat::iD_thermostat);
      setConfig(config_automatic);
      setHumidite(0);
      setTargetTemperature(25);
      setEnable(enable_mode);



}




Fakethermostat::~Fakethermostat()
{
    delete ui;
}

double Fakethermostat::temprerature() const
{
    return m_temprerature;
}

void Fakethermostat::setTemprerature(double temprerature)
{   if(m_temprerature==temprerature) return;
    m_temprerature = temprerature;
    emit temperatureChanged();

}


void Fakethermostat::RefreshTargetData()
{
    setTargetTemperature(ui->targetTempRatureDoubleSpinBox->value());
}

void Fakethermostat::RefreshConfigData()
{
    setConfig(ui->modeConfigurationComboBox->currentText());
}

double Fakethermostat::targetTemperature() const
{
    return m_targetTemperature;
}

void Fakethermostat::setTargetTemperature(double targetTemperature)
{
    if(m_targetTemperature==targetTemperature) return;
    m_targetTemperature = targetTemperature;
    emit targetChanged();
}

int Fakethermostat::humidite() const
{
    return m_humidite;
}

void Fakethermostat::setHumidite(int humidite)
{
    if(m_humidite==humidite)return;
    m_humidite = humidite;
    emit humiditeChanged();
}

QString Fakethermostat::id() const
{
    return Fakethermostat::iD_thermostat;
}

void Fakethermostat::setId(const QString &id)
{
    m_id = id;
}

bool Fakethermostat::enable() const
{
    return m_enable;
}

void Fakethermostat::setEnable(bool enable)
{
   if(m_enable==enable) return;
   m_enable = enable;
   emit enableChanged();
}

QString Fakethermostat::config() const
{
    return m_config;
}

void Fakethermostat::setConfig(const QString &config)
{   if(m_config==config) return;
    m_config = config;
    emit configChanged();
}
