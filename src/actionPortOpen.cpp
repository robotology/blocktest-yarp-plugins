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

void ActionPortOpen::beforeExecute()
{
    ActionPortClose::beforeExecute();
}

execution ActionPortOpen::execute(const TestRepetitions& testrepetition)
{
    auto port = std::make_shared<Port>();
    bool opened_ = port->open(portname_);

    if (opened_)
        YarpActionDepotStart::portDepot_[portname_] = port;
    else
    {
        stringstream logStream;
        logStream << "Unable to open " << portname_;
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
    }

    return execution::continueexecution;
}
