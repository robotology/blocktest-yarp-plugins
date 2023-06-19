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


namespace YarpAction {

class ActionPolydriverOpener : public YarpActions::ActionYarp {
public:
  ActionPolydriverOpener(const CommandAttributes &parameters,
                         const std::string &testCode);
  execution execute(const TestRepetitions &) override;
  void beforeExecute() override{};

private:
  std::string tag_;
  yarp::os::Property property_;

  ACTIONREGISTER_DEC_TYPE(ActionPolydriverOpener)
};

} // namespace YarpAction