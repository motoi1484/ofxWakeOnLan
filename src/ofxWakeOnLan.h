//
//  ofxWakeOnLan.h
//  wakeonlan_test
//
//  Created by Motoi Ishibashi on 2018/02/28.
//
//

#ifndef ofxWakeOnLan_h
#define ofxWakeOnLan_h

#include "ofMain.h"
#include "ofxNetwork.h"


class ofxWakeOnLan
{
public:
    
    ofxWakeOnLan()
    {
    
    }
    
    ~ofxWakeOnLan()
    {
        
    }
    
    void setBroadCastAddress(string address)
    {
        broadcastAddress = address;
    }
    
    void addTargetHost(string hostMacAddress)
    {
        if(hostMacAddress != ""){
            targetHostMacAddress.push_back(hostMacAddress);
        }
    }
    
    void excute()
    {
        for(int i=0; i<targetHostMacAddress.size(); i++){
            
            makeMagicPacket(targetHostMacAddress[i], &magicPacket[0]);
            
            /*for(int i=0; i<102; i++){
                printf("%d ", magicPacket[i]);
            }*/
            
            udp.Create();
            udp.SetEnableBroadcast(true);
            udp.Connect(broadcastAddress.c_str(), 7);
            udp.Send((char*)magicPacket, sizeof(uint8_t)*102);
            udp.Send((char*)magicPacket, sizeof(uint8_t)*102);
            udp.Close();
            
            udp.Create();
            udp.SetEnableBroadcast(true);
            udp.Connect(broadcastAddress.c_str(), 9);
            udp.Send((char*)magicPacket, sizeof(uint8_t)*102);
            udp.Send((char*)magicPacket, sizeof(uint8_t)*102);
            udp.Close();
        }
    
    }
    
private:
    
    vector<string> targetHostMacAddress;
    ofxUDPManager udp;
    string broadcastAddress;
    
    void makeMagicPacket(string macAdd, uint8_t* packet)
    {
        for(int i=0; i<6; i++){
            packet[i] = 0xFF;
        }
        
        unsigned char macAddress[6];
        convertMacAddress(macAdd, &macAddress[0]);
        
        for(int i=6; i<102; i++){
            packet[i] = macAddress[i%6];
        }
    }
    
    void convertMacAddress(string macaddr, uint8_t* byte)
    {
        vector<string> splitaddr = ofSplitString(macaddr, ":");
        if(splitaddr.size() != 6){
            ofLogError() << "ofxWakeOnLan : mac address error";
            return;
        }
        
        for(int i=0; i<splitaddr.size(); i++){
            byte[i] = (uint8_t)strtol(splitaddr[i].c_str(), NULL, 16);
        }
        
        return;
    }
    
    uint8_t magicPacket[102];
    
};

#endif /* ofxWakeOnLan_h */
