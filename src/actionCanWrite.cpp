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

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanWrite, yarpactions::yarpcanwrite);

namespace YarpActions
{
ActionCanWrite::ActionCanWrite(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanWrite::beforeExecute()
{
    getCommandAttribute("device", device_);
    getCommandAttribute("messageid", messageId_);
    getCommandAttribute("cantxtimeout", canTxTimeout_);   
    getCommandAttribute("canrxtimeout", canRxTimeout_);
    getCommandAttribute("candevicenum", canDeviceNum_);
    getCommandAttribute("canmyaddress", canMyAddress_);   
    getCommandAttribute("data", data_);   
}

execution ActionCanWrite::execute(const TestRepetitions&)
{
    Property prop;
    bool openFail(false);

    prop.put("device", device_);
    prop.put("messageid", messageId_);

    prop.put("CanTxTimeout", canTxTimeout_);
    prop.put("CanRxTimeout", canRxTimeout_);
    prop.put("CanDeviceNum", canDeviceNum_);
    prop.put("CanMyAddress", canMyAddress_);

    prop.put("CanTxQueueSize", CAN_DRIVER_BUFFER_SIZE_);
    prop.put("CanRxQueueSize", CAN_DRIVER_BUFFER_SIZE_);
   
    iCanBus_=0;
    iBufferFactory_=0;

    //open the can driver
    driver_.open(prop);
    if (!driver_.isValid())
    {
        TXLOG(Severity::error)<<"Error opening PolyDriver check parameters"<<std::endl;
        openFail = true;
    }
    driver_.view(iCanBus_);
    if (!iCanBus_)
    {
        TXLOG(Severity::debug)<<"Error opening can device not available";
        openFail = true;
    }
    driver_.view(iBufferFactory_);
    
    if(!openFail)
    {
        outBuffer_ = iBufferFactory_->createBuffer(CAN_DRIVER_BUFFER_SIZE_);

        //select the communication speed
        iCanBus_->canSetBaudRate(0); //default 1MB/s


        std::regex regex(" ");

        std::vector<std::string> out(
                        std::sregex_token_iterator(data_.begin(), data_.end(), regex, -1),
                        std::sregex_token_iterator()
                        );

        unsigned int k = out.size();
        unsigned int canMessages = 0;

        CanMessage &msg = outBuffer_[0];

        for(unsigned int i = 0; i < k; i++)
        {
            if(i==8) continue;
            msg.getData()[i]= std::stoi(out.at(i), 0, 16);
        }

        msg.setId(std::stoi(messageId_, 0, 16));
        msg.setLen(k);
        canMessages = 0;

        bool res = iCanBus_->canWrite(outBuffer_, 1, &canMessages);
                
        if (res)
        {
            TXLOG(Severity::debug)<< "Data sent over the CAN bus : " + data_ << std::endl;
            std::cout << std::endl << "Data sent over the CAN bus : " + data_ << std::endl << std::endl;
        }
        else
        {
            TXLOG(Severity::error)<< "Failed to send data over the CAN bus !!" << std::endl;
            std::cout << std::endl << "Failed to send data over the CAN bus !!" << std::endl << std::endl;
        }
            
        driver_.close();

    }
    
    return execution::continueexecution;
}
}