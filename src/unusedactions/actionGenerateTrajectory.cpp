/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionGenerateTrajectory.cpp
 * @authors: Luca Tricerri <luca.tricerri@iit.it>
 */



#include "thrifts/WalkingCommands.h"
#include "actionGenerateTrajectory.h"

#include "logger.h"
#include "report.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionGenerateTrajectory,yarpactions::generatetrajectory);

namespace YarpActions
{
ActionGenerateTrajectory::ActionGenerateTrajectory(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{    
}     

void ActionGenerateTrajectory::beforeExecute()
{
    getCommandAttribute("lenght",lenght_);    
}


BlockTestCore::execution ActionGenerateTrajectory::execute(const TestRepetitions& testrepetition)
{
    yarp::os::Port rpcPortWalking;
    WalkingCommands walkingCommands;
    openWalking(rpcPortWalking,walkingCommands);

    bool ok=walkingCommands.generateTrajectories(lenght_);
    if(!ok)
    {
        addProblem(testrepetition,Severity::error,"Generate trajectory failed",true);
    }

    closeWalking(rpcPortWalking);
    return BlockTestCore::execution::continueexecution;;
}
}