/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionPolydriverClose.cpp
  * @author Andrea Ruzzenenti <andrea.ruzzenenti@iit.it>, Luca Tricerri
  */

#include "actionYarp.h"
#include "yarpActionDepotStart.h"
#include "actionPolydriverClose.h"

#include <yarp/dev/PolyDriver.h>
#include <memory>

using namespace yarp::dev;
using namespace yarp::os;

ACTIONREGISTER_DEF_TYPE(YarpAction::ActionPolydriverClose, yarpactions::yarpclosepolydriver);

namespace YarpAction
{

ActionPolydriverClose::ActionPolydriverClose(const CommandAttributes& parameters, const std::string& testCode) : ActionYarp(parameters, testCode)
{  
    tag_ = parameters.at(yarpsyntax::wrappername);
};

BlockTestCore::execution ActionPolydriverClose::execute(const TestRepetitions&)
{

    auto it=YarpActionDepotStart::polyDriverDepot_.find(tag_);
    if(it==YarpActionDepotStart::polyDriverDepot_.end())
    {
        TXLOG(Severity::info)<<"Close PolyDrive tag:"<<tag_<<std::endl;
        TestRepetitions rep{0,0};
        addProblem(rep, Severity::critical, "Polydriver failed to close tag:"+tag_,true);
        return BlockTestCore::execution::continueexecution;
    }
    
    it->second->close();
    YarpActionDepotStart::polyDriverDepot_.erase(it);
    TXLOG(Severity::info)<<"Close PolyDrive tag:"<<tag_<<std::endl;
    return BlockTestCore::execution::continueexecution;
}


}