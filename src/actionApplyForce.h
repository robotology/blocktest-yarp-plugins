/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionApplyForce.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{
/**
 * @class ActionApplyForce
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionApplyForce : public ActionYarp
{
    public:
        ActionApplyForce(const CommandAttributes& commandAttributes,const std::string& testCode);
        BlockTestCore::execution execute(const TestRepetitions& testrepetition) override;        
        void beforeExecute() override;

    private:
        std::string force_;

    ACTIONREGISTER_DEC_TYPE(ActionApplyForce)        
};

}