/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionSendDirectPosition.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionSendPosition.h"

namespace YarpActions
{

class ActionSendDirectPosition : public ActionYarp
{
    public:
        ActionSendDirectPosition(const CommandAttributes& commandAttributes,const std::string& testCode);    
        execution execute(unsigned int testrepetition) override;
    
    private:
        std::vector<std::string> degree_;
        std::vector<std::string> jointToMove_;
        std::string wrapperPrefix_;

    ACTIONREGISTER_DEC_TYPE(ActionSendDirectPosition)        
};

}
