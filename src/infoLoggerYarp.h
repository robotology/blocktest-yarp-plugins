#pragma once

/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file infoLoggerYarp.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#include "general.h"
#include "type.h"
#include "infoLogger.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ControlBoardInterfaces.h>


using namespace BlockTestCore;

namespace YarpActions
{
class InfoLoggerYarp: public InfoLogger
{
    public:
        InfoLoggerYarp(const std::string& toLog,double loggingTime,const std::string& wrapperName,const std::string& testCode,int repetition);
        ~InfoLoggerYarp();
        void start() override;
        void stop() override;

        std::shared_ptr<std::thread> work_;

    private:
        std::map<std::string, int> jointNames_;

        void working();

        //std::shared_ptr<std::thread> work_;
        std::atomic_bool working_{true};

    LOGGERREGISTER_DEC_TYPE(InfoLoggerYarp)        
};
}