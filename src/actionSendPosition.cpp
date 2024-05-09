/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionSendPosition.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionSendPosition.h"

#include "logger.h"
#include "report.h"
#include "yarpActionDepotStart.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionSendPosition,yarpactions::yarpsendpos);

namespace YarpActions
{

ActionSendPosition::ActionSendPosition(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{    
}     

void ActionSendPosition::beforeExecute()
{
    std::string degreeStr;
    getCommandAttribute("degree",degreeStr);

    std::string velocityStr;
    getCommandAttribute("velocity",velocityStr);      

    std::string jointnameStr;
    getCommandAttribute("jointname",jointnameStr);          
    
    Action::tokenize<double>(degreeStr,degree_);
    Action::tokenize<int>(velocityStr,velocity_);
    Action::tokenize<std::string>(jointnameStr,jointToMove_);

    getCommandAttribute("wrappername",wrapperPrefix_);    
}

execution ActionSendPosition::execute(const TestRepetitions& testrepetition)
{
    //TO REMOVE
    std::ofstream out;
    out.open("log/target.log", std::fstream::in | std::fstream::out | std::fstream::app);

    if(degree_[0])
        out<<ClockFacility::instance().now()<<","<<0<<std::endl; 
    out<<ClockFacility::instance().now()<<","<<degree_[0]<<std::endl; 
    //TO REMOVE

    if(degree_.size()!=velocity_.size())
    {
        addProblem(testrepetition,Severity::error,"Joint info not cooerent",true);
        return BlockTestCore::execution::stopexecution;;      
    }

    if(degree_.size()!=jointToMove_.size())
    {
        addProblem(testrepetition,Severity::error,"Joint info not cooerent",true);
        return BlockTestCore::execution::stopexecution;;      
    }

    yarp::dev::IPositionControl *ipos{nullptr};
    yarp::dev::IControlMode *icmd{nullptr};
   
    if(YarpActionDepotStart::polyDriverDepot_.find(wrapperPrefix_)==YarpActionDepotStart::polyDriverDepot_.end())
    {
        addProblem(testrepetition,Severity::error,"Unable to find Polydrive:"+wrapperPrefix_,true);
        return BlockTestCore::execution::stopexecution;
    }

    bool ok=YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(ipos);
    if(!ok)
    {
        addProblem(testrepetition,Severity::error,"Unable to open pos mode interface",true);
        return BlockTestCore::execution::stopexecution;;
    }
    ok=YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(icmd);
    if(!ok)
    {
        addProblem(testrepetition,Severity::error,"Unable to open control mode interface",true);
        return BlockTestCore::execution::stopexecution;;
    }
 
    std::map<std::string,int> jointNames;
    getJointNames(*YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_],jointNames);

    std::vector<int> desiredJoint;
    std::vector<double> desiredJointPosInDegrees;   
    for(unsigned int index=0;index<jointToMove_.size();++index)
    {
        auto it=jointNames.find(jointToMove_[index]);
        if(it==jointNames.end())
        {
            TXLOG(Severity::error)<<"Error joint not found:"<<jointToMove_[index]<<std::endl;
            addProblem(testrepetition,Severity::error,"Error joint not found",false);
            return BlockTestCore::execution::stopexecution;;
        }
        desiredJoint.push_back(it->second);
        desiredJointPosInDegrees.push_back(degree_[index]);
        icmd->setControlMode(it->second, VOCAB_CM_POSITION);
        ipos->setRefSpeed (it->second, velocity_[index]);
    }

    ipos->positionMove(jointToMove_.size(),desiredJoint.data(),desiredJointPosInDegrees.data());
    return BlockTestCore::execution::continueexecution;;
}

}

