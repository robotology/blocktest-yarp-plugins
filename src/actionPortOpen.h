/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file actionPortOpen.h
  * @author Luca Tricerri <luca.tricerri@iit.it>
  *         Nicolo' Genesio <nicolo.genesio@iit.it>
  */

#pragma once

#include <actionPortClose.h>

namespace YarpActions
{
/**
* @class ActionPortDisconnect
* @brief ...
* @todo missing brief and detailed description
*/
class ActionPortOpen : public ActionPortClose
{
public:
    ActionPortOpen(const CommandAttributes& commandAttributes, const std::string& testCode);
    execution execute(const TestRepetitions& testrepetition) override;
    void beforeExecute() override;

	ACTIONREGISTER_DEC_TYPE(ActionPortOpen)
};

} // namespace YarpActions
