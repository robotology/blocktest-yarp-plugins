/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionPrepareStraightWalking.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{
/**
 * @class ActionPrepareStraightWalking
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionPrepareStraightWalking : public ActionYarp
{
    public:
        ActionPrepareStraightWalking(const CommandAttributes& commandAttributes,const std::string& testCode);
        execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        

    ACTIONREGISTER_DEC_TYPE(ActionPrepareStraightWalking)        
};

}