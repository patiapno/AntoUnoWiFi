#include <Arduino.h>
#include <Wire.h>
#include <Ciao.h>

class AntoUnoWiFi{
	public:
		AntoUnoWiFi(const char* anto_key,const char* anto_thing);	
		AntoUnoWiFi(const char* anto_key,const char* anto_thing1,
		const char* anto_thing2);
		void AntoSwitch(int pin,const char* channel);
		//it use to control your pin
		void AntoDataService(const char* anto_service);
		//can read=your dataService,can't read=Error
		void AntoSwitch(int pin,const char* channel,int num_thing);
		//it use to control your pin
		
		void AntoGetString(const char* anto_ch);
		bool AntoSetString(String myString,const char* anto_ch);
		float AntoGetFloat(const char* anto_ch);
		int AntoGetInt(const char* anto_ch);
		
		void AntoGetString(const char* anto_ch,int thing_num);
	 private:
	 	String CutData(int count_length,char cdms[]);
	 	String rawString;
	 	String CutString;
	 	float to_float(String data);
	 	int to_int(String data);
	 	String mix_String(String myString,
		 const char* anto_ch,const char* anto_thing);
	 	String mix_String(const char* anto_ch,const char* anto_thing);
     public:
     	String readstring;
     	float  readfloat;
     	bool can_read;
     	int readint;
     	String status;
};