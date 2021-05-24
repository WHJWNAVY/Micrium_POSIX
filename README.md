# Micrium uCOS3

* Micrium ***[uCOS3](https://github.com/weston-embedded/uC-OS3)*** Ports for Linux POSIX(ubuntu)
* orig source: ***[Micrium_POSIX.tar.gz](https://github.com/WHJWNAVY/Micrium-uCOS/blob/master/orig/Micrium_POSIX.tar.gz)***

## Configuring the Build Environment

In order to run µC/OS-III on Linux, the maximum realtime priority for processes must be increased. For the following step, you must acquire root access. Modify ***`/etc/security/limits.conf`*** by adding the following line, replacing `“username”` with your login name:

```
username - rtprio unlimited
```


Once you save the changes, log out of your original session and then log back in.

## Building and Running

> build

```bash
$ make && make install
```

> run

```bash
$ sudo ./install/ucos_app
```

> output

```
Error: RTPRIO[0 - -1] limit is too low. Set to 'unlimited' via 'ulimit -r' or /etc/security/limits.conf
uCOS-III is running.
uCOS-III is running.
uCOS-III is running.
uCOS-III is running.
uCOS-III is running.
uCOS-III is running.
uCOS-III is running.
```

