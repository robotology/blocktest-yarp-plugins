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

#include "syntax.h"
#include <actionCanRead.h>
#include <yarpActionDepotStart.h>

#include <sstream>
#include <type.h>

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanRead, yarpactions::yarpcanread);

namespace YarpActions
{
ActionCanRead::ActionCanRead(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanRead::beforeExecute()
{
    getCommandAttribute(yarpsyntax::wrappername,polyDriverTag_);
    getCommandAttribute("messageid", messageId_); 
    getCommandAttribute("data", data_);  
    getCommandAttribute("readtimeout", readTimeout_); 
}


execution ActionCanRead::execute(const TestRepetitions& testrepetition)
{
    unsigned int readMessages=0;
    int timer=0;
    bool openFail(false);
    stringstream logStream;


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
        inBuffer_ = iBufferFactory_->createBuffer(CAN_DRIVER_BUFFER_SIZE_);

    iCanBus_->canSetBaudRate(0); //default 1MB/s
   
    while (readMessages == 0 && timer < readTimeout_) 
    {
       iCanBus_->canRead(inBuffer_,CAN_DRIVER_BUFFER_SIZE_,&readMessages,false);
       std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
       timer += 10;
    }

    CanMessage &m = inBuffer_[0];
    std::string s;
    s= "Message Id: " + std::to_string(m.getId()) + "  Data: ";
    unsigned int x = std::stoi(messageId_, 0, 16);

    if(m.getId() == x)
    {
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
    }
    else readMessages = 0;

    if(readMessages > 0)
    {
        TXLOG(Severity::debug)<< "Data received over the CAN bus : " + s << std::endl;
    }
    else
    {
        TXLOG(Severity::error)<< "Failed to receive data over the CAN bus !!" << std::endl;
    }
    
    }

    return BlockTestCore::execution::continueexecution;
}
}