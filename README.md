# BigFont Library for Arduino for hd44780

This library allows an Arduino board (a controller using the Arduino core libraries) to display big digits/numbers on 4 row monochrome hd44780 displays.

This library is derived from [https://github.com/gcassarino/BigFont](https://github.com/gcassarino/BigFont) but unlike the previous this library is for hd44780 displays


## Getting Started

This library was tested using a hd44780 LCD display. The controller was drived using the [hd44780](https://github.com/duinoWitchery/hd44780) LCD Library by duinoWitchery. 

Example of use:
```
    BigFont bigfont(3); // declaration, 2 for 3colx2rows, 3 for 3colx3rows or 4 4colx4rows digits
    
    bigfont.setFontSize(size); // can be used to change display font size 2,3 or 4 at runtime
    
    // somewhere in the code...

    	if(_bigFontSize == 2){
		bigfont.printbigchar(lcd, 0, 0, 0);
		bigfont.printbigchar(lcd, this->_dt.hour, 3, 0);
	} else if(_bigFontSize == 3){
		bigfont.printbigchar(lcd, 0, 0, 0);
		bigfont.printbigchar(lcd, this->_dt.hour, 3, 0);
	} else {
		bigfont.printbigchar(lcd, 0, 0, 0);
		bigfont.printbigchar(lcd, this->_dt.hour, 4, 0);
	}

```
The BigFont library was tested on ESP8266 and ATMega328 boards using the Arduino core.


## Authors

* Tom Igoe et al... - *Initial work*
* [wa1hco](https://github.com/wa1hco/BigFont)
* [Gianluca Cassarino](https://github.com/gcassarino) New LiquidCrystal library
* [Nathan Watson](https://github.com/NathanWatson/BigFont-for-hd44780) This version


## License

This project is licensed under the GPL License - see the [LICENSE](LICENSE) file for details

## Acknowledgments/Credits

* this Library is derived from [gcassarino/BigFont](https://github.com/gcassarino/BigFont) 
