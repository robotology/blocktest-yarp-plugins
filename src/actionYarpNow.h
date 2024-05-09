/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionYarpNow.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{
/**
 * @class ActionYarpWait
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionYarpNow : public ActionYarp
{
    public:
        ActionYarpNow(const CommandAttributes& commandAttributes,const std::string& testCode);    
        BlockTestCore::execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        
        double getDouble() override;    
    private:        
        double seconds_{0};

    ACTIONREGISTER_DEC_TYPE(ActionYarpNow)        
};
}
