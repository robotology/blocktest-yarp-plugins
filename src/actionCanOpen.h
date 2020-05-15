/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanOpen.h
  * @author Davide Tomé <davide.tome@iit.it>
  */

#pragma once

#include <actionCanClose.h>

namespace YarpActions
{
  class ActionCanOpen : public ActionCanClose
  {
  public:
      ActionCanOpen(const CommandAttributes& commandAttributes, const std::string& testCode);
      execution execute(const TestRepetitions& testrepetition) override;
      void beforeExecute() override;

    ACTIONREGISTER_DEC_TYPE(ActionCanOpen)
  };

} // namespace YarpActions
