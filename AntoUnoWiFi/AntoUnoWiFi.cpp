#include <Arduino.h>
#include <Wire.h>
#include <Ciao.h>
#include "AntoUnoWiFi.h"

#define driver "rest"
#define host "api.anto.io"

#define ANTO_GET "/channel/get/"
#define ANTO_SET "/channel/set/" 
const char* key;
const char* thing1;
const char* thing2;

AntoUnoWiFi::AntoUnoWiFi(const char* anto_key,const char* anto_thing)
{
	key=anto_key;
	thing1=anto_thing;
}
AntoUnoWiFi::AntoUnoWiFi(const char* anto_key,const char* anto_thing1,
const char* anto_thing2 )
{
	key=anto_key;
	thing1=anto_thing1;
	thing2=anto_thing2;
}
String AntoUnoWiFi::mix_String(const char* anto_ch,const char* anto_thing) 
//get
{
	rawString="/channel/get/";
	rawString+=key;
	rawString+="/";
	rawString+=anto_thing;
	rawString+="/";
	rawString+=anto_ch;
	
	return rawString;
}
String AntoUnoWiFi::mix_String(String myString,
const char* anto_ch,const char* anto_thing) //set
{
	rawString="/channel/set/";
	rawString+=key;
	rawString+="/";
	rawString+=anto_thing;
	rawString+="/";
	rawString+=anto_ch;
	rawString+="/";
	rawString+=myString;
	
	return rawString;
}
float AntoUnoWiFi::to_float(String data)
{
	return data.toFloat();
}
int AntoUnoWiFi::to_int(String data)
{
	return data.toInt();
}
String AntoUnoWiFi::CutData(int count_length,char cdms[])
{
	String cut1,cut2[4];
	int y,i;
	for(y=0;y<count_length;y++)
	{
		if(cdms[y]=='{'||cdms[y]=='"')
		{
			continue;
		}
		else
		{
			cut1+=cdms[y];
		}
	}
	
	int j=cut1.length();
	char cdms2[j];
	cut1.toCharArray(cdms2,j);
	for(i=0;i<4;i++)
	{
		for(y=0;y<j;y++)
		{
			if(cdms2[y]==':'||cdms2[y]==',')
			{
				i+=1;
			}
			else if(cdms2[y]==' ')
			{
				y=j+1;
				i=5;
			}
			else
			{
				cut2[i]+=cdms2[y];
			}
		}
	}
	return cut2[3];
}

void AntoUnoWiFi::AntoSwitch(int pin,const char* channel)
{
	String url="/channel/get/";
	url+=key;
	url+="/";
	url+=thing1;
	url+="/";
	url+= channel;
	
    CiaoData data=Ciao.read(driver,host,url,"GET");
	if(!data.isEmpty())
	{
		String a=data.get(1);
		if(a=="400"||a=="404")
		{
			Ciao.println("Bad request");
			readstring="Bad_request";
		}
		else
		{
			rawString=data.get(2);
			int count=rawString.length();
	        char cdms[count];
	        rawString.toCharArray(cdms,count);
	        readstring=CutData(count,cdms);
		}
	}
	else
	{
		Ciao.println("Error");
		readstring="Error";
	}
	
	if(readstring=="1")
	{
		digitalWrite(pin,LOW);
	}
	else if(readstring=="0")
	{
		digitalWrite(pin,HIGH);
	}
	else
	{
		Ciao.println("Excption");
	}
}
void AntoUnoWiFi::AntoSwitch(int pin,const char* channel,int num_thing)
{
	if(num_thing==2)
	{
		String url="/channel/get/";
        url+=key;
	    url+="/";
	    url+=thing2;
	    url+="/";
	    url+= channel;
	
        CiaoData data=Ciao.read(driver,host,url,"GET");
	    if(!data.isEmpty())
       {
		  String a=data.get(1);
		  if(a=="400"||a=="404")
		  {
			  Ciao.println("Bad request");
			  readstring="Bad_request";
		  }
		  else
		  {
			  rawString=data.get(2);
			  int count=rawString.length();
              char cdms[count];
	          rawString.toCharArray(cdms,count);
	          readstring=CutData(count,cdms);
		  }
	   }
	   else
	   {
		  Ciao.println("Error");
		  readstring="Error";
	   }
	
	   if(readstring=="1")
	    {
		  digitalWrite(pin,LOW);
	    }
	  else if(readstring=="0")
	    {
		  digitalWrite(pin,HIGH);
	    }
      else
	   {
		  Ciao.println("Excption");
	   }
	}
	else
	{
		Ciao.println("Excption plest use first key");
	}
}
void AntoUnoWiFi::AntoDataService(const char* anto_service){
	String url="/request/";
	url+=key;
	url+="/";
	url+=anto_service;
	
	CiaoData data=Ciao.read(driver,host,url);
	if(!data.isEmpty())
	{
		String a=data.get(1);
		if(a=="400"||a=="404")
		{
			readstring="Bad_request";
		}
		else
		{
			rawString=data.get(2);
			int count=rawString.length();
			char cdms[count];
			rawString.toCharArray(cdms,count);
			readstring=CutData(count,cdms);
		}
	}
	else
	{
		readstring="Error";
	}	
}
void AntoUnoWiFi::AntoGetString(const char* anto_ch)
{
	String url="/channel/get/";
	url+=key;
	url+="/";
	url+=thing1;
	url+="/";
	url+= anto_ch;
	
    CiaoData data=Ciao.read(driver,host,url,"GET");
    if(!data.isEmpty())
    {
      String a=data.get(1);
      if(a=="400"||a=="404")
       {
          //Ciao.println("Bad request");
          Ciao.println(url);
          readstring="Bad_request";
       }
       else
       {
		  rawString=data.get(2);
          int count=rawString.length();
          char cdms[count];
          rawString.toCharArray(cdms,count);
          readstring=CutData(count,cdms);
          //Ciao.println(url);
       }
    }
    else
    {
       //Ciao.println("Error");
       Ciao.println(url);
       readstring="Error";
    }
}
bool AntoUnoWiFi::AntoSetString(String myString,const char* anto_ch)
{
	String url="/channel/set/";
	url+=key;
	url+="/";
	url+=thing1;
	url+="/";
	url+=anto_ch;
	url+="/";
	url+=myString;
	
	CiaoData data=Ciao.read(driver,host,url,"GET");
	if(!data.isEmpty())
	{
		String a=data.get(1);
		if(a=="400"||a=="404")
		{
			status="BadRequest";
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		status="ErrorUrl";
		Ciao.println(url);
		return false;
	}
}

float AntoUnoWiFi::AntoGetFloat(const char* anto_ch){
	//rawString=AntoGetString1(anto_ch);
    AntoGetString(anto_ch);
	rawString=readstring;
	if(rawString!="Bad_request"||rawString!="Error")
	{
		return to_float(rawString);
	}
	else
	{
		status="Can't_readInt";
		return 0;
	}
}
int AntoUnoWiFi::AntoGetInt(const char* anto_ch){
	//rawString=AntoGetString1(anto_ch);
    AntoGetString(anto_ch);
	rawString=readstring;
	if(rawString!="Bad_request"||rawString!="Error")
	{
		return to_int(rawString);
	}
	else
	{
		status="Can't_readInt";
		return 0;
	}
}

void AntoUnoWiFi::AntoGetString(const char* anto_ch,int thing_num)
{
	/*if(thing_num==1)
	{
		rawString=mix_String(anto_ch,thing1);
	}
	else if(thing_num==2)
	{
		rawString=mix_String(anto_ch,thing2);
	}
	else
	{
		Ciao.println("Not fond thing");
	}
	
	CiaoData data=Ciao.read(driver,host,rawString,"GET");
	if(!data.isEmpty())
	{
		String a=data.get(1);
		if(a=="400"||a=="404")
		{
			readstring="Badrequest";
		}
		else
		{
			CutString=data.get(2);
			int y=CutString.length();
			char cdms[y];
			CutString.toCharArray(cdms,y);
			readstring=CutData(y,cdms);	
		}
	}
	else
	{
		readstring="Error";
		//data="";
	}
	//data="";*/
	if(thing_num==2)
	{
		String url="/channel/get/";
	    url+=key;
	    url+="/";
	    url+=thing2;
	    url+="/";
	    url+= anto_ch;
	
        CiaoData data=Ciao.read(driver,host,url,"GET");
        if(!data.isEmpty())
        {
          String a=data.get(1);
          if(a=="400"||a=="404")
          {
            //Ciao.println("Bad request");
            Ciao.println(url);
            readstring="Bad_request";
          }
          else
          {
		    rawString=data.get(2);
            int count=rawString.length();
            char cdms[count];
            rawString.toCharArray(cdms,count);
            readstring=CutData(count,cdms);
            //Ciao.println(url);
          }
        }
         else
         {
           //Ciao.println("Error");
           Ciao.println(url);
           readstring="Error";
         }
	}
	else
	{
		Ciao.println("Plest use first key");
	}
}
