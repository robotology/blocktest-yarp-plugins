/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanClose.cpp
  * @author Davide Tomé <davide.tome@iit.it>
  */

#include <actionCanClose.h>
#include <yarpActionDepotStart.h>

#include <yarp/os/Time.h>

#include <sstream>
#include <type.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCanClose, "canclose");

ActionCanClose::ActionCanClose(const CommandAttributes& commandAttributes,
                                 const std::string& testCode) : ActionYarp(commandAttributes, testCode)
{
}

void ActionCanClose::beforeExecute()
{
	getCommandAttribute("portname",   portname_);    
}

execution ActionCanClose::execute(const TestRepetitions& testrepetition)
{
   
	return execution::continueexecution;
}
