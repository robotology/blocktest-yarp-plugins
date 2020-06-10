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
{
    getCommandAttribute("device", device);
    getCommandAttribute("messageid", messageId);
    getCommandAttribute("cantxtimeout", cantxtimeout);   
    getCommandAttribute("canrxtimeout", canrxtimeout);
    getCommandAttribute("candevicenum", candevicenum);
    getCommandAttribute("canmyaddress", canmyaddress);   
    getCommandAttribute("data", data); 
}

execution ActionCanRead::execute(const TestRepetitions& testrepetition)
{
    Property prop;

    prop.put("device", device);
    prop.put("messageid", messageId);

    prop.put("CanTxTimeout", cantxtimeout);
    prop.put("CanRxTimeout", canrxtimeout);
    prop.put("CanDeviceNum", candevicenum);
    prop.put("CanMyAddress", canmyaddress);

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
        yError("Error opening can device not available\n");
    }
    driver.view(iBufferFactory);
    
    inBuffer=iBufferFactory->createBuffer(CAN_DRIVER_BUFFER_SIZE);

    //select the communication speed
    iCanBus->canSetBaudRate(0); //default 1MB/s
    unsigned int canMessages=0;

    unsigned int max_messages=CAN_DRIVER_BUFFER_SIZE;
    unsigned int read_messages = 0;

    while (read_messages == 0)
    {
       bool b = iCanBus->canRead(inBuffer,max_messages,&read_messages,false);

    }

    for (unsigned int i=0; i<read_messages; i++)
    {
        CanMessage& m= inBuffer[i];
        unsigned int currId=m.getId();
        std::cout << currId << std::endl;
    }

    
    driver.close();
    
    

    return execution::continueexecution;
}
