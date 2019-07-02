/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionYarpWait.h
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
class ActionYarpWait : public ActionYarp
{
    public:
        ActionYarpWait(const CommandAttributes& commandAttributes,const std::string& testCode);    
        execution execute(unsigned int testrepetition) override;
        void beforeExecute() override;        

    private:        
        double seconds_{0};

    ACTIONREGISTER_DEC_TYPE(ActionYarpWait)        
};

}

