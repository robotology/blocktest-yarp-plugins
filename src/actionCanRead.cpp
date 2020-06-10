/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanRead.cpp
  * @author Davide Tomé <davide.tome@iit.it>
  */

#include <actionCanRead.h>
#include <yarpActionDepotStart.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanRead, "yarpcanread");

ActionCanRead::ActionCanRead(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanRead::beforeExecute()
{}

execution ActionCanRead::execute(const TestRepetitions& testrepetition)
{
    Property prop;
    prop.put("device", "socketcan");

    prop.put("CanTxTimeout", 500);
    prop.put("CanRxTimeout", 500);
    prop.put("CanDeviceNum", 0);
    prop.put("CanMyAddress", 0);

    prop.put("CanTxQueueSize", CAN_DRIVER_BUFFER_SIZE);
    prop.put("CanRxQueueSize", CAN_DRIVER_BUFFER_SIZE);
   
    iCanBus=0;
    iBufferFactory=0;
     //open the can driver
    driver.open(prop);
    if (!driver.isValid())
    {
        yError("Error opening PolyDriver check parameters\n");
    }
    driver.view(iCanBus);
    if (!iCanBus)
    {
        yError ("Error opening can device not available\n");
    }
    driver.view(iBufferFactory);
    outBuffer=iBufferFactory->createBuffer(CAN_DRIVER_BUFFER_SIZE);
    inBuffer=iBufferFactory->createBuffer(CAN_DRIVER_BUFFER_SIZE);

    //select the communication speed
    iCanBus->canSetBaudRate(0); //default 1MB/s
    
    unsigned int canMessages=0;
    
    bool res=iCanBus->canRead(inBuffer,CAN_DRIVER_BUFFER_SIZE,&canMessages);
    
    driver.close();
    
    
    return execution::continueexecution;
}
