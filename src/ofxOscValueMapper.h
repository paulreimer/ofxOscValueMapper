/*
 * Copyright Limbic Media, 2014
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#pragma once

#include "ofxOscReceiver.h"
#include "ofxOscSender.h"

class ofxOscValueMapper
{
public:
  void setup(unsigned short _receivePort);
  
  void addSendDestination(const std::string& _sendHostname, unsigned short _sendPort);
  
  void addFloat(const std::string& addr, float& value, bool doSend=true);
  
  bool processMessages();

private:
  unsigned short receivePort;
  std::vector<std::pair<std::string, unsigned short> > sendSockets;

  ofxOscReceiver oscReceiver;
  std::vector<ofxOscSender> oscSenders;
  
  std::multimap<std::string, float&> oscValueRefMap;
};

