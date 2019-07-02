/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionCheckVertical.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{
/**
 * @class ActionCheckVertical
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionCheckVertical : public ActionYarp
{
    public:
        ActionCheckVertical(const CommandAttributes& commandAttributes,const std::string& testCode);
        execution execute(unsigned int testrepetition) override;
        void beforeExecute() override;        

    ACTIONREGISTER_DEC_TYPE(ActionCheckVertical)        
};
}