/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionApplyForce.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionApplyForce.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include "logger.h"
#include "report.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionApplyForce,yarpactions::applyforce);

namespace YarpActions
{
ActionApplyForce::ActionApplyForce(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
}     

void ActionApplyForce::beforeExecute()
{
    getCommandAttribute("force",force_);    
}

execution ActionApplyForce::execute(const TestRepetitions& testrepetition)
{
    std::string localExtWrenchPort = "/myPortForExternalWrench:o";
    std::string remoteExtWrenchPort = "/icab/applyExternalWrench/rpc:i";
    yarp::os::RpcClient extWrenchPort;
    bool ok=extWrenchPort.open(localExtWrenchPort);
   if(!ok)
    {
        addProblem(testrepetition,Severity::critical,"Unable to open ports applyforce",true);
        return execution::stopexecution;
    }

    yarp::os::Network::connect(localExtWrenchPort,remoteExtWrenchPort);

    std::istringstream iss(force_);
    std::vector<std::string> tokenized(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());

    if(tokenized.size()!=8)
    {
        addProblem(testrepetition,Severity::error,"Error in parameter number for applyForce",true);
        return execution::stopexecution;
    }

    yarp::os::Bottle cmd;
    cmd.addString(tokenized[0]);
    cmd.addFloat64(std::atof(tokenized[1].c_str()));
    cmd.addFloat64(std::atof(tokenized[2].c_str()));
    cmd.addFloat64(std::atof(tokenized[3].c_str()));
    cmd.addFloat64(std::atof(tokenized[4].c_str()));
    cmd.addFloat64(std::atof(tokenized[5].c_str()));
    cmd.addFloat64(std::atof(tokenized[6].c_str()));
    cmd.addFloat64(std::atof(tokenized[7].c_str()));

    yarp::os::Bottle response;
    extWrenchPort.write(cmd,response);
  
    if(response.toString().empty())
    {
          addProblem(testrepetition,Severity::critical,"No response from ExternalWrench plugin",true);
    }
      
    extWrenchPort.interrupt();
    extWrenchPort.close();    
    return execution::continueexecution;
}
}