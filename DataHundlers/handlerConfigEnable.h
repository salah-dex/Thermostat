#ifndef HANDLERCONFIGENABLE_H
#define HANDLERCONFIGENABLE_H


#include<datahandlers/datahandler.h>
#include<units/units.h>



class HandlerConfigEnable: public DataHandler
{
     Q_OBJECT



public:
    HandlerConfigEnable(const QString&id=Nauvelis::newID(),
                        const DataHandlersFieldList& fields = defaultFields());


    HandlerConfigEnable(const DataHandler& copy);

    static DataHandlersFieldList defaultFields();
    static const  QString enable_name_field;
    static const  QString config_name_field;



    QString config()  const noexcept;
    bool enable()    const noexcept;

    void setConfig(const QString &newconfig);
    void setEnable(const bool &newEnable);


};

 REGISTER_DATAHANDLER_CLASS(configEnable_Functionality,HandlerConfigEnable)

#endif // HANDLERCONFIGENABLE_H
