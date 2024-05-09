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

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionPortWrite, yarpactions::yarpportwrite);

ActionPortWrite::ActionPortWrite(const CommandAttributes& commandAttributes,const std::string& testCode) : 
                                    ActionYarp(commandAttributes, testCode)
{}

void ActionPortWrite::beforeExecute()
{
    getCommandAttribute("portname",   portname_);   
    getCommandAttribute("value",   value_);
}

BlockTestCore::execution ActionPortWrite::execute(const TestRepetitions& testrepetition)
{

    auto it=YarpActionDepotStart::portDepot_.find(portname_);
    if(it==YarpActionDepotStart::portDepot_.end())
    {
        stringstream logStream;
        logStream << "Unable to find " << portname_;
        addProblem(testrepetition, Severity::error, logStream.str(),true);
        return BlockTestCore::execution::continueexecution;   
    }

    auto port=it;
    Bottle bot{value_};
    bool ok=port->second->write(bot);
    if(!ok)
    {
        stringstream logStream;
        logStream << "Unable to write " << portname_;
        addProblem(testrepetition, Severity::error, logStream.str(),true);
        return BlockTestCore::execution::continueexecution;          
    }

    return BlockTestCore::execution::continueexecution;
}
