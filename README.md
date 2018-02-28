# ofxWakeOnLan

## openframeworks addon for Wake on Lan

### Usage
~~~
ofxWakeOnLan wol;
wol.addTargetHost(TARGET_MACADDRESS); //add target computer MAC address, multiple host can be added
wol.setBroadCastAddress("127.0.0.255"); //set broad cast address

wol.excute(); //send MagicPacket to host
~~~

