#include <Adafruit_VL53L0X.h>
#include <Wire.h>
 
void rewriteAddress(byte oldAdress, byte newAddress){
	Adafruit_VL53L0X lox = Adafruit_VL53L0X();
	lox.begin(oldAdress);
	if(lox.setAddress(newAddress))
		Serial.printf("Rewriting address 0x%x to 0x%x\n\n",oldAdress ,newAddress);
	else
		Serial.printf("Rewriting failed\n");
}

byte parseHex(){
	byte address = 0;
	for (size_t i = 0; i < 2; i++)
	{
		char c = Serial.read();
		if(c >= '0' && c <= '9'){
			address += (c - '0');
		}
		else if(c >= 'A' && c <= 'F'){
			address += (c - 'A' + 10);
		}
		else if(c >= 'a' && c <= 'f'){
			address += (c - 'a' + 10);
		}
		else{
			Serial.println("Invalid character. Expected a hexadecimal digit.");
			for(;;){
				Serial.read(); // dump
			}
		}
		if(i < 1)
			address <<= 4;
	}
	return address;
}

 
void setup()
{
  Wire.begin();
 
  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}

void loop()
{
	byte error, address, theAddress;
	int nDevices;
	for(;;){
		Serial.println("Scanning...");
	
		nDevices = 0;
		for(address = 1; address < 127; address++ )
		{
			// The i2c_scanner uses the return value of
			// the Write.endTransmisstion to see if
			// a device did acknowledge to the address.
			Wire.beginTransmission(address);
			error = Wire.endTransmission();
		
			if (error == 0)
			{
				Serial.print("I2C device found at address 0x");
				if (address<16)
					Serial.print("0");
				Serial.print(address,HEX);
				Serial.println("  !");
				theAddress = address;
				nDevices++;
			}
			else if (error==4)
			{
				Serial.print("Unknown error at address 0x");
				if (address<16)
					Serial.print("0");
				Serial.println(address,HEX);
			}    
		}
		if (nDevices == 0)
			Serial.println("No I2C devices found\n");
		else if (nDevices == 1){
		    Serial.println("rewrite Address?\n0 for exit");
		    while(!Serial.available());
			rewriteAddress(theAddress, parseHex());
			delay(2000);
		}
		else
			Serial.println("to much addresses found\n");
	
		delay(1000);           // wait 5 seconds for next scan
	}
}

