/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file actionCheckVertical.cpp
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */


#include "actionCheckVertical.h"
#include "logger.h"
#include "report.h"
#include "yarpActionDepotStart.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include <cmath>

ACTIONREGISTER_DEF_TYPE(YarpActions::ActionCheckVertical,yarpactions::yarpcheckrobotisvertical);

namespace YarpActions
{
ActionCheckVertical::ActionCheckVertical(const CommandAttributes& commandAttributes,const std::string& testCode):ActionYarp(commandAttributes,testCode)
{}

void ActionCheckVertical::beforeExecute()
{
}

BlockTestCore::execution ActionCheckVertical::execute(const TestRepetitions& testrepetition)
{
    yarp::os::BufferedPort<yarp::sig::Vector> imuPort;
    std::string localImuPort  = "/myrobot/imu:i";
    std::string remoteImuPort = "/" + YarpActionDepotStart::robotName_ + "/inertial";
    bool ok=imuPort.open(localImuPort);
    if(!ok)
    {
        addProblem(testrepetition,Severity::critical,"Unable to open ports checkvertical",true);
        return BlockTestCore::execution::stopexecution;;
    }
    ok=yarp::os::Network::connect(remoteImuPort.c_str(), localImuPort.c_str());
    if(!ok)
    {
        addProblem(testrepetition,Severity::critical,"Unable to connect to imu port",true);
        return BlockTestCore::execution::stopexecution;;
    }

    // To check the robot is vertical, we do a simple test: we check if the z component of the
    // reading of the accelerometer is the biggest one
    yarp::sig::Vector* imuReadings = imuPort.read();
    if(!imuReadings)
    {
        addProblem(testrepetition,Severity::critical,"Impossible to read accelerometer measurements",true);
        return BlockTestCore::execution::stopexecution;;
    }
    if(imuReadings->size()<12)
    {
        TXLOG(Severity::critical)<<"IMU readings should have at least 12 elements current:"<<imuReadings->size()<<std::endl;
        addProblem(testrepetition,Severity::critical,"IMU readings should have at least 12 elements",false);
        return BlockTestCore::execution::stopexecution;;        
    }

    double gravityOnX = std::fabs((*imuReadings)[3]);
    double gravityOnY = std::fabs((*imuReadings)[4]);
    double gravityOnZ = std::fabs((*imuReadings)[5]);

    BlockTestCore::execution error{BlockTestCore::execution::stopexecution};
    if(!(gravityOnX < gravityOnZ))
    {
        TXLOG(Severity::error)<<"Absolute gravity on x:"<<gravityOnX<< " is greater then on z:"<<gravityOnZ<<std::endl;
        error=BlockTestCore::execution::continueexecution;;
    }
    if(!(gravityOnY < gravityOnZ))
    {
        TXLOG(Severity::error)<<"Absolute gravity on y:"<<gravityOnY<< " is greater then on z:"<<gravityOnZ<<std::endl;
        error=BlockTestCore::execution::continueexecution;
    }

    if(error==BlockTestCore::execution::stopexecution)
        addProblem(testrepetition,Severity::error,"Absolute gravity",true);

    imuPort.interrupt();
    imuPort.close();
    return BlockTestCore::execution::continueexecution;;
}
}