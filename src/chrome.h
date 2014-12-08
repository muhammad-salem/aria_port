/*
 * chrome.h
 *
 *  Created on: Nov 24, 2014
 *      Author: salem
 */

#include <iostream>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

#ifndef CHROME_H_
#define CHROME_H_



void sendLength(unsigned int len ){
//	std::cout   << char(len>>0)
//				<< char(len>>8)
//				<< char(len>>16)
//				<< char(len>>24);
	cout.write(reinterpret_cast<char*>(&len), 4);
}

void sendMSG(std::string msg){
	 std::cout << msg << std::flush;
}

void sendMessage(std::string message){
	 sendLength(message.length());
	 sendMSG(message);
}

unsigned int readLength(){
	uint32_t reqLen = 0;
	cin.read(reinterpret_cast<char*>(&reqLen), 4);
	return reqLen;		
}

std::string readMSG( unsigned int length){
	std::string msg = "";
	for (unsigned int i = 0; i < length; i++)
	{
		msg += getchar();
	}
	return msg;
}

std::string readMessage(){
	unsigned int length = readLength();
	return readMSG(length);
}



#endif /* CHROME_H_ */
