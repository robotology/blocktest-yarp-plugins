/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionReset.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{

/**
 * @class ActionResetPose
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionResetPose : public ActionYarp
{
    public:
        ActionResetPose(const CommandAttributes& commandAttributes,const std::string& testCode);
        execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        

    ACTIONREGISTER_DEC_TYPE(ActionResetPose)        
};

}