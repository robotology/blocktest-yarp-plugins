/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionPortRead.cpp
  * @author Luca Tricerri <luca.tricerri@iit.it>
  */

#include <actionPortRead.h>
#include <yarpActionDepotStart.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortRead, "yarpportread");

ActionPortRead::ActionPortRead(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionPortRead::beforeExecute()
{
    getCommandAttribute("portname",   portname_);   
    getCommandAttribute("value",   value_);
}

execution ActionPortRead::execute(const TestRepetitions& testrepetition)
{

    auto it=YarpActionDepotStart::portDepot_.find(portname_);
    if(it==YarpActionDepotStart::portDepot_.end())
    {
        stringstream logStream;
        logStream << "Unable to find " << portname_;
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
        return execution::continueexecution;   
    }

    auto port=it;
    Bottle input;
    bool ok=port->second->read(input);
    if(!ok)
    {
        stringstream logStream;
        logStream << "Unable to read " << portname_;
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
        return execution::continueexecution;          
    }

    if(input.toString()!=value_)
    {
        stringstream logStream;
        logStream << "Read unexpected value " << portname_;
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
        return execution::continueexecution;                  
    }

    return execution::continueexecution;
}
