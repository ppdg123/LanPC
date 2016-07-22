#1.Introduction
interfaces for power_on/off/restart PC in LAN. 
#2.Requirement
 + VPS with public ip address
 + LAN server
 + local PC with WOL mainboard

#3.build
Modify lines below in `src/common.h`
```cpp
#define VPS_IP
#define PORT
#define LAN_MAC
#define TM_OT //check time_out
```
Then, run `build.sh` to generate :
`lan_client` : client installed on LAN server
`pc_client` : client installed on local PC
`vps_server` : server installed on VPS
`user_client` : user interfaces

#4.Install

 + `scp` `lan_client` to LAN server; add `* * * * * path_to_+lan_client` to `crontab`
 + `scp` `pc_client` to local pc; add `* * * * * path_to_+pc_client` to `crontab` with `sudo`
 + `scp` `vps_server` to VPS; run by `nohup`;
 + use `user_client` for controlling anywhere.

#5.Framework

![Imgur](http://i.imgur.com/dW9s3Xo.png)



