#!/bin/bash
MODULE="pam_tek_module.so";
sudo mkdir -p /lib/security/
sudo cp $MODULE /lib/security/$MODULE
sudo grep "auth optional $MODULE" /etc/pam.d/common-auth;
if [ "$?" = 1 ]
then
    echo "Adding $MODULE to auth modules";
    sudo echo -e  "\nauth optional $MODULE" >> /etc/pam.d/common-auth;
fi

sudo grep "session optional $MODULE" /etc/pam.d/common-session;
if [ "$?" = 1 ]
then
    echo "Adding $MODULE to session modules";
    sudo echo -e "\nsession optional $MODULE" >> /etc/pam.d/common-session;
fi

sudo grep "password optional $MODULE" /etc/pam.d/common-password;
if [ "$?" = 1 ]
then
    echo "Adding $MODULE to password modules";
    sudo echo -e "\npassword optional $MODULE" >> /etc/pam.d/common-password;
fi
