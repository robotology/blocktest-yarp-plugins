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

#include <actionPortDisconnect.h>

namespace YarpActions
{
/**
* @class ActionPortDisconnect
* @brief ...
* @todo missing brief and detailed description
*/
class ActionPortConnect : public ActionPortDisconnect
{
public:
	ActionPortConnect(const CommandAttributes& commandAttributes, const std::string& testCode);
	execution execute(const TestRepetitions& testrepetition) override;
  void beforeExecute() override;  

private:
	std::string crr_;

	ACTIONREGISTER_DEC_TYPE(ActionPortConnect)
};

} // namespace YarpActions
