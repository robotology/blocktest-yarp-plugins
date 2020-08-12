/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanWritePD.h
  * @author Davide Tomé <davide.tome@iit.it>
  */

#pragma once

#include <actionYarp.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/CanBusInterface.h>
#include <yarp/sig/Vector.h>


using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::os;
using namespace yarp;

namespace YarpActions
{

class ActionCanWritePD : public ActionYarp
{
  

public:
    ActionCanWritePD(const CommandAttributes& commandAttributes, const std::string& testCode);
    execution execute(const TestRepetitions& testrepetition) override;
    void beforeExecute() override;

protected:
  PolyDriver driver_;
  ICanBus *iCanBus_;
  ICanBufferFactory *iBufferFactory_;
  std::string device_, messageId_, data_, polydrivertag_;
  int canBaudRate_, canTxTimeout_, canRxTimeout_, canDeviceNum_, canMyAddress_;
  const int CAN_DRIVER_BUFFER_SIZE_ = 2047;
  const int localBufferSize_ = 512;
  CanBuffer outBuffer_;

	ACTIONREGISTER_DEC_TYPE(ActionCanWritePD)
};

} // namespace YarpActions
