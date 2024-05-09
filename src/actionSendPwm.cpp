/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

#include "actionSendPwm.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "yarpActionDepotStart.h"

#include "logger.h"
#include "report.h"

#include <cmath>

using namespace yarp::sig;
using namespace yarp::dev;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionSendPwm,yarpactions::yarpsendpwm);

namespace YarpActions
{

ActionSendPwm::ActionSendPwm(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
}     

void ActionSendPwm::beforeExecute()
{
    getCommandAttribute("profile",profile_);
    getCommandAttribute("dutycycle",dutycycle_);
    getCommandAttribute("time",time_);
    getCommandAttribute("jointname",jointname_);
    getCommandAttribute("frequency",frequency_);
    getCommandAttribute("wrappername",wrapperPrefix_);    
}

BlockTestCore::execution ActionSendPwm::execute(const TestRepetitions& testrepetition)
{
    if(!profile_.empty())
    {
        TXLOG(Severity::debug)<<"Using profile:"<<profile_<<std::endl;
    }

    if(YarpActionDepotStart::polyDriverDepot_.find(wrapperPrefix_)==YarpActionDepotStart::polyDriverDepot_.end())
    {
        addProblem(testrepetition,Severity::error,"Unable to find Polydrive:"+wrapperPrefix_,true);
        return BlockTestCore::execution::stopexecution;
    }

    yarp::dev::IPWMControl *ipwm=nullptr;
    yarp::dev::IControlMode *icmd=nullptr;

    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(ipwm))
    {
        addProblem(testrepetition,Severity::critical,"Unable to open pwm mode interface",true);
    }

    if(!YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_]->view(icmd))
    {
        addProblem(testrepetition,Severity::critical,"Unable to open control mode interface",true);
    }    

    std::map<std::string,int> jointNames;
    getJointNames(*YarpActionDepotStart::polyDriverDepot_[wrapperPrefix_],jointNames);
    auto it=jointNames.find(jointname_);
    if(it==jointNames.end())
    {
        TXLOG(Severity::error)<<"Error joint not found:"<<jointname_<<std::endl;
        addProblem(testrepetition,Severity::critical,"Error joint not found",false);
        return  BlockTestCore::execution::stopexecution;
    }

    icmd->setControlMode(it->second, VOCAB_CM_PWM);
    if(dutycycle_>securityLimits_)
    {
        dutycycle_=securityLimits_;
        TXLOG(Severity::error)<<"Pwm to hight:"<<dutycycle_<<std::endl;
    }
    if(dutycycle_<-securityLimits_)
    {
        dutycycle_=-securityLimits_;
        TXLOG(Severity::error)<<"Pwm to low:"<<dutycycle_<<std::endl;
    }

    if(profile_=="const")
    {
        ipwm->setRefDutyCycle(it->second, dutycycle_);
        yarp::os::Time::delay(time_);
    }
    else if(profile_=="sin")
    {
        const double frequency=frequency_;//Hz
        const double pi=3.14;

        TXLOG(Severity::debug)<<"Pwm sin frequency:"<<frequency_<<std::endl;

        double msec=0;
        while(msec<time_*1000)
        {
            double sec=msec/(double)1000;
                       
            double value=sin(pi*2*frequency*sec)*dutycycle_;
            ipwm->setRefDutyCycle(it->second,value );
            //TXLOG(Severity::debug)<<"Pwm sin value:"<<value<<std::endl;
            msec=msec+10;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    else if(profile_=="stepwave")
    {
        const double frequency=frequency_;//Hz
        const double pi=3.14;

        TXLOG(Severity::debug)<<"Pwm step frequency:"<<frequency_<<std::endl;

        double msec=0;
        while(msec<time_*1000)
        {
            double sec=msec/(double)1000;
                       
            double value=sign(sin(pi*2*frequency*sec)*dutycycle_);
            ipwm->setRefDutyCycle(it->second,value );
            //TXLOG(Severity::debug)<<"Pwm sin value:"<<value<<std::endl;
            msec=msec+10;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }    

    ipwm->setRefDutyCycle(it->second, 0);
    yarp::os::Time::delay(time_);
    return BlockTestCore::execution::continueexecution;
}

int ActionSendPwm::sign(double value)
{
    if (value > 0) return 1;
    if (value < 0) return -1;
    return 0;
}

}
