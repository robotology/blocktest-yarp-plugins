/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionReset.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#include "actionReset.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "ClockServer.h"

#include "logger.h"
#include "report.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionReset,yarpactions::yarpreset);

namespace YarpActions
{

ActionReset::ActionReset(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{}     

void ActionReset::beforeExecute()
{
}

execution ActionReset::execute(const TestRepetitions& testrepetition)
{
    GazeboYarpPlugins::ClockServer clockServer;
    yarp::os::Port clockClientPort;

    std::string localRpcPort =  "/resetxxx";
    std::string remoteRpcPort = "/clock/rpc";
    bool ok=clockClientPort.open(localRpcPort);
    if(ok)
    {
        ok &=yarp::os::Network::exists(remoteRpcPort.c_str());
        ok &=yarp::os::Network::connect(localRpcPort.c_str(), remoteRpcPort.c_str());
        if(!ok)
        {
            addProblem(testrepetition,Severity::critical,"Unable to open clock/rpc",true);
        }
        clockServer.yarp().attachAsClient(clockClientPort);
    }

    clockServer.resetSimulation();
    yarp::os::SystemClock systemClock;
    systemClock.delay(1.0);
    clockClientPort.close();
    return BlockTestCore::execution::continueexecution;;
}

}