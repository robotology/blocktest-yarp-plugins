/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionCheckRobot.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{

class ActionCheckRobot : public ActionYarp
{
    public:
        ActionCheckRobot(const CommandAttributes& commandAttributes,const std::string& testCode);
        execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        

    private:
        std::string wrapperPrefix_;
    ACTIONREGISTER_DEC_TYPE(ActionCheckRobot)        
};

}