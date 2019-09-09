/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionPrepareStraightWalking.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#include "thrifts/WalkingCommands.h"
#include "actionPrepareStraightWalking.h"

#include "logger.h"
#include "report.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPrepareStraightWalking,"preparestraightwalking");

ActionPrepareStraightWalking::ActionPrepareStraightWalking(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{}     

void ActionPrepareStraightWalking::beforeExecute()
{
}

execution ActionPrepareStraightWalking::execute(const TestRepetitions& testrepetition)
{
    yarp::os::Port rpcPortWalking;
    WalkingCommands walkingCommands;
    openWalking(rpcPortWalking,walkingCommands);

    bool ok=walkingCommands.prepareStraightWalking();
    if(!ok)
    {
        addProblem(testrepetition,Severity::error,"Prepare straight walking failed",true);
    }
    closeWalking(rpcPortWalking);
    TXLOG(Severity::info)<<"Prepare straight walking OK"<<std::endl;
    return execution::continueexecution;;
}
