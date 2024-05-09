/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionCheckRobot.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionCheckRobot.h"
#include "logger.h"
#include "report.h"
#include "yarpActionDepotStart.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCheckRobot,yarpactions::checkrobot);

namespace YarpActions
{

ActionCheckRobot::ActionCheckRobot(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
     
}     

void ActionCheckRobot::beforeExecute()
{
    getCommandAttribute("wrappername",wrapperPrefix_);  
}

execution ActionCheckRobot::execute(const TestRepetitions& testrepetition)
{
    yarp::dev::IEncoders       *iencs;
    int nj;

    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(iencs))
    {
        addProblem(testrepetition,Severity::critical,"Unable to view IEncoder interface",true);
    }
    if(!iencs->getAxes(&nj))
    {
        addProblem(testrepetition,Severity::critical,"getAxes failed",true);
    }        
    return BlockTestCore::execution::continueexecution;;
}

}