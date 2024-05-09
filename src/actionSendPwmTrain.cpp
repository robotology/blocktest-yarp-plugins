/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionSendPwmTrain.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionSendPwmTrain.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "yarpActionDepotStart.h"
#include "logger.h"
#include "report.h"


using namespace yarp::sig;
using namespace yarp::dev;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionSendPwmTrain,yarpactions::yarpsendpwmtrain);

namespace YarpActions
{

ActionSendPwmTrain::ActionSendPwmTrain(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{   
}     

void ActionSendPwmTrain::beforeExecute()
{
    getCommandAttribute("cycletime",cycleTime_);
    getCommandAttribute("cyclesleep",cycleSleep_);
    getCommandAttribute("maxposition",maxAngle_);
    getCommandAttribute("minposition",minAngle_);
    getCommandAttribute("dutycycle",dutycycle_);
    getCommandAttribute("jointname",jointname_);
    getCommandAttribute("direction",direction_);    
    getCommandAttribute("wrappername",wrapperPrefix_);        
}

BlockTestCore::execution ActionSendPwmTrain::execute(const TestRepetitions& testrepetition)
{

    yarp::dev::IPWMControl *ipwm=nullptr;
    yarp::dev::IControlMode *icmd=nullptr;
    yarp::dev::IEncoders *iencs=nullptr;
    int nj=0;

    if(YarpActionDepotStart::polyDriverDepot_.find(wrapperPrefix_)==YarpActionDepotStart::polyDriverDepot_.end())
    {
        addProblem(testrepetition,Severity::error,"Unable to find Polydrive:"+wrapperPrefix_,true);
        return BlockTestCore::execution::stopexecution;
    }

    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(ipwm))
    {
        addProblem(testrepetition,Severity::critical,"Unable to open pwm mode interface",true);
    }

    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(icmd))
    {
        addProblem(testrepetition,Severity::critical,"Unable to open control mode interface",true);
    }    

    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(iencs))
    {
        addProblem(testrepetition,Severity::error,"Unable to view IEncoder interface",true);
        return BlockTestCore::execution::stopexecution;;
    }

    if(!iencs->getAxes(&nj))
    {
        addProblem(testrepetition,Severity::error,"getAxes failed",true);
        return BlockTestCore::execution::stopexecution;;
    }    

    std::map<std::string,int> jointNames;
    getJointNames(*YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_],jointNames);
    auto it=jointNames.find(jointname_);
    if(it==jointNames.end())
    {
        TXLOG(Severity::error)<<"Error joint not found:"<<jointname_<<std::endl;
        addProblem(testrepetition,Severity::critical,"Error joint not found",false);
        return BlockTestCore::execution::stopexecution;;
    }
    

    int jointPos=jointNames[jointname_];
    icmd->setControlMode(it->second, VOCAB_CM_PWM);   
    ipwm->setRefDutyCycle(it->second, dutycycle_);
    double currentDutyCycle=dutycycle_;

    for(unsigned int index=0;index<cycleTime_;++index)
    {
        double pos=getPosition(jointPos,iencs,nj);
        
        if(direction_==1)
        {
            while( (pos<maxAngle_ && pos>minAngle_) || (pos>maxAngle_ && currentDutyCycle<0) || (pos<minAngle_ && currentDutyCycle>0) )
            {
                pos=getPosition(jointPos,iencs,nj);
                //TXLOG(Severity::debug)<<pos<<","<<currentDutyCycle<<std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(cycleSleep_));
            }
        }
        else
        {
            while( (pos<maxAngle_ && pos>minAngle_) || (pos>maxAngle_ && currentDutyCycle>0) || (pos<minAngle_ && currentDutyCycle<0) )
            {
                pos=getPosition(jointPos,iencs,nj);
                //TXLOG(Severity::debug)<<pos<<","<<currentDutyCycle<<std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(cycleSleep_));
            }
        }
        currentDutyCycle=-1*currentDutyCycle;
        ipwm->setRefDutyCycle(it->second, currentDutyCycle);
        //TXLOG(Severity::debug)<<"New duty to be set:"<<currentDutyCycle<<"pos:"<<pos<<std::endl;
    }

    ipwm->setRefDutyCycle(it->second, 0);
    return BlockTestCore::execution::continueexecution;;
}


double ActionSendPwmTrain::getPosition(int jointNumber,yarp::dev::IEncoders* iencs,int& nj)
{
    std::vector<double> position(nj, 0.0);
    iencs->getEncoders(position.data());

    return position[jointNumber];   
}

}