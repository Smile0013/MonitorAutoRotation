┌─┬─┐    ┌┬┐     ┌──┐ ┌┐   ┌─┐ ┌┐   ┌┐┌┐     
││││├─┬─┬┼┤└┬─┬┬┐│┌┐├┬┤└┬─┐│┼├─┤└┬─┐│└┼┼─┬─┬┐
│││││┼│││││┌┤┼│┌┘│├┤│││┌┤┼││┐┤┼│┌┤┼└┤┌┤│┼││││
└┴─┴┴─┴┴─┴┴─┴─┴┘ └┘└┴─┴─┴─┘└┴┴─┴─┴──┴─┴┴─┴┴─┘
Read Me

Welcome to the Monitor Auto Rotation!
First, thank you for using this little program, and I hope you like it.

table of contents:
------------------------------------------------------------------------------------------------------------------------
Discription...........................................................Line...17
Equipmant.............................................................Line...23
UD Variables..........................................................Line...30
------------------------------------------------------------------------------------------------------------------------

__Discription__
This program will automaticly rotate screen of your monitor when arduino detects rotation. It works only for Linux OS.
When rotation detected, arduino will emulate keyboard and type "ctrl+alt+t" to run terminal, after that it will type
command for rotating screen adn at last it will close terminal bay typing "exit". Beforu using make shure you checked
UD Variables.

__Equipmant__
Equpment needed for this project:
    - Arduino IDE
    - Arduino pro-micro/leonardo
    - MPU-6050
    - PC with Linux OS

__UD Variables__
User defined variables are variables that are ment to be changed by user befour using program.
    - screenName:           enter name of screen you want to rotate. To check all screen names of your system use
                            xrandr --query.
    - systemSensitivity:    needed value change detected by gyroscope befour trigering screen rotating sequence
    - rotationalModifier:   direction of rotoation, depends on side of monitor on witch device is connected, and
                            orientation of MPU-6050 module.
