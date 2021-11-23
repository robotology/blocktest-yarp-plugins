# CI Status
![Continuous Integration](https://github.com/robotology/blocktest-yarp-plugins/workflows/Continuous%20Integration/badge.svg)

# 1. blocktest-yarp-plugins


- [CI Status](#ci-status)
- [1. blocktest-yarp-plugins](#1-blocktest-yarp-plugins)
- [4. Installation](#4-installation)
  - [4.1. Prerequisite Linux](#41-prerequisite-linux)
  - [4.2. Prerequisite Windows](#42-prerequisite-windows)
  - [4.3. Installation and compilation](#43-installation-and-compilation)
- [2. Available commands](#2-available-commands)
  - [1.0.2. Yarp commands](#102-yarp-commands)
  - [1.0.2. Yarp walking commands (not tested and not more used)](#102-yarp-walking-commands-not-tested-and-not-more-used)


Repository containing the yarp plugins for blocktest.


# 4. Installation

Supported OS: Linux Ubuntu 18.10 and Windows 10.
Boost library version must be >1.64.


## 4.1. Prerequisite Linux

```bash
sudo apt-get install -y cmake libboost-all-dev
```
YARP see https://github.com/robotology/yarp

Add in your bashrc:

```
export CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}:/<build/install_dir_of_yarp>
```
Instead if you use robotology_superbuild in .bashrc:
```
export CMAKE_PREFIX_PATH=:${ROBOTOLOGY_SUPERBUILD_BUILD_DIR}/src/YARP

export ROBOTOLOGY_SUPERBUILD_INSTALL_DIR=<path to your robotology install dir>
source ${ROBOTOLOGY_SUPERBUILD_INSTALL_DIR}/share/robotology-superbuild/setup.sh

```

## 4.2. Prerequisite Windows

```bash
vcpkg install boost:x86-windows
```
YARP see https://github.com/robotology/yarp

In bash:
```bash
export blocktestcore_DIR=<path to your blocktest build dir>
```

## 4.3. Installation and compilation

In order to compile just execute the following commands in a bash
terminal.
```bash
git clone https://github.com/robotology/blocktest-yarp-plugins     
cd blocktest-yarp-plugins
mkdir build
cd build
ccmake ..
```
Make sure your CMAKE_INSTALL_PREFIX in ccmake is \<path to your blocktest install dir\>

Suggested location:
```
~\blocktest\install
```

Make sure your blocktestcore_DIR is \<path to your blocktest build dir\>

Suggested location:
```
~\blocktest\build
```

Make sure your blocktestcore_INCLUDE_DIR is \<path to your blocktest src dir\>



Then:

```bash
make -j 4
make install
```

# 2. Available commands
These action blocks are contained in yarp blocktest plugin.

## 1.0.2. Yarp commands

-   **yarpreset**

    Reset the robot to the original frame position and pose.

    ```xml
        <command name="yarpreset" repetitions="1" wait="0" reporterror="true"/>
    ```

-   **yarpsendpwm**

    Send the pwm value to a specific jointname. The pwm profile can be: ```sin/const/stepwave```  
    If profile is ```const``` dutycycle is between -60 and +60, frequency is not used.  
    If profile is ```sin``` frequency is the sin frequency. 

    ```xml
        <command name="yarpsendpwm" profile="sin" frequency="1" dutycycle="20" time="20" jointname="L_AK_R" repetitions="1" wait="0" reporterror="true"/>
    ```

-   **yarpsendposdirect**

    Send the position to a specific jointname

    ```xml
        <command name="yarpsenddirectpos" jointname="L_AK_R" degree="-30" repetitions="1" wait="0" reporterror="true"/>
    ```

-   **yarpsendpos**

    Send the position to a specific jointname using a minimum jerk trajectory.

    ```xml
        <command name="yarpsendpos" jointname="L_AK_R" degree="0" velocity="20" repetitions="1" wait="0" reporterror="true"/>
    ```

-   **yarpcheckrobot**

    ```xml
        <command name="checkRobot" repetitions="1" wait="0" reporterror="true"/>
    ```
    Check if joints are present.

-   **yarpcheckjointposition**

    Check if the joint position is correct.


    ```xml
        <command name="yarpcheckjointposition" wrappername="/right_leg" jointname="r_ankle_pitch" tolerance="1" expectedvalue="15" repetitions="1" wait="0" reporterror="true"/>
    ``` 

-   **yarpcheckrobotisvertical**

    Check if robot is vertical.

    ```xml
        <command name="yarpcheckrobotisvertical" repetitions="1" wait="0" reporterror="true"/>
    ``` 
-   **yarpsendpwmtrain**

    ```xml
        <command name="yarpsendpwmtrain" dutycycle="20" maxposition="20" minposition="-20" cycletime="10" cyclesleep="8" jointname="L_AK_R" repetitions="1" wait="0" reporterror="true"/>
    ```
    Send a PWM train. Chenge PWM sign when the position is reached

-   **applyforce**

    Apply wrench to the robot.

-   **yarpcanwrite**

    ```xml
       <command library="yarp" name="yarpcanwrite" device="socketcan" messageid="0x011" data="0x17 0x00 0x00 0x00 0x00 0x00 0x00 0x00" candevicenum="0" canmyaddress="0" cantxtimeout="500" canrxtimeout="500" repetitions="1" wait="0" reporterror="true"></command>
    ```
    Sends a CAN message trought ``device`` (socketcan available at the moment) . Sets the parameters for the driver.

-   **yarpcanread**

    ```xml
       <command library="yarp" name="yarpcanread" device="socketcan" messageid="0x011" checkdata="false" data="0xAA" candevicenum="0" canmyaddress="0" cantxtimeout="500" canrxtimeout="500" readtimeout="1000" repetitions="1" wait="0" reporterror="true"></command>
    ```
    Receives a CAN message trought ``device`` (socketcan available at the moment) until ``readtimeout`` is reached (milliseconds) . Sets the parameters for the driver. 

 -  **yarpopenpolydriver**

    ```xml
       <command library="yarp" name="yarpopenpolydriver" property="" polydrivertag="" repetitions="1" wait="0" reporterror="true"></command>
    ```
    Open a polydriver using the property as in xml. The property must be in (key value) yarp format. The parameter polydrivertag is used for tagging the device in others block

 -  **yarpclosepolydriver**

    ```xml
       <command library="yarp" name="yarpclosepolydriver" property="" polydrivertag="" repetitions="1" wait="0" reporterror="true"></command>
    ```
    Close a polydriver using the property as in xml. The property must be in (key value) yarp format. The parameter polydrivertag is used for tagging the device in others block


## 1.0.2. Yarp walking commands (not tested and not more used)


-   **setvelocity**

    ```xml
        <command name="setVelocity" xvelocity="0.05" yvelocity="0.00001" repetitions="1" wait="0" reporterror="true"/>
    ```

    The attributes xvelocity and yvelocity rapesent the velocity in that direction.



-   **checkposition**
    ```xml
        <command name="checkPosition" xminposition="0.14" yminposition="0.13" zminposition="0.15" repetitions="1" wait="0" reporterror="true"/>
    ```
    Check if joints are present.


-   **preparestraightwalking**

    ```xml
        <command name="prepareStraightWalking" repetitions="1" wait="0" reporterror="true"/>
    ```

    No params needed

-   **startwalking**

    ```xml
        <command name="startWalking" repetitions="1" wait="0" reporterror="true"/>
    ```

    No params needed

-   **resetwalking**

    ```xml
        <command name="resetWalking" repetitions="1" wait="0" reporterror="true"/>
    ```

    No params needed


    If the robot position is less than xminposition,yminposition,zminposition the check fails. If the position is 0 it doesn't check on that axis.
    For now only the abs value of the position is checked.

