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
    getCommandAttribute("readtimeout", readtimeout); 
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
    
    timer = 0;
    
    while (read_messages == 0 && timer < readtimeout) 
    {
       iCanBus->canRead(inBuffer,max_messages,&read_messages,false);
       //yarp::os::Time::delay(0.1);
       std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
       timer += 100;
    }

    CanMessage &m = inBuffer[0];
    string s;
    s= "Message Id: " + std::to_string(m.getId()) + "  Data: ";
   
    for(int i = 0; i<8 ; i++)
    {
        int u = m.getData()[i];
        std::stringstream stream;
        stream << std::hex << u;
        std::string str = stream.str();
        std::transform(str.begin(), str.end(),str.begin(), ::toupper);
        if(str.length()<2) str = "0x0" + str;
        else str = "0x" + str;
        s += str + " ";
    }
      
    if(read_messages > 0)
    {
        TXLOG(Severity::debug)<< "Data received over the CAN bus : " + s << std::endl;
        std::cout << std::endl <<  "Data received over the CAN bus : " + s << std::endl << std::endl;
    }
    else
    {
        TXLOG(Severity::error)<< "Failed to receive data over the CAN bus !!" << std::endl;
        std::cout << std::endl << "Failed to receive data over the CAN bus !!" << std::endl << std::endl;
    }
    
    driver.close();
    
    return execution::continueexecution;
}
