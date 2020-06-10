/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCanRead.h
  * @author Davide Tomé <davide.tome@iit.it>
  */

#pragma once

#include <actionYarp.h>

#include <yarp/os/Network.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/CanBusInterface.h>
#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>

#include <yarp/os/PeriodicThread.h>

using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::os;
using namespace yarp;

namespace YarpActions
{

class ActionCanRead : public ActionYarp
{
  

public:
    ActionCanRead(const CommandAttributes& commandAttributes, const std::string& testCode);
    execution execute(const TestRepetitions& testrepetition) override;
    void beforeExecute() override;

protected:

	PolyDriver driver;
  ICanBus *iCanBus;
  ICanBufferFactory *iBufferFactory;
  
  std::string devname;
  int port;
  const int SNIFFER_THREAD_RATE=50;
const int CAN_DRIVER_BUFFER_SIZE=2047;
const int localBufferSize=512;


    CanBuffer          inBuffer;
    CanBuffer          outBuffer;
   
    std::mutex         mtx;

    unsigned short     boardId;
    unsigned short     canId;

	ACTIONREGISTER_DEC_TYPE(ActionCanRead)
};

} // namespace YarpActions
