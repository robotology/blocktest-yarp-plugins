/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionCheckComDistance.cpp
 * @authors: Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionCheckComDistance.h"
#include "logger.h"
#include "report.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>


ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCheckComDistance,yarpactions::checkcomdistance);

namespace YarpActions
{

ActionCheckComDistance::ActionCheckComDistance(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
}     

void ActionCheckComDistance::beforeExecute()
{
    getCommandAttribute("comdistancemax",commaxdistance_);
    getCommandAttribute("comdistancemin",commindistance_);    
}


execution ActionCheckComDistance::execute(const TestRepetitions&)
{
   /* bool error{false};
    if(test_->comDistance_<commindistance_)
    {
        TXLOG(Severity::error)<<"COM distance too little:"<<test_->comDistance_<<" desidered at least:"<<commindistance_<<std::endl;
        error=true;        
    }
        
    if(test_->comDistance_>commaxdistance_)
    {
        TXLOG(Severity::error)<<"COM distance too big:"<<test_->comDistance_<<" desidered at least:"<<commaxdistance_<<std::endl;
        error=true;        
    }


    if(error)
        addProblem(testrepetition,Severity::error);
*/
    return execution::stopexecution;
}

}