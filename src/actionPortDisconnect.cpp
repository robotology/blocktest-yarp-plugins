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

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortDisconnect, yarpactions::yarpdisconnect);

ActionPortDisconnect::ActionPortDisconnect(const CommandAttributes& commandAttributes, const std::string& testCode) : ActionYarp(commandAttributes, testCode)
{
}

void ActionPortDisconnect::beforeExecute()
{
	getCommandAttribute( "source",      src_);
	getCommandAttribute("destination", dst_);	
}

execution ActionPortDisconnect::execute(const TestRepetitions& testrepetition)
{
	auto ok{ true };
	ok &= Network::disconnect(src_, dst_);
	if(!ok)
	{
		stringstream logStream;
		logStream << "Unable to disconnect " << src_ << " -> " << dst_ ;
		addProblem(testrepetition, Severity::critical, logStream.str(),true);
	}
	return BlockTestCore::execution::continueexecution;
}
