# ESP32-Sound-Level-Monitoring-with-LCD-Display-and-ThingSpeak-Logging
This project uses an ESP32 and a sound sensor to monitor ambient noise levels. A LED indicates high noise, an LCD displays the current level, and the data is sent to ThingSpeak for logging and visualization.

🔍 How it works
1️⃣ Hardware used

Arduino board (e.g., ESP32)

Sound sensor (analog output)

LED (to indicate high noise)

I2C LCD (16×2)

Wi-Fi network for ThingSpeak integration

2️⃣ Program flow

Setup:

Initialize LED pin as output.

Initialize LCD via I2C.

Connect to Wi-Fi.

Start Serial Monitor for debugging.

Loop:

Read analog value from sound sensor.

Display the current sound level on LCD.

If the sound level exceeds 20, turn LED on; otherwise, turn it off.

Every 15 seconds, send the sound data to ThingSpeak via HTTP GET.

3️⃣ What you’ll see

The LCD shows real-time sound intensity.

The LED lights up when the sound exceeds the threshold.

Data is logged on ThingSpeak for remote monitoring.
