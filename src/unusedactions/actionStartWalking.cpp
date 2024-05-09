/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionStartWalking.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionStartWalking.h"
#include "logger.h"
#include "report.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionStartWalking,yarpactions::startwalking);

namespace YarpActions
{

ActionStartWalking::ActionStartWalking(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{}     


void ActionStartWalking::beforeExecute()
{
}

BlockTestCore::execution ActionStartWalking::execute(const TestRepetitions& testrepetition)
{
    yarp::os::Port rpcPortWalking;
    WalkingCommands walkingCommands;
    openWalking(rpcPortWalking,walkingCommands);

    bool ok=walkingCommands.startWalking();
    if(!ok)
    {
        addProblem(testrepetition,Severity::error,"start walking failed",true);
    }

    closeWalking(rpcPortWalking);
}

}