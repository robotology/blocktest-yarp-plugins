/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanClose.h
  * @author Davide Tomé <davide.tome@iit.it>
  */

#pragma once

#include <actionYarp.h>

namespace YarpActions
{
/**
* @class ActionCanClose
* @brief ...
* @todo missing brief and detailed description
*/
class ActionCanClose: public ActionYarp
{
public:
    ActionCanClose(const CommandAttributes& commandAttributes, const std::string& testCode);
    execution execute(const TestRepetitions& testrepetition) override;
    void beforeExecute() override;  

protected:
	std::string portname_{""};

	ACTIONREGISTER_DEC_TYPE(ActionCanClose)
};

} // namespace YarpActions
