/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionPortClose.h
  * @author Luca Tricerri <luca.tricerri@iit.it>
  *         Nicolo' Genesio <nicolo.genesio@iit.it>
  */

#pragma once

#include <actionYarp.h>

namespace YarpActions
{
/**
* @class ActionPortClose
* @brief ...
* @todo missing brief and detailed description
*/
class ActionPortClose: public ActionYarp
{
public:
    ActionPortClose(const CommandAttributes& commandAttributes, const std::string& testCode);
    execution execute(unsigned int testrepetition) override;
    void beforeExecute() override;  

protected:
	std::string portname_{""};

	ACTIONREGISTER_DEC_TYPE(ActionPortClose)
};

} // namespace YarpActions
