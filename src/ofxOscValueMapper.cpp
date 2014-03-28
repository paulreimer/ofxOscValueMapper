/*
 * Copyright Limbic Media, 2014
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxOscValueMapper.h"

//--------------------------------------------------------------
void
ofxOscValueMapper::setup(unsigned short _receivePort)
{
  receivePort = _receivePort;
  oscReceiver.setup(receivePort);
}

//--------------------------------------------------------------
void
ofxOscValueMapper::addSendDestination(const std::string& _sendHostname, unsigned short _sendPort)
{
  sendSockets.push_back(make_pair(_sendHostname, _sendPort));

  oscSenders.resize(oscSenders.size() + 1);
  oscSenders.back().setup(_sendHostname, _sendPort);
}

//--------------------------------------------------------------
void
ofxOscValueMapper::addFloat(const std::string& addr, float& value, bool doSend)
{
  oscValueRefMap.insert(std::pair<std::string, float&>(addr, value));
  
  if (doSend)
  {
    
  }
}

//--------------------------------------------------------------
bool
ofxOscValueMapper::processMessages()
{
  bool didProcessAnyMessages = false;
  
  while (oscReceiver.hasWaitingMessages())
  {
    ofxOscMessage msg;
    oscReceiver.getNextMessage(&msg);
    
    const std::string& addr = msg.getAddress();
    
    std::pair<std::multimap<std::string, float&>::iterator, std::multimap<std::string, float&>::iterator> matchedRefs;
    matchedRefs = oscValueRefMap.equal_range(addr);
    
    for (std::multimap<std::string, float&>::iterator matchedRefIter=matchedRefs.first;
         matchedRefIter!=matchedRefs.second; ++matchedRefIter)
    {
      matchedRefIter->second = msg.getArgAsFloat(0);
      didProcessAnyMessages = true;
    }
    
    for (std::vector<ofxOscSender>::iterator oscSenderIter=oscSenders.begin();
         oscSenderIter!=oscSenders.end(); ++oscSenderIter)
    {
      oscSenderIter->sendMessage(msg);
    }
  }

  return didProcessAnyMessages;
}

