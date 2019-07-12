/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionSetVelocity.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionSetVelocity.h"

#include "logger.h"
#include "report.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionSetVelocity,"setvelocity");

namespace YarpActions
{

ActionSetVelocity::ActionSetVelocity(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
}     

void ActionSetVelocity::beforeExecute()
{
    getCommandAttribute("xvelocity",xVelocity_);    
    getCommandAttribute("yvelocity",yVelocity_);          
}

execution ActionSetVelocity::execute(const TestRepetitions& testrepetition)
{
    yarp::os::Port rpcPortWalking;
    WalkingCommands walkingCommands;
    openWalking(rpcPortWalking,walkingCommands);

    bool ok=walkingCommands.sendVelocity(normalizeDouble(xVelocity_,false),normalizeDouble(yVelocity_,false));
    TXLOG(Severity::debug)<<"xVelocity:"<<normalizeDouble(xVelocity_,true)<<" yVelocity:"<<normalizeDouble(yVelocity_,true)<<std::endl;
    if(!ok)
    {
        TXLOG(Severity::critical)<<"send velocity failed"<<std::endl;
        addProblem(testrepetition,Severity::critical,"send velocity failed");
    }

    closeWalking(rpcPortWalking);    
    return execution::continueexecution;;
}
}