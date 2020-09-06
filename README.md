# iot-soleil

## Adventures in IOT land

### Install notes

Install ubuntu server 20.04 LTS with Raspberry Pi Imager

Default username/password after install is ubuntu/ubuntu
Default hostname is ubuntu

### Set up private wireless network on wlan0

Edit /etc/hosts and add

`127.0.0.1 ubuntu # to avoid problems with sudo when dns is down`

Install access point and dns server and switch it off to configure:

```
ubuntu$ sudo apt-get install dnsmasq hostapd dhcpcd5
ubuntu$ sudo systemctl stop dnsmasq
ubuntu$ sudo systemctl stop hostapd
ubuntu$ sudo systemctl stop dhcpcd
```

Append this to /etc/dhcpcd.conf:

```
interface wlan0
static ip_address=192.168.131.1/24
```

Edit contents of /etc/hostapd/hostapd.conf:

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

Disable systemd-resolved:

```
sudo systemctl stop systemd-resolved
sudo systemctl disable systemd-resolved
sudo systemctl mask systemd-resolved
```

Enable hostapd

```
sudo systemctl unmask hostapd
sudo systemctl enable hostapd
sudo systemctl start hostapd
```

Reboot:

`sudo reboot`

Monitor DHCP requests from wifi clients:

`journalctl -u dnsmasq -f`

### Install influxdb

```
echo "deb https://repos.influxdata.com/ubuntu bionic stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
sudo curl -sL https://repos.influxdata.com/influxdb.key | sudo apt-key add -
sudo apt-get install influxdb
sudo systemctl enable --now influxdb
```

Create a database named iot:

curl -i -XPOST http://localhost:8086/query --data-urlencode "q=CREATE DATABASE iot"

Monitor influxdb activity:

`journalctl -u influxdb -f`


### Install grafana

```
sudo apt-get install -y apt-transport-https
sudo apt-get install -y software-properties-common wget
wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
echo "deb https://packages.grafana.com/oss/deb stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list 
sudo apt-get update
sudo apt-get install grafana
```

Start the grafana server:
```
sudo systemctl daemon-reload
sudo systemctl start grafana-server
sudo systemctl status grafana-server
```

Check it has started (navigate to http://ip-address:3000, initial account is admin/admin).

Configure to start up
```
sudo systemctl enable grafana-server.service
```

Configure grafana by adding an influxdb data source with URL http://localhost:8086 and server access, then explore the data and create dashboards as required.
