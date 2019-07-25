/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file yarpActionDepotStart.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionDepotStart.h"

#include <yarp/dev/PolyDriver.h>

using PolyDriver_sptr=std::shared_ptr<yarp::dev::PolyDriver>;
using Port_sptr = std::shared_ptr<yarp::os::Port>;

using namespace BlockTestCore;

/**
 * @class YarpActionDepotStart
 * @brief ...
 * @todo missing brief and detailed description
 */
class YarpActionDepotStart :public ActionDepotStart
{
    public:
        YarpActionDepotStart(); 
        ~YarpActionDepotStart() override;

        void configure(const std::map<std::string,std::string>&) override;
        void stop() override;

        static std::map<std::string,PolyDriver_sptr> polyDriverDepot_;//PolyDrive collection for each wrappers
        static std::map<std::string,Port_sptr> portDepot_;
        static std::string robotName_;
        bool useNetClock_{false};
};
