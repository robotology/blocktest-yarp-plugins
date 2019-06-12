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

#include <actionPortConnect.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortConnect, "yarpconnect");

ActionPortConnect::ActionPortConnect(const CommandAttributes& commandAttributes, const std::string& testCode) : ActionPortDisconnect(commandAttributes, testCode)
{
	getCommandAttribute(commandAttributes, "carrier", crr_);
}

execution ActionPortConnect::execute(unsigned int testrepetition)
{
	auto ok{ true };
	ok &= Network::connect(src_, dst_, crr_);
	if(!ok)
	{
		stringstream logStream;
		logStream << "Unable to connect " << src_ << " -> " << dst_ << " with "<<crr_<<" carrier";
		TXLOG(Severity::error) << logStream.str() << std::endl;
		addProblem(testrepetition, Severity::critical, logStream.str());
	}
	return execution::continueexecution;
}
