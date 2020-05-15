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

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanRead, "canRead");

ActionCanRead::ActionCanRead(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionCanRead::beforeExecute()
{
    getCommandAttribute("meassageId",   messageId_);   
    getCommandAttribute("message",   message_);
}

execution ActionCanRead::execute(const TestRepetitions& testrepetition)
{
    /*
    TO DO
    */

    return execution::continueexecution;
}
