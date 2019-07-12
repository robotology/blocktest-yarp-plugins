/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionYarpNow.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#include "actionYarpNow.h"

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionYarpNow,"yarpnow");

namespace YarpActions
{

ActionYarpNow::ActionYarpNow(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{
}     

void ActionYarpNow::beforeExecute()
{
}

execution ActionYarpNow::execute(const TestRepetitions&)
{
    return execution::continueexecution;;
}

double ActionYarpNow::getDouble()
{
    return yarp::os::Time::now();
}    

}