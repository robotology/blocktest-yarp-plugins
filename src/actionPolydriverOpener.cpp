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
#include "syntax.h"
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
    tag_ = parameters.at(yarpsyntax::wrappername);
    property_.fromString( parameters.at(yarpsyntax::property));
};

BlockTestCore::execution ActionPolydriverOpener::execute(const TestRepetitions&)
{
    auto pdr = std::make_shared<PolyDriver>();
    bool opened = pdr->open(property_);
    if (opened)
    {
        YarpActionDepotStart::polyDriverDepot_[tag_] = pdr;
        TXLOG(Severity::info)<<"Open PolyDrive tag:"<<tag_<<std::endl;
    }
    else
    {
        TestRepetitions rep{0,0};
        addProblem(rep, Severity::critical, "Polydriver failed to open tag:"+tag_,true);
    }
    return BlockTestCore::execution::continueexecution;
}


}