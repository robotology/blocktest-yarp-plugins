/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionCheckJointPosition.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionCheckJointPosition.h"
#include "logger.h"
#include "report.h"
#include "yarpActionDepotStart.h"

#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>


ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCheckJointPosition,yarpactions::yarpcheckjointposition);


namespace YarpActions
{

ActionCheckJointPosition::ActionCheckJointPosition(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
}     

void ActionCheckJointPosition::beforeExecute()
{
    getCommandAttribute("wrappername",wrapperPrefix_);
    getCommandAttribute("jointname",jointname_);
    getCommandAttribute("expectedvalue",expectedValue_);
    getCommandAttribute("tolerance",tolerance_);    
}

execution ActionCheckJointPosition::execute(const TestRepetitions& testrepetition)
{
    yarp::dev::IEncoders *iencoders=nullptr;
    
    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(iencoders))
    {
        addProblem(testrepetition,Severity::error,"Unable to open encoder control mode interface 2",true);        
        return BlockTestCore::execution::stopexecution;
    }

    int nj{0};
    if(!iencoders->getAxes(&nj))
    {
        addProblem(testrepetition,Severity::error,"Unable to open encoder control mode interface 3",true);
        return BlockTestCore::execution::stopexecution;;    
    }       
         
    std::map<std::string, int> jointNames;
    getJointNames(*YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_],jointNames);         

    auto it=jointNames.find(jointname_);
    if(it==jointNames.end())
    {
        TXLOG(Severity::error)<<"Joint not found:"<<jointname_<<std::endl;   
        addProblem(testrepetition,Severity::error,"Joint not found:",false);
        return BlockTestCore::execution::stopexecution;;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    std::vector<double> positions(nj,0.0);
    while(!iencoders->getEncoders(positions.data()))
    {
        TXLOG(Severity::debug)<<"Unable to open encoder control mode interface 4:"<<positions[5]<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));    
    }
    
    double ref=positions[it->second];
    if(expectedValue_>ref+tolerance_ || expectedValue_<ref-tolerance_)
    {
        TXLOG(Severity::error)<<"Joint position check value:"<<ref<<" expected:" <<expectedValue_<<" tolerance:"<<tolerance_ <<" name:"<<jointname_<<std::endl;   
        addProblem(testrepetition,Severity::error,"Joint position check value",false);
    }
    else
    {
        TXLOG(Severity::debug)<<"Joint position check value ok:"<<ref<<" expected:" <<expectedValue_<<" tolerance:"<<tolerance_ <<" name:"<<jointname_<<std::endl;   
    }
    return BlockTestCore::execution::continueexecution;;
}

}