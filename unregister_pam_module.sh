#!/bin/bash
MODULE="pam_tek_module.so";
sudo grep "auth optional $MODULE" /etc/pam.d/common-auth;
if [ "$?" = 0 ]
then
    sudo sed -i "/auth optional $MODULE/d" /etc/pam.d/common-auth;
fi
sudo grep "session optional $MODULE" /etc/pam.d/common-session;
if [ "$?" = 0 ]
then
    sudo sed -i "/session optional $MODULE/d" /etc/pam.d/common-session;
fi
sudo grep "password optional $MODULE" /etc/pam.d/common-password;
if [ "$?" = 0 ]
then
    sudo sed -i "/password optional $MODULE/d" /etc/pam.d/common-password;
fi
sudo rm /lib/security/$MODULE;
