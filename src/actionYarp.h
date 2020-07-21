/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionYarp.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "general.h"
#include "logger.h"
#include "action.h"
#include "type.h"
#include "syntax.h"

#include <yarp/dev/PolyDriver.h>    

using namespace BlockTestCore;

namespace YarpActions
{

/**
 * @class ActionYarp
 * @brief ...
 * @todo missing brief, detailed description and methods documentation
 */
class ActionYarp: public Action
{
    public:
        ActionYarp(const CommandAttributes& commandAttributes,const std::string& testCode);
        
        static void getJointNames(yarp::dev::PolyDriver& drive,std::map<std::string,int> &jointNames);        
};

}
