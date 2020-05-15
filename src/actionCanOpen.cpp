/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanOpen.cpp
  * @author Davide Tomé <davide.tome@iit.it>
  */

#include <actionCanOpen.h>
#include <yarpActionDepotStart.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanOpen, "canopen");

ActionCanOpen::ActionCanOpen(const CommandAttributes& commandAttributes,
                               const std::string& testCode) : ActionCanClose(commandAttributes, testCode)
{}

void ActionCanOpen::beforeExecute()
{
    ActionCanClose::beforeExecute();
}

execution ActionCanOpen::execute(const TestRepetitions& testrepetition)
{
    /*
    TO DO
    */

    return execution::continueexecution;
}
