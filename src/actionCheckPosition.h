/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionCheckPosition.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{

class ActionCheckPosition : public ActionYarp
{
    public:
        ActionCheckPosition(const CommandAttributes& commandAttributes,const std::string& testCode);
        BlockTestCore::execution execute(const TestRepetitions& testrepetition) override;
        void beforeExecute() override;        
    
    private:
        double xminposition_{0};
        double yminposition_{0};
        double zminposition_{0};

    ACTIONREGISTER_DEC_TYPE(ActionCheckPosition)        
};

}