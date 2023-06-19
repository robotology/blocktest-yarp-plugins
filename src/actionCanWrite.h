/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanWrite.h
  * @author Davide Tomé <davide.tome@iit.it>
  */

#pragma once

#include <actionYarp.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/CanBusInterface.h>
#include <yarp/sig/Vector.h>


namespace YarpActions
{

class ActionCanWrite : public ActionYarp
{
  

public:
    ActionCanWrite(const CommandAttributes& commandAttributes, const std::string& testCode);
    execution execute(const TestRepetitions& testrepetition) override;
    void beforeExecute() override;

protected:
  yarp::dev::ICanBus *iCanBus_;
  yarp::dev::ICanBufferFactory *iBufferFactory_;
  std::string messageId_, data_, polyDriverTag_;
  const int CAN_DRIVER_BUFFER_SIZE_ = 2047;
  const int localBufferSize_ = 512;
  yarp::dev::CanBuffer outBuffer_;

	ACTIONREGISTER_DEC_TYPE(ActionCanWrite)
};

} // namespace YarpActions
