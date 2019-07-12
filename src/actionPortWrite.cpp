/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionPortWrite.cpp
  * @author Luca Tricerri <luca.tricerri@iit.it>
  */

#include <actionPortWrite.h>
#include <yarpActionDepotStart.h>

using namespace std;
using namespace yarp::os;
using namespace YarpActions;

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortWrite, "yarpportwrite");

ActionPortWrite::ActionPortWrite(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionPortWrite::beforeExecute()
{
    getCommandAttribute("portname",   portname_);   
    getCommandAttribute("value",   value_);
}

execution ActionPortWrite::execute(const TestRepetitions& testrepetition)
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
    Bottle bot{value_};
    bool ok=port->second->write(bot);
    if(!ok)
    {
        stringstream logStream;
        logStream << "Unable to write " << portname_;
        TXLOG(Severity::error) << logStream.str() << std::endl;
        addProblem(testrepetition, Severity::error, logStream.str());
        return execution::continueexecution;          
    }

    return execution::continueexecution;
}
