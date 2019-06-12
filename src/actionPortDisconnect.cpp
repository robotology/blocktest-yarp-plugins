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

#include <actionPortDisconnect.h>
#include <sstream>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortDisconnect, "yarpdisconnect");

ActionPortDisconnect::ActionPortDisconnect(const CommandAttributes& commandAttributes, const std::string& testCode) : ActionYarp(commandAttributes, testCode)
{
	getCommandAttribute(commandAttributes, "source",      src_);
	getCommandAttribute(commandAttributes, "destination", dst_);
}

execution ActionPortDisconnect::execute(unsigned int testrepetition)
{
	auto ok{ true };
	ok &= Network::disconnect(src_, dst_);
	if(!ok)
	{
		stringstream logStream;
		logStream << "Unable to disconnect " << src_ << " -> " << dst_ ;
		TXLOG(Severity::error) << logStream.str() << std::endl;
		addProblem(testrepetition, Severity::critical, logStream.str());
	}
	return execution::continueexecution;
}
