/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

 /**
  * @file ActionCheckJointPosition.h
  * @author Andrea Ruzzenenti <andrea.ruzzenenti@iit.it>
  */

#include "actionYarp.h"
#include "yarpActionDepotStart.h"
#include <yarp/dev/PolyDriver.h>
#include <memory>

using namespace YarpActions;
using namespace yarp::dev;
using namespace yarp::os;
namespace YarpAction
{
    class ActionPolydriverOpener : public ActionYarp
    {
    public:
        ActionPolydriverOpener(const CommandAttributes& parameters, const std::string& testCode);
        execution execute(unsigned int testrepetition) override { return execution::continueexecution; };

    private:
        bool        opened_{false};
        Property    p_;
        std::string tag_;

        ACTIONREGISTER_DEC_TYPE(ActionPolydriverOpener)
    };


    ActionPolydriverOpener::ActionPolydriverOpener(const CommandAttributes& parameters, const std::string& testCode) : ActionYarp(parameters, testCode)
    {
        
        CommandAttributes myparameters = parameters;
        tag_                           = parameters.at("polydrivertag");
        myparameters.erase("polydrivertag");

        for (const auto& kv : parameters)
        {
            auto prm = tokenize<std::string>(kv.second);
            if (prm.size() != 2)
                continue;
            p_.put(prm[0], prm[1]);
        }

        auto pdr = std::make_shared<PolyDriver>();
        opened_ = pdr->open(p_);

        if (opened_)
            YarpActionDepotStart::polyDriverDepot_[tag_] = pdr;
        else
        {
            addProblem(0, Severity::critical, "Polydriver failed to open");
            TXLOG(Severity::error) << "polydriver failed to open" << std::endl;
        }
    };
    ACTIONREGISTER_DEF_TYPE(ActionPolydriverOpener, "yarpopenpolydriver");
}