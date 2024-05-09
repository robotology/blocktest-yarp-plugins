/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionPolydriverClose.h
 * @author Andrea Ruzzenenti <andrea.ruzzenenti@iit.it>, Luca Tricerri
 */

#include "actionYarp.h"
#include "yarpActionDepotStart.h"

#include <memory>

namespace YarpAction {

class ActionPolydriverClose : public YarpActions::ActionYarp {
public:
  ActionPolydriverClose(const CommandAttributes &parameters,
                         const std::string &testCode);
  BlockTestCore::execution execute(const TestRepetitions &) override;
  void beforeExecute() override{};

private:
  std::string tag_;
  yarp::os::Property property_;

  ACTIONREGISTER_DEC_TYPE(ActionPolydriverClose)
};

} // namespace YarpAction