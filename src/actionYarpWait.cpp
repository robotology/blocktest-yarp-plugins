/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionYarpWait.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#include "actionYarpWait.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionYarpWait, yarpactions::yarpwait);

namespace YarpActions
{

ActionYarpWait::ActionYarpWait(const CommandAttributes &commandAttributes, const std::string &testCode) : ActionYarp(commandAttributes, testCode)
{
    getCommandAttribute("seconds", seconds_);    
}

void ActionYarpWait::beforeExecute()
{
    getCommandAttribute("seconds", seconds_);
}

execution ActionYarpWait::execute(const TestRepetitions&)
{
    //yarp::os::yarpClockType clockType=yarp::os::Time::getClockType();
    //TXLOG(Severity::debug)<<"Using clock type config:"<<yarp::os::Time::clockTypeToString(clockType)<<" Wait value:"<<seconds_<<std::endl;
    yarp::os::Time::delay(seconds_);
    return execution::continueexecution;
}

} // namespace YarpActions
