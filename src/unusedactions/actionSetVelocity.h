/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionSetVelocity.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{
/**
 * @class ActionSetVelocity
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionSetVelocity : public ActionYarp
{
    private:
        std::string xVelocity_;
        std::string yVelocity_;

    public:
        ActionSetVelocity(const CommandAttributes& commandAttributes,const std::string& testCode);    
        BlockTestCore::execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        

    ACTIONREGISTER_DEC_TYPE(ActionSetVelocity)        
};

}