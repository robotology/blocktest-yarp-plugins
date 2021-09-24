/******************************************************************************
 *                                                                            *
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file syntax.h
 * @author Luca Tricerri <luca.tricerri@iit.it>
 */

#pragma once
namespace yarpsyntax
{
    constexpr char const* polydrivertag{"polydrivertag"};
    constexpr char const* property{"property"};
};

namespace yarpactions
{
    constexpr char const* yarpopenpolydriver{"yarpopenpolydriver"};
    constexpr char const* yarpclosepolydriver{"yarpclosepolydriver"};
    constexpr char const* yarpcanwritepd{"yarpcanwritepd"};   
    constexpr char const* yarpcanwrite{"yarpcanwrite"}; 
    constexpr char const* yarpcanread{"yarpcanread"};
    constexpr char const* yarpportopen{"yarpportopen"};
    constexpr char const* yarpportclose{"yarpportclose"};
    constexpr char const* yarpconnect{"yarpconnect"};
    constexpr char const* yarpdisconnect{"yarpdisconnect"};
    constexpr char const* yarpportread{"yarpportread"};
    constexpr char const* yarpportwrite{"yarpportwrite"};
    constexpr char const* yarpreset{"yarpreset"};
    constexpr char const* yarpsenddirectpos{"yarpsenddirectpos"};
    constexpr char const* yarpsendpos{"yarpsendpos"};
    constexpr char const* yarpsendpwm{"yarpsendpwm"};
    constexpr char const* yarpsendpwmtrain{"yarpsendpwmtrain"};
    constexpr char const* yarpcheckjointposition{"yarpcheckjointposition"};
    constexpr char const* checkposition{"checkposition"};
    constexpr char const* checkrobot{"checkrobot"};
    constexpr char const* yarpcheckrobotisvertical{"yarpcheckrobotisvertical"};
    constexpr char const* checkcomdistance{"checkcomdistance"};
    constexpr char const* yarpresetpose{"yarpresetpose"};
    constexpr char const* applyforce{"applyforce"};
    constexpr char const* yarpnow{"yarpnow"};
    constexpr char const* yarpwait{"yarpwait"};
    constexpr char const* infologgeryarp{"infologgeryarp"};
    //Not used
    constexpr char const* generatetrajectory{"generatetrajectory"};                 //wc
    constexpr char const* resetwalking{"resetwalking"};                             //wc
    constexpr char const* setvelocity{"setvelocity"};                               //wc
    constexpr char const* startwalking{"startwalking"};                             //wc
    constexpr char const* preparestraightwalking{"preparestraightwalking"};         //wc

};