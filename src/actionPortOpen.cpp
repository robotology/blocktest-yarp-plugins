/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionPortDisconnect.cpp
  * @author Luca Tricerri <luca.tricerri@iit.it>
  *         Nicolo' Genesio <nicolo.genesio@iit.it>
  */

#include <actionPortOpen.h>
#include <yarpActionDepotStart.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortOpen, "yarpportopen");

ActionPortOpen::ActionPortOpen(const CommandAttributes& commandAttributes,
                               const std::string& testCode) : ActionPortClose(commandAttributes, testCode)
{}

execution ActionPortOpen::execute(unsigned int testrepetition)
{
    auto port_ptr = std::make_shared<Port>();
    bool opened_ = port_ptr->open(name_);

    if (opened_)
        YarpActionDepotStart::portDepot_[name_] = port_ptr;
    else
    {
        stringstream logStream;
        logStream << "Unable to open " << name_;
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
    }
    return execution::continueexecution;
}
