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

#include <actionPortClose.h>
#include <yarpActionDepotStart.h>

#include <yarp/os/Time.h>

#include <sstream>
#include <type.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortClose, "yarpportclose");

ActionPortClose::ActionPortClose(const CommandAttributes& commandAttributes,
                                 const std::string& testCode) : ActionYarp(commandAttributes, testCode)
{
}

void ActionPortClose::beforeExecute()
{
	getCommandAttribute("portname",   portname_);    
}

execution ActionPortClose::execute(const TestRepetitions& testrepetition)
{
    auto exists {true};
    stringstream logStream;

    auto portIt = YarpActionDepotStart::portDepot_.find(portname_);

    if (portIt == YarpActionDepotStart::portDepot_.end())
    {
        logStream << "Unable to find " << portname_<<" in the port depot";
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
        return execution::continueexecution;
    }
    auto port_ptr = portIt->second;

    port_ptr->close();

    YarpActionDepotStart::portDepot_.erase(portname_);

    yarp::os::Time::delay(0.2);

    exists &= Network::exists(portname_);

    if (exists)
    {
        logStream << "Unable to close " << portname_;
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
    }

	return execution::continueexecution;
}
