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

#include <actionCanWritePD.h>
#include <yarpActionDepotStart.h>
#include <regex>

#include <sstream>
#include <type.h>

using namespace std;
using namespace yarp::os;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanWritePD, yarpactions::yarpcanwritepd);

namespace YarpActions
{
ActionCanWritePD::ActionCanWritePD(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanWritePD::beforeExecute()
{
   
    getCommandAttribute("polydrivertag",polydrivertag_);
    getCommandAttribute("device", device_);
    getCommandAttribute("canBaudRate", canBaudRate_);
    getCommandAttribute("messageid", messageId_);
    getCommandAttribute("cantxtimeout", canTxTimeout_);   
    getCommandAttribute("canrxtimeout", canRxTimeout_);
    getCommandAttribute("candevicenum", canDeviceNum_);
    getCommandAttribute("canmyaddress", canMyAddress_);   
    getCommandAttribute("data", data_);       

}

execution ActionCanWritePD::execute(const TestRepetitions& testrepetition)
{
    auto exists {true};
    stringstream logStream;
    Property prop;
    bool openFail(false);

    prop.put("device", device_);
    prop.put("messageid", messageId_);
    prop.put("canBaudRate", canBaudRate_);
    prop.put("CanTxTimeout", canTxTimeout_);
    prop.put("CanRxTimeout", canRxTimeout_);
    prop.put("CanDeviceNum", canDeviceNum_);
    prop.put("CanMyAddress", canMyAddress_);

    prop.put("CanTxQueueSize", CAN_DRIVER_BUFFER_SIZE_);
    prop.put("CanRxQueueSize", CAN_DRIVER_BUFFER_SIZE_);
   
    iCanBus_=0;
    iBufferFactory_=0;
    
    auto pdr = YarpActionDepotStart::polyDriverDepot_.find(polydrivertag_);
    
    if (pdr == YarpActionDepotStart::polyDriverDepot_.end())
    {
        std::cout << std::endl << "Unable to find " << polydrivertag_ << std::endl << std::endl;
        logStream << "Unable to find " << polydrivertag_ <<" in the depot";
        addProblem(testrepetition, Severity::error, logStream.str(),true);
        return execution::continueexecution;
    }
    auto pdr_ptr = pdr->second;
    
    pdr_ptr->open(prop);

   if (!pdr_ptr->isValid())
    {
        std::cout << std::endl << "Error opening PolyDriver check parameters" << std::endl << std::endl;
        TXLOG(Severity::error)<<"Error opening PolyDriver check parameters"<<std::endl;
     //   openFail = true;
    }
    pdr_ptr->view(iCanBus_);
    if (!iCanBus_)
    {
        std::cout << std::endl << "Error opening can device not available" << std::endl << std::endl;
        TXLOG(Severity::debug)<<"Error opening can device not available";
      //  openFail = true;
    }
    pdr_ptr->view(iBufferFactory_);

    outBuffer_ = iBufferFactory_->createBuffer(CAN_DRIVER_BUFFER_SIZE_);

        //select the communication speed
        //iCanBus_->canSetBaudRate(0); //default 1MB/s


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
                
        if (iCanBus_->canWrite(outBuffer_, 1, &canMessages))
        {
            TXLOG(Severity::debug)<< "Data sent over the CAN bus : " + data_ << std::endl;
            std::cout << std::endl << "Data sent over the CAN bus : " + data_ << std::endl << std::endl;
        }
        else
        {
            TXLOG(Severity::error)<< "Failed to send data over the CAN bus !!" << std::endl;
            std::cout << std::endl << "Failed to send data over the CAN bus !!" << std::endl << std::endl;
        }
            
        pdr_ptr->close();

    return execution::continueexecution;
}
}