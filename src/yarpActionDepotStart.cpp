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

#include "general.h"
#include "logger.h"
#include "action.h"

#include "yarpActionDepotStart.h"
#include <yarp/os/Network.h>

ACTIONDEPOTSTART(YarpActionDepotStart)

std::string YarpActionDepotStart::robotName_{""};
std::map<std::string,PolyDriver_sptr> YarpActionDepotStart::polyDriverDepot_;
std::map<std::string,Port_sptr> YarpActionDepotStart::portDepot_;

YarpActionDepotStart::YarpActionDepotStart()
{
    yarp::os::Network::init();
    TXLOG(Severity::info)<<"Library setup"<<std::endl;
}     

void YarpActionDepotStart::configure(const std::map<std::string,std::string>& conf)
{
    TXLOG(Severity::info)<<"Library config called:"<<std::endl;

    bool useNetClock;
    getLibraryAttribute(conf,"netclock",useNetClock);
    getLibraryAttribute(conf,"robotname",robotName_);
    std::string wrapperNames;
    getLibraryAttribute(conf,"wrappername",wrapperNames);

    if(useNetClock)
    {
        useNetClock_=true;
        TXLOG(Severity::info)<<"Use netclock"<<std::endl;
        yarp::os::Time::useNetworkClock("/clock");
    }
    else
    {
        TXLOG(Severity::info)<<"Use systemclock"<<std::endl;
        yarp::os::Time::useSystemClock(); 
    }
    yarp::os::yarpClockType clockType=yarp::os::Time::getClockType();
    TXLOG(Severity::info)<<"Really using clock type:"<<yarp::os::Time::clockTypeToString(clockType)<<std::endl;

    std::vector<std::string> out;
    Action::tokenize<std::string>(wrapperNames,out);
    for(const std::string& current:out)
    {
        yarp::os::Property options;
        options.put("device", "remote_controlboard");
        options.put("local",current+"xx");
        std::string wrapperPort="/"+ robotName_+current;
        options.put("remote", wrapperPort);
        PolyDriver_sptr toAdd=std::make_shared<yarp::dev::PolyDriver>();
        if(!toAdd->open(options))
        {
            TXLOG(Severity::error)<<"Unable to open PolyDrive for wrapper name:"<<wrapperPort<<std::endl;
            continue;  
        }
        else
        {                
            TXLOG(Severity::info)<<"Opened PolyDrive for wrapper name:"<<wrapperPort<<" Polydrive name:"<<current<<std::endl;
        }

        polyDriverDepot_[current]=toAdd;
    }    
}

void YarpActionDepotStart::stop()
{
    TXLOG(Severity::info)<<"Library stop called:"<<std::endl;

    // Close all polydrivers
    for(auto& current:polyDriverDepot_)
    {
        current.second->close();
    }
    // Close all ports
    for(auto& current:portDepot_)
    {
        current.second->close();
    }
    polyDriverDepot_.clear();
}

YarpActionDepotStart::~YarpActionDepotStart()
{
    std::cout<<"Before yarp::os::Network::fini"<<std::endl;
    //yarp::os::Network::fini();
    std::cout<<"After yarp::os::Network::fini"<<std::endl;
}
    