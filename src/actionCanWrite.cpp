/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanWrite.cpp
  * @author Davide Tomé <davide.tome@iit.it>
  */

#include <actionCanWrite.h>
#include <yarpActionDepotStart.h>
#include <regex>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanWrite, "yarpcanwrite");

ActionCanWrite::ActionCanWrite(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanWrite::beforeExecute()
{
    getCommandAttribute("device", device);
    getCommandAttribute("messageid", messageId);
    getCommandAttribute("cantxtimeout", cantxtimeout);   
    getCommandAttribute("canrxtimeout", canrxtimeout);
    getCommandAttribute("candevicenum", candevicenum);
    getCommandAttribute("canmyaddress", canmyaddress);   
    getCommandAttribute("data", data);   
}

execution ActionCanWrite::execute(const TestRepetitions& testrepetition)
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
    
    outBuffer=iBufferFactory->createBuffer(CAN_DRIVER_BUFFER_SIZE);

    //select the communication speed
    iCanBus->canSetBaudRate(0); //default 1MB/s
    
  
	std::regex regex(" ");

	std::vector<std::string> out(
					std::sregex_token_iterator(data.begin(), data.end(), regex, -1),
					std::sregex_token_iterator()
					);
	
    unsigned int k = out.size();
    unsigned int canMessages=0;
   
    CanMessage &msg=outBuffer[0];
   
    for(unsigned int i = 0; i < k; i++)
    {
        if(i==8) continue;
        msg.getData()[i]= std::stoi(out.at(i), 0, 16);
    }

    msg.setId(std::stoi(messageId, 0, 16));
    msg.setLen(k);
    canMessages=0;

    iCanBus->canWrite(outBuffer, 1, &canMessages);
    
    driver.close();
    
    return execution::continueexecution;
}
