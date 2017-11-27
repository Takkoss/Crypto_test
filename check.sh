#!/bin/bash
MODULE="pam_tek_module.so";
grep "auth optional $MODULE" /etc/pam.d/common-auth;
if [ "$?" = 0 ]
then
    echo "$MODULE is registered as a auth module";
else
    echo "$MODULE is not registered as a auth module";
fi

grep "session optional $MODULE" /etc/pam.d/common-session;
if [ "$?" = 0 ]
then
    echo "$MODULE is registered as a session module";
else
    echo "$MODULE is not registered as a session module";
fi

grep "password optional $MODULE" /etc/pam.d/common-password;
if [ "$?" = 0 ]
then
    echo "$MODULE is registered as a password module";
else
    echo "$MODULE is not registered as a password module";
fi
