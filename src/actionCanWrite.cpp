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

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanWrite, "canwrite");

ActionCanWrite::ActionCanWrite(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanWrite::beforeExecute()
{
    getCommandAttribute("meassageId",   messageId_);   
    getCommandAttribute("message",   message_);
}

execution ActionCanWrite::execute(const TestRepetitions& testrepetition)
{
    /*
    TO DO
    */

    return execution::continueexecution;
}
