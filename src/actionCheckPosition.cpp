/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionCheckPosition.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionCheckPosition.h"
#include "logger.h"
#include "report.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCheckPosition,yarpactions::checkposition);

namespace YarpActions
{

ActionCheckPosition::ActionCheckPosition(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{          
}     

void ActionCheckPosition::beforeExecute()
{
    getCommandAttribute("xminposition",xminposition_);
    getCommandAttribute("yminposition",yminposition_);
    getCommandAttribute("zminposition",zminposition_);     
}


execution ActionCheckPosition::execute(const TestRepetitions& testrepetition)
{
    yarp::os::Port fbePort;
    std::string localfbePort  = "/myrobot/odometry:i";
    std::string remotefbePort = "/icubFloatingBaseEstimator/floating_base/state:o";
    bool ok=fbePort.open(localfbePort);
    if(!ok)
    {
        addProblem(testrepetition,Severity::critical,"Unable to open ports checkposition",true);
    }
    ok=yarp::os::Network::connect(remotefbePort.c_str(), localfbePort.c_str());
    if(!ok)
    {
        addProblem(testrepetition,Severity::critical,"Unable to connect to fbe port",true);
    }
    yarp::os::Bottle fbeReadings;
    fbePort.read(fbeReadings);
    yarp::os::Bottle *coordList = fbeReadings.get(0).asList();

    if(coordList->size()<6)
    {
        TXLOG(Severity::critical)<<"FBE readings should have 6 elements current:"<<fbeReadings.size()<<std::endl;
        addProblem(testrepetition,Severity::critical,"FBE readings should have 6 elements",false);
        fbePort.interrupt();
        fbePort.close();  
        return execution::stopexecution;;
    }   

    TXLOG(Severity::debug)<<"FBE x:"<<coordList->get(0).asDouble()<<" y:"<<coordList->get(1).asDouble()<<" z:"<<coordList->get(2).asDouble()<<std::endl;
    
    execution error=execution::stopexecution;;
    if(xminposition_&& std::abs(xminposition_)>std::abs(coordList->get(0).asDouble()))
    {
        TXLOG(Severity::error)<<"FBE x not enough:"<<coordList->get(0).asDouble()<<" desidered at least:"<<xminposition_<<std::endl;
        error=execution::continueexecution;;
    }
    if(yminposition_ &&  std::abs(yminposition_)>std::abs(coordList->get(1).asDouble()))
    {
        TXLOG(Severity::error)<<"FBE y not enough:"<<coordList->get(1).asDouble()<<" desidered at least:"<<yminposition_<<std::endl;
        error=execution::continueexecution;;        
    }
    if(zminposition_ &&  std::abs(zminposition_)>std::abs(coordList->get(2).asDouble()))
    {
        TXLOG(Severity::error)<<"FBE z not enough:"<<coordList->get(2).asDouble()<<" desidered at least:"<<zminposition_<<std::endl;
        error=execution::continueexecution;;        
    }

    if(error==execution::stopexecution)
        addProblem(testrepetition,Severity::error,"FBE not enough",true);
    
    fbePort.interrupt();
    fbePort.close();  
    return execution::continueexecution;;
}

}