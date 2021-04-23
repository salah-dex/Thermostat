#ifndef FAKETHERMOSTAT_H
#define FAKETHERMOSTAT_H

#include <QMainWindow>
#include <QtDebug>
namespace Ui {
class Fakethermostat;
}

class Fakethermostat : public QMainWindow
{
    Q_OBJECT

public:

    explicit Fakethermostat(QWidget *parent = nullptr);

    ~Fakethermostat();

    static const QString config_manual;
    static const QString config_automatic;

    static const bool enable_mode;
    static const bool disable_mode;

    static const QString temperatureID;
    static const QString targetID;
    static const QString humiditeID;
    static const QString configurationID;
    static const QString enableConfigID;

    static const QString iD_thermostat;




    double temprerature() const;

    double targetTemperature() const;

    int humidite() const;

    QString config() const;

    QString id() const;

    bool enable() const;




    void RefreshTargetData();
    void RefreshConfigData();


    void setConfig(const QString &config);

    void setTargetTemperature(double targetTemperature);

    void setTemprerature(double temprerature);

    void setHumidite(int humidite);

    void setId(const QString &id);

    void setEnable(bool enable);




signals:
    void temperatureChanged ();
    void targetChanged();
    void humiditeChanged();
    void configChanged();
    void enableChanged();

private:
    Ui::Fakethermostat *ui;
    QString m_id;
    double  m_temprerature;
    double  m_targetTemperature;
    int     m_humidite;
    QString m_config;
    bool    m_enable;
};

#endif // FAKETHERMOSTAT_H
