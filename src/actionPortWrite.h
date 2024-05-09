/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file actionPortWrite.h
  * @author Luca Tricerri <luca.tricerri@iit.it>
  */

#pragma once

#include <actionYarp.h>

namespace YarpActions
{
/**
* @class ActionPortWrite
* @brief ...
* @todo missing brief and detailed description
*/
class ActionPortWrite : public ActionYarp
{
public:
    ActionPortWrite(const CommandAttributes& commandAttributes, const std::string& testCode);
    BlockTestCore::execution execute(const TestRepetitions& testrepetition) override;
    void beforeExecute() override;

protected:
	std::string portname_{""};
  std::string value_{""};

	ACTIONREGISTER_DEC_TYPE(ActionPortWrite)
};

} // namespace YarpActions
