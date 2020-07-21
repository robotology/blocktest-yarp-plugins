/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionPolydriverOpener.cpp
  * @author Andrea Ruzzenenti <andrea.ruzzenenti@iit.it>, Luca Tricerri
  */

#include "actionYarp.h"
#include "yarpActionDepotStart.h"
#include "actionPolydriverOpener.h"

#include <yarp/dev/PolyDriver.h>
#include <memory>

using namespace yarp::dev;
using namespace yarp::os;

ACTIONREGISTER_DEF_TYPE(YarpAction::ActionPolydriverOpener, yarpactions::yarpopenpolydriver);

namespace YarpAction
{
ActionPolydriverOpener::ActionPolydriverOpener(const CommandAttributes& parameters, const std::string& testCode) : ActionYarp(parameters, testCode)
{  
    std::string tag = parameters.at(yarpsyntax::polydrivertag);
    Property property;
    property.fromString( parameters.at(yarpsyntax::property));

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
}