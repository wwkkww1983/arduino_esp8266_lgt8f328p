/*
 ESP 8266联合BMP180 读取气压并且NTP时间
 测试使用的是  ESP 8266 mini
 使用的库
 BMP180MI

 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
#include <Ticker.h>
#include <Wire.h>
#include <BMP180MI.h>

#define I2C_ADDRESS 0x77

//create an BMP180 object using the I2C interface
BMP180I2C bmp180(I2C_ADDRESS);

#ifndef STASSID
#define STASSID "Xiaomi_E3B4"
#define STAPSK  "xm901unicom"
#define TZ              7       // (utc+) TZ in hours  东8区为啥是+7 ？？？
#define DST_MN          60      // use 60mn for summer time in some countries

#define TZ_MN           ((TZ)*60)
#define NTP0_OR_LOCAL1  1       // 0:use NTP  1:fake external RTC
#define RTC_TEST     1510592825 // 1510592825 = Monday 13 November 2017 17:07:05 UTC

////////////////////////////////////////////////////////

#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)
#endif
// for testing purpose:
extern "C" int clock_gettime(clockid_t unused, struct timespec *tp);

const char * ssid = STASSID; // your network SSID (name)
const char * pass = STAPSK;  // your network password
int conts = 0;  //计数器
boolean if_ntp = false;  //是否同步NTP
uint32_t chipId = ESP.getChipId();
unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "ntp1.aliyun.com"; //换成阿里的NTP的话更快 还有很多 例如 cn.ntp.org.cn

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

timeval tv;
timespec tp;
time_t now;
uint32_t now_ms, now_us;

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp; // @suppress("Abstract class cannot be instantiated")
Ticker oneSec; //定时一秒一次
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	ESP.wdtEnable(WDTO_4S); //打开看门狗

	Serial.begin(115200);
	Serial.println();
	Serial.println();

	// We start by connecting to a WiFi network
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, pass);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");

	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println(WiFi.SSID());

	Serial.println("Starting UDP");
	udp.begin(localPort);
	Serial.print("Local port: ");
	Serial.println(udp.localPort());
	Wire.begin();
	if (!bmp180.begin()) {
		Serial.println(
				"begin() failed. check your BMP180 Interface and I2C Address.");
	}
	//reset sensor to default parameters.
	bmp180.resetToDefaults();

	//enable ultra high resolution mode for pressure measurements
	bmp180.setSamplingMode(BMP180MI::MODE_UHR);

	oneSec.attach(1, oneSecond); //每秒执行一次

}

void oneSecond() {
	Serial.print(chipId);
	// Serial.println(if_ntp);

	if ((conts == 0) or (conts == (30 * 60))
			or (conts == 10 and if_ntp == false)) {
		setTime(ntpServerName); // @suppress("Invalid arguments")
		conts = 0;
	};
	ESP.wdtFeed();
	gettimeofday(&tv, nullptr);
	clock_gettime(0, &tp);
	now = time(nullptr);

	// EPOCH+tz+dst
	Serial.print(" time:");
	Serial.print((uint32_t) now);

	if (!bmp180.measureTemperature()) {
		Serial.println(
				"could not start temperature measurement, is a measurement already running?");
		return;
	}

	//wait for the measurement to finish. proceed as soon as hasValue() returned true.
	do {
		delay(100);
	} while (!bmp180.hasValue());

	Serial.print("  Temperature: ");
	Serial.print(bmp180.getTemperature());
	Serial.print(" degC ");

	//start a pressure measurement. pressure measurements depend on temperature measurement, you should only start a pressure
	//measurement immediately after a temperature measurement.
	if (!bmp180.measurePressure()) {
		Serial.println(
				"could not start perssure measurement, is a measurement already running?");
		return;
	}

	//wait for the measurement to finish. proceed as soon as hasValue() returned true.
	do {
		delay(100);
	} while (!bmp180.hasValue());

	Serial.print("Pressure: ");
	Serial.print(bmp180.getPressure() / 100.0);
	Serial.print(" Pa  ");

	// human readable
	//Serial.print(" ctime:(UTC+");
	//Serial.print((uint32_t) (TZ * 60 + DST_MN));
	//Serial.print("mn) ");
//	Serial.print(ctime(&now));
	print_time();

	//Serial.print(time_t(&now));
	conts++; //计数加1

}

void loop() {
}

void print_time() {
	gettimeofday(&tv, nullptr);
	clock_gettime(0, &tp);

	now = time(nullptr);
	//Serial.print(now.yr, now.mon, now.date, now.hr, now.min, now.sec);

	int y = 1970, mon, d, h, m, s, wk;

	wk = ((now / 86400L) % 7 + 4) % 7; //86400 is secons in one day; +1 for 1970/1/1 is 周四
	do {
		unsigned long ys;
		if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
			ys = 31622400L; //31622400 = 366 * 24 * 3600;
		} else {
			ys = 31536000L;  // 31536000 = 365 * 24 * 3600;
		}
		if (now < (signed long) ys) {
			break;
		} else {
			now -= ys;
			y++;
		}
	} while (1);

	int mons[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
		mons[1] = 29;
	}
	for (mon = 0; mon < 12; mon++) {
		if (now < mons[mon] * 86400L) {
			break;
		} else {
			now -= mons[mon] * 86400L;
		}
	}

	d = now / 86400L + 1; //86400 = 24 * 3600 = how many seconds in a day
	now = now % 86400L;

	h = now / 3600;
	now = now % 3600;
	m = now / 60;
	s = now % 60;

	char buf[50];
	snprintf(buf, sizeof(buf), "%04d/%02d/%02d %02d:%02d:%02d %0d", y, mon + 1,
			d, h, m, s, wk);
	Serial.print("DATE: ");
	Serial.println(buf);

}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress& address) {
	Serial.println("sending NTP packet...");
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	udp.beginPacket(address, 123); //NTP requests are to port 123
	udp.write(packetBuffer, NTP_PACKET_SIZE);
	udp.endPacket();
}
void setTime(const char * ntpServerName) {
	//get a random server from the pool
	WiFi.hostByName(ntpServerName, timeServerIP);
	digitalWrite(LED_BUILTIN, LOW);
	sendNTPpacket(timeServerIP); // send an NTP packet to a time server
	// wait to see if a reply is available
	delay(200);

	int cb = udp.parsePacket();
	if (!cb) {
		Serial.println("no packet yet");
		if_ntp = false;
	} else {
		digitalWrite(LED_BUILTIN, HIGH);
		if_ntp = true;
		Serial.print("packet received, length=");
		Serial.println(cb);
		// We've received a packet, read the data from it
		udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

		//the timestamp starts at byte 40 of the received packet and is four bytes,
		// or two words, long. First, esxtract the two words:

		unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
		unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		//   Serial.print("Seconds since Jan 1 1900 = ");
		//   Serial.println(secsSince1900);

		//    // now convert NTP time into everyday time:
		//   Serial.print("Unix time = ");
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears;
		// print Unix time:
		//  Serial.println(epoch);

		time_t rtc = epoch;
		timeval tv = { rtc, 0 };
		timezone tz = { TZ_MN + DST_MN, 0 };
		settimeofday(&tv, &tz);

		// print the hour, minute and second:
		Serial.print("The UTC time is "); // UTC is the time at Greenwich Meridian (GMT)
		Serial.print((epoch % 86400L) / 3600); // print the hour (86400 equals secs per day)
		Serial.print(':');
		if (((epoch % 3600) / 60) < 10) {
			// In the first 10 minutes of each hour, we'll want a leading '0'
			Serial.print('0');
		}
		Serial.print((epoch % 3600) / 60); // print the minute (3600 equals secs per minute)
		Serial.print(':');
		if ((epoch % 60) < 10) {
			// In the first 10 seconds of each minute, we'll want a leading '0'
			Serial.print('0');
		}
		Serial.println(epoch % 60); // print the second
	}
	// wait ten seconds before asking for the time again

}
