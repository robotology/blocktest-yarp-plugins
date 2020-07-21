/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionResetWalking.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#include "thrifts/WalkingCommands.h"
#include "actionResetWalking.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "logger.h"
#include "report.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionResetWalking,yarpactions::resetwalking);

namespace YarpActions
{

ActionResetWalking::ActionResetWalking(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{}     

void ActionResetWalking::beforeExecute()
{
}

execution ActionResetWalking::execute(const TestRepetitions& testrepetition)
{
    yarp::os::Port rpcPortWalking;
    WalkingCommands walkingCommands;
    openWalking(rpcPortWalking,walkingCommands);

    bool ok=walkingCommands.stopWalking();
    if(!ok)
    {
        addProblem(testrepetition,Severity::error,"Reset walking failed",true);
    }    

    closeWalking(rpcPortWalking);       
    return execution::continueexecution;;
}

}