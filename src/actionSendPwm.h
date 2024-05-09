/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionSendPwm.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{

class ActionSendPwm : public ActionYarp
{
    public:
        ActionSendPwm(const CommandAttributes& commandAttributes,const std::string& testCode);    
        BlockTestCore::execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        
    
    private:
        std::string profile_;
        int dutycycle_{0};
        int time_{0};
        std::string jointname_;
        double frequency_{1};
        int sign(double value);
        std::string wrapperPrefix_;

        static constexpr int securityLimits_{80};

    ACTIONREGISTER_DEC_TYPE(ActionSendPwm)        
};

}