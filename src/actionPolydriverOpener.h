/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file ActionPolydriverOpener.h
 * @author Andrea Ruzzenenti <andrea.ruzzenenti@iit.it>, Luca Tricerri
 */

#include "actionYarp.h"
#include "yarpActionDepotStart.h"

#include <memory>

using namespace YarpActions;
using namespace yarp::dev;
using namespace yarp::os;

namespace YarpAction {

class ActionPolydriverOpener : public ActionYarp {
public:
  ActionPolydriverOpener(const CommandAttributes &parameters,
                         const std::string &testCode);
  execution execute(const TestRepetitions &) override;
  void beforeExecute() override{};

private:
  std::string tag_;
  Property property_;

  ACTIONREGISTER_DEC_TYPE(ActionPolydriverOpener)
};

} // namespace YarpAction