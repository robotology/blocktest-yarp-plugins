/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionGenerateTrajectory.h
 * @authors: Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{
class ActionGenerateTrajectory : public ActionYarp
{
    public:
        ActionGenerateTrajectory(const CommandAttributes& commandAttributes,const std::string& testCode);
        execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        
    private:
        double lenght_{0};

    ACTIONREGISTER_DEC_TYPE(ActionGenerateTrajectory)        
};

}