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
#include <yarpActionDepotStart.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortConnect, "yarpconnect");

ActionPortConnect::ActionPortConnect(const CommandAttributes& commandAttributes, const std::string& testCode) : ActionPortDisconnect(commandAttributes, testCode)
{
}

void ActionPortConnect::beforeExecute()
{
	ActionPortDisconnect::beforeExecute();
	getCommandAttribute("carrier", crr_);	
}

execution ActionPortConnect::execute(const TestRepetitions& testrepetition)
{
	bool ok{ true };
	ok=Network::exists(src_);
	if(!ok)
	{
		stringstream logStream;
		logStream << "Port not exists " << src_;
		addProblem(testrepetition, Severity::error, logStream.str(),true);
		return execution::continueexecution;
	}	
	ok=Network::exists(dst_);
	if(!ok)
	{
		stringstream logStream;
		logStream << "Port not exists " << dst_;
		addProblem(testrepetition, Severity::error, logStream.str(),true);
		return execution::continueexecution;
	}
	
	ok=Network::isValidPortName(src_);
	ok&=Network::isValidPortName(dst_);
	if(!ok)
	{
		stringstream logStream;
		logStream << "Port not valid " << src_ << " -> " << dst_ << " with "<<crr_<<" carrier";
		addProblem(testrepetition, Severity::error, logStream.str(),true);
		return execution::continueexecution;
	}

	ok &= Network::connect(src_, dst_, crr_);
	if(!ok)
	{
		stringstream logStream;
		logStream << "Unable to connect " << src_ << " -> " << dst_ << " with "<<crr_<<" carrier";
		addProblem(testrepetition, Severity::error, logStream.str(),true);
	}
	return execution::continueexecution;
}
