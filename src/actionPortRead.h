/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file actionPortRead.h
  * @author Luca Tricerri <luca.tricerri@iit.it>
  */

#pragma once

#include <actionYarp.h>

namespace YarpActions
{
/**
* @class ActionPortRead
* @brief ...
* @todo missing brief and detailed description
*/
class ActionPortRead : public ActionYarp
{
public:
    ActionPortRead(const CommandAttributes& commandAttributes, const std::string& testCode);
    execution execute(unsigned int testrepetition) override;
    void beforeExecute() override;

protected:
	std::string portname_{""};
  std::string value_{""};

	ACTIONREGISTER_DEC_TYPE(ActionPortRead)
};

} // namespace YarpActions
