#include "actionYarp.h"

#include <yarp/dev/all.h>
#include <yarp/dev/IFrameTransform.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "logger.h"
#include "report.h"

using namespace yarp::os;

namespace YarpActions
{

ActionYarp::ActionYarp(const CommandAttributes& commandAttributes,const std::string& testCode):Action(commandAttributes,testCode)
{
}

void ActionYarp::getJointNames(yarp::dev::PolyDriver& drive,std::map<std::string,int> &jointNames)
{
    yarp::dev::IEncoders *iencs=nullptr;
    yarp::dev::IAxisInfo *iaxis=nullptr;
    int nj{0};

    if(!drive.view(iencs))
    {
        TXLOG(Severity::critical)<<"Unable to view IEncoder interface"<<std::endl;
        //addProblem(0,Severity::critical,"Unable to view IEncoder interface");
    }
    if(!drive.view(iaxis))
    {
        TXLOG(Severity::critical)<<"Unable to view IAxisInfo interface"<<std::endl;
        //addProblem(0,Severity::critical,"Unable to view IAxisInfo interface");
    }
    if(!iencs->getAxes(&nj))
    {
        TXLOG(Severity::critical)<<"getAxes failed"<<std::endl;                
        //addProblem(0,Severity::critical,"getAxes failed");      
    }
        
    std::string yarpString;
    
    for (int index=0; index < nj; index++)
    {
        bool ok = iaxis->getAxisName(index,yarpString);
        if(!ok)
        {
            TXLOG(Severity::critical)<<"getAxisName failed"<<std::endl;        
            //addProblem(0,Severity::critical,"getAxisName failed");
        }
        jointNames.insert(std::make_pair(yarpString,index));
    }
}
}
