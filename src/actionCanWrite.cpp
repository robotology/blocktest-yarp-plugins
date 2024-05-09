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

#include "syntax.h"
#include <actionCanWrite.h>
#include <yarpActionDepotStart.h>
#include <regex>

#include <sstream>
#include <type.h>

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanWrite, yarpactions::yarpcanwrite);

namespace YarpActions
{
ActionCanWrite::ActionCanWrite(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanWrite::beforeExecute()
{
    getCommandAttribute(yarpsyntax::wrappername,polyDriverTag_);
    getCommandAttribute("messageid", messageId_);
    getCommandAttribute("data", data_);   
}

execution ActionCanWrite::execute(const TestRepetitions& testrepetition)
{
    auto exists {true};
    stringstream logStream;
    bool openFail(false);

    auto pdr = YarpActionDepotStart::polyDriverDepot_.find(polyDriverTag_);
    
    if (pdr == YarpActionDepotStart::polyDriverDepot_.end())
    {
        logStream << "Unable to find " << polyDriverTag_ <<" in the depot";
        addProblem(testrepetition, Severity::error, logStream.str(),true);
        return BlockTestCore::execution::continueexecution;
    }
    auto pdrPtr = pdr->second;
   
    iCanBus_=0;
    iBufferFactory_=0;

    if (!pdrPtr->isValid())
    {
        TXLOG(Severity::error)<<"Error opening PolyDriver check parameters"<<std::endl;
        openFail = true;
    }
    pdrPtr->view(iCanBus_);
    if (!iCanBus_)
    {
        TXLOG(Severity::debug)<<"Error opening can device not available";
        openFail = true;
    }
    pdrPtr->view(iBufferFactory_);
    
    if(!openFail)
    {
        outBuffer_ = iBufferFactory_->createBuffer(CAN_DRIVER_BUFFER_SIZE_);

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
                
        if (iCanBus_->canWrite(outBuffer_, 1, &canMessages))
        {
            TXLOG(Severity::debug)<< "Data sent over the CAN bus : Message Id: " + std::to_string(msg.getId()) + "  Data: " + data_ << std::endl;
        }
        else
        {
            TXLOG(Severity::error)<< "Failed to send data over the CAN bus !!" << std::endl;
        }
            
    }
    
    return BlockTestCore::execution::continueexecution;
}
}