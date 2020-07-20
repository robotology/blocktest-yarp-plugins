/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCheckJointPosition.h
  * @author Andrea Ruzzenenti <andrea.ruzzenenti@iit.it>, Luca Tricerri
  */

#include "actionYarp.h"
#include "yarpActionDepotStart.h"
#include "actionPolydriverOpener.h"
#include <yarp/dev/PolyDriver.h>
#include <memory>

using namespace YarpActions;
using namespace yarp::dev;
using namespace yarp::os;
namespace YarpAction
{
    ActionPolydriverOpener::ActionPolydriverOpener(const CommandAttributes& parameters, const std::string& testCode) : ActionYarp(parameters, testCode)
    {
        Property    property;
        std::string tag;
        std::string device;

        tag = parameters.at("polydrivertag");
        device = parameters.at("device");

        property.put("device", device);       
        auto pdr = std::make_shared<PolyDriver>();
        bool opened = pdr->open(property);
        if (opened)
            YarpActionDepotStart::polyDriverDepot_[tag] = pdr;
        else
        {
            TestRepetitions rep{0,0};
            addProblem(rep, Severity::critical, "Polydriver failed to open",true);
        }
    };
    ACTIONREGISTER_DEF_TYPE(ActionPolydriverOpener, "yarpopenpolydrive");
}