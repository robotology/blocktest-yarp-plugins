/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionSendDirectPosition.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionSendDirectPosition.h"

#include "yarpActionDepotStart.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "logger.h"
#include "report.h"

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionSendDirectPosition,"yarpsenddirectpos");

namespace YarpActions
{

ActionSendDirectPosition::ActionSendDirectPosition(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
}     

void ActionSendDirectPosition::beforeExecute()
{
    std::string degreeStr;
    getCommandAttribute("degree",degreeStr);
    std::string jointnameStr;
    getCommandAttribute("jointname",jointnameStr);
    
    Action::tokenize<double>(degreeStr,degree_);
    Action::tokenize<std::string>(jointnameStr,jointToMove_);

    getCommandAttribute("wrappername",wrapperPrefix_);
}

execution ActionSendDirectPosition::execute(const TestRepetitions& testrepetition)
{
    //TO REMOVE

    std::ofstream out;
    out.open("log/targetdirect.log", std::fstream::in | std::fstream::out | std::fstream::app);

    if(degree_.empty()) {
        addProblem(testrepetition,Severity::error,"Missing degree information",true);
        return execution::stopexecution;
    }


    out<<ClockFacility::instance().now()<<","<<0<<std::endl;
    out<<ClockFacility::instance().now()<<","<<degree_[0]<<std::endl; 
    //TO REMOVE

    if(degree_.size()!=jointToMove_.size())
    {
        addProblem(testrepetition,Severity::error,"Joint info not cooerent",true);
        return execution::stopexecution;
    }

    yarp::dev::IPositionDirect *ipos=nullptr;
    yarp::dev::IControlMode *icmd=nullptr;
  
    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(ipos))
    {
        addProblem(testrepetition,Severity::error,"Unable to open pos mode interface",true);
        return execution::stopexecution;
    }

    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(icmd))
    {
        addProblem(testrepetition,Severity::error,"Unable to open control mode interface",true);      
        return execution::stopexecution;
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
            addProblem(testrepetition,Severity::critical,"Error joint not found",false);
            return execution::stopexecution;
        }
        
        desiredJoint.push_back(it->second);
        double currentDegree=0;
        currentDegree=degree_[index];
        if (std::isnan(currentDegree))
        {
            TXLOG(Severity::error)<<"Empty number from table"<<std::endl;
            return execution::continueexecution;
        }

        desiredJointPosInDegrees.push_back(currentDegree);
        static bool flag{true};
        if(flag)
        {
            icmd->setControlMode(it->second, VOCAB_CM_POSITION_DIRECT);
            flag=false;
        }
    }

    ipos->setPositions(jointToMove_.size(),desiredJoint.data(),desiredJointPosInDegrees.data());
    //TXLOG(Severity::debug)<<"---------:"<<desiredJointPosInDegrees[0]<<std::endl;

    return execution::continueexecution;
}

}
