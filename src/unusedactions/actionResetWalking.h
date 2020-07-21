/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionResetWalking.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{

/**
 * @class ActionResetWalking
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionResetWalking : public ActionYarp
{
    public:
        ActionResetWalking(const CommandAttributes& commandAttributes,,const std::string& testCode);
        execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        

    ACTIONREGISTER_DEC_TYPE(ActionResetWalking)        
};

}
