/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionPortDisconnect.h
  * @author Luca Tricerri <luca.tricerri@iit.it>
  *         Nicolo' Genesio <nicolo.genesio@iit.it>
  */

#pragma once

#include <actionYarp.h>

namespace YarpActions
{
/**
* @class ActionPortDisconnect
* @brief ...
* @todo missing brief and detailed description
*/
class ActionPortDisconnect: public ActionYarp
{
public:
	ActionPortDisconnect(const CommandAttributes& commandAttributes, const std::string& testCode);
	execution execute(unsigned int testrepetition) override;

protected:
	std::string src_{""};
	std::string dst_{""};

	ACTIONREGISTER_DEC_TYPE(ActionPortDisconnect)
};

} // namespace YarpActions
