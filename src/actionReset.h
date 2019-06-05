/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionReset.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once

#include "actionYarp.h"

namespace YarpActions
{

/**
 * @class ActionReset
 * @brief ...
 * @todo missing brief and detailed description
 */
class ActionReset : public ActionYarp
{
    public:
        ActionReset(const CommandAttributes& commandAttributes,const std::string& testCode);
        execution execute(unsigned int testrepetition) override;

    ACTIONREGISTER_DEC_TYPE(ActionReset)        
};

}