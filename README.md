# Docker Role manager
allow users to easly add or remove themselfs from the docker group on a linux computer

## setup
Run ` build.sh ` on the device you want to use this on  
2 files will be generated: `dkgms` and `dkgm`  
move `dkgms` into a private location  
create a new systemd service unit to run this program on system startup  
example service unit `/etc/systemd/system/dkgms.service`:
```service
[Unit]
Description=dkgms
After=network.target

[Service]
ExecStart=/path/to/dkgms
Type=simple

[Install]
WantedBy=default.target
```
then run the folowing commands `systemctl daemon-reload` and `systemctl start dkgms.service`


Move `dkgm` to anywhere that is on the PATH enviorment varible  
Change the permissions of it so that everyone is allowed to execute it

## useage
- To add a user to the docker group run the command: ` dkgm add USERNAME `
- To remove a user from the docker group run the command ` dkgm remove USERNAME `
