/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionStartWalking.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{

/**
 * @class ActionStartWalking
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionStartWalking : public ActionYarp
{
    public:
        ActionStartWalking(const CommandAttributes& commandAttributes,const std::string& testCode);        
        BlockTestCore::execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        

    ACTIONREGISTER_DEC_TYPE(ActionStartWalking)        
};

}

