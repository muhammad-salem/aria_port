//============================================================================
// Name        : aria_port.cpp
// Author      : Salem
// Version     : 0.1
// Copyright   : Salem copyright notice
// Description : Aria Port in C++, Ansi-style
//============================================================================

#include <iostream>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>
#include <cstdio>

#include <cctype>
#include <iomanip>
#include <sstream>


//#include "JsonObj.h"
#include "chrome.h"
#include "utility.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;
using namespace Utility;


string url_encode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << '%' << setw(2) << int((unsigned char) c);
    }

    return escaped.str();
}

string urlDecode(std::string &eString) {
	std::string ret;
	char ch;
	unsigned int i, j;
	for (i=0; i<eString.length(); i++) {
		if (int(eString[i])==37) {
			sscanf(eString.substr(i+1,2).c_str(), "%x", &j);
			ch=static_cast<char>(j);
			ret+=ch;
			i=i+2;
		} else {
			ret+=eString[i];
		}
	}
	return (ret);
}

string getParamter(string msg) {
	
	Document doc;
	doc.Parse(msg.data());
	
	string param = "";
	param += "--url=";
	string url = doc["url"].GetString();
	param += url_encode(url);

	if (doc.HasMember("referrer")) {
		if(doc["referrer"].GetStringLength() > 0){
			param += " --http-referer=";
			//param += doc["referrer"].GetString();
			string str = doc["referrer"].GetString();
			param += urlEncode(str);
		}
		
	}


	 if (doc.HasMember("cookies")) {
		 if(doc["cookies"].GetStringLength() > 0){

	 //		 // create file
	 //		 char name[L_tmpnam];
	 //		 //tmpnam(name);  // Get temp name
	 //		 mkstemp(name);
	 //		 
	 //		 //		sendMessage("{\"name\": " + string(name) +"\" }");
	 //		 
	 //		 fstream file(name);
	 //	
	 //		 file << cookies;
	 //	
	 //		 //remove(name);
		
			 // [--cookie=COOKIE] [--cookie-file=CFILE]
			 param += " --cookie=\"";
			 param += doc["cookies"].GetString();
			 param +="\"";
	 //		 param += " --cookie-file" + string(name);
		 }
		 
	 }


	if (doc.HasMember("filename")) {
		if(doc["filename"].GetStringLength() > 0){
			param += " --file-name=\"";
			param += doc["filename"].GetString();
			param +="\"";
		}
		
	}

	if (doc.HasMember("fileSize")) {
		if(doc["fileSize"].GetInt64() > 0){
			param += " --fileSize=";
			param += doc["fileSize"].GetInt64();
		}
		
	}

	if (doc.HasMember("useragent")) {
		param += " --user-agent=\"";
		param += doc["useragent"].GetString();
		param +="\"";
	}

	return param;
}


string replace(string str) {
	string temp = "";
	for (unsigned int i = 0; i < str.length(); ++i) {
		if (str[i] == '\\') {
			if (str[i + 1] == 't') {
				temp += '\t';
			} else if (str[i + 1] == 'n') {
				temp += '\n';
			}
			++i;
			continue;
		}
		temp += str[i];
	}
	return temp;
}

/**
 * function UrlToAria(id, url, referrer,
 *  filename, page, postdata, fileSize, mime)
 * 
 * sendNativeMessage({
 'date':Date.now(),
 'id': id,
 'mime': mime,
 'fileSize':fileSize,
 'list': false,
 'page': ((typeof page !== 'undefined') ? page : false),
 'url': url,
 'origUrl': origUrl,
 'cookies': cookie_string,
 'referrer': referrer,
 'filename': filename, 
 'post': ((typeof postdata !== 'undefined') ? postdata : ""),
 'useragent': navigator.userAgent
 });
 */

/**
 * function UrlListToAria(urllist, referrer)
 */

int main(int argc, char* argv[]) {

//	ofstream file("/home/salem/Desktop/rr.txt", ios::app);
	std::string msg = readMessage();
	
	// json job in c++
	string paramter = getParamter(msg);
//	file << paramter << endl << flush;

	string str = "ariafx ";
//	str += doc["url"].GetString();
	str += paramter;
	
//	file << str.data() << endl << flush;
	system(str.data());
//	file.close();
	return 0;
}
