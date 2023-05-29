# Weather forecast
This console app prints the current temperature in any city in degrees Celsius and degrees Fahrenheit using this [Weather API](https://www.weatherapi.com/).
## Features and usage
- Use ```./weather <city>``` to get the temperature in the city that you typed. If city is not entered the value stored in file city.txt will be used. By default it's London.
- Use ```./weather <city>``` to get the temperature in the city that you typed.
- Use ```./weather <city> -r``` to get the temperature in the city that you typed and store the city in file city.txt.
- Use ```./weather <city> -f``` to get the temperature in the city in degrees Fahrenheit. If city is not entered the value stored in file city.txt will be used. By default the temperature is printed in degrees Celsius.
- These are all possible combinations of the arguments. If the city name is entered, it must be entered as the first argument.
  - ```./weather```
  - ```./weather <city>```
  - ```./weather -f```
  - ```./weather <city> -r```
  - ```./weather <city> -f```
  - ```./weather <city> -r -f```
  - ```./weather <city> -f -r```
## Installation
Clone the repository and launch weather.
## Built with
<ul>
  <li><img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++"></li>
  <li>libcurl library</li>
  <li><a href="https://www.weatherapi.com/">Weather API</a></li>
</ul>

## License
Copyright © 2023, [Kristina Migel](https://github.com/kmigel).
Released under the [MIT License](https://choosealicense.com/licenses/mit/).
