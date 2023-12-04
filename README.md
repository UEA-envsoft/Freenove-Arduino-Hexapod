# Freenove-Arduino-Hexapod

The Freenove Hexapod Robot Kit is an excellent value hexapod kit that can be controlled from PC or phone or a supplied rf controller. It is available from ebay or amazon or aliexpress.  
Here's the Amazon UK link: https://www.amazon.co.uk/Freenove-Raspberry-Crawling-Detailed-Tutorial/dp/B07FLXFDZ1?th=1  
One nice thing about the kit is that it exposes certain pins for further expansion possibilities. I decided that what the hexapod needed was a head with a dot matrix mouth and ultrasonic sensor 'eyes' that could scan from side to side and provide the necessary information to code in some object avoidance. I also added a buzzer for good measure!

Note this model uses the US-100 Ultrasonic Distance Sensor (using serial comms) not the HC-SR04 which has slightly different dimensions (and didn't play nicely with the existing code).

The 3d files for the head are here: https://www.printables.com/model/654812-head-for-the-freenove-hexapod

Assembly instructions are here: https://www.instructables.com/Moving-Sensing-Head-for-the-Freenove-Hexapod

The code makes use of the additional control buttons on the app:  
20 is happy expression  
21 is angry expression  
15 is suprised expression  
2 is sad expression  
14 is obj avoid on  
3 is obj avoid off - this can be a hit or miss, so blocking the ultrasonic sensor with your finger will also cancel object avoidance after a few moments.  
