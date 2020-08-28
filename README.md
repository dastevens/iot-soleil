# iot-soleil

## Adventures in IOT land

### Install notes

Install ubuntu server 20.04 LTS with Raspberry Pi Imager

Default username/password after install is ubuntu/ubuntu

### Set up private wireless network on wlan0

Edit /etc/hosts and add

`127.0.0.1 ubuntu # to avoid problems with sudo when dns is down`

Install access point and dns server and switch it off to configure:

```
ubuntu$ sudo apt-get install dnsmasq hostapd dhcpcd
ubuntu$ sudo systemctl stop dnsmasq
ubuntu$ sudo systemctl stop hostapd
ubuntu$ sudo systemctl stop dhcpcd
```

Append this to /etc/dhcpcd.conf:

```
interface wlan0
static ip_address=192.168.131.1/24
```

Edit contents of /etc/hostapd/hostapd.conf

```
interface=wlan0
hw_mode=g
channel=7
wmm_enabled=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
ssid=<NETWORK-SSID>
wpa_passphrase=<NETWORK-PASSPHRASE>
```

Set DAEMON_CONF in /etc/default/hostapd:

`DAEMON_CONF="/etc/hostapd/hostapd.conf"`

Edit contents of /etc/dnsmasq.conf:

```
interface=wlan0
dhcp-range=192.168.131.2,192.168.131.254,24h
```
