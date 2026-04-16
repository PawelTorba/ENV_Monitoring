# ESP32 Enviroment Monitoring 

Use [Wokwi for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode) to simulate this project.

## Building

This is a [PlatformIO](https://platformio.org) project. To build it, [install PlatformIO](https://docs.platformio.org/en/latest/core/installation/index.html), and then run the following command:

```
pio run
```

## Simulating

To simulate this project, install [Wokwi for VS Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode). Open the project directory in Visual Studio Code, press **F1** and select "Wokwi: Start Simulator".

To start monitoring the simulated values please install Live View in VSCode and go to localhost:5500 (demo.html)

Project supports automatic email notifications using Gmail STP.

//TO DO:
1 -- MOTION SENSOR - NIE DZIAŁA SYMULACJA - BRAK DANYCH WYSYŁANYCH DO AZURE <br>
2 -- MOTION SENSOR - WYKRES KIEDY WYSTĘPOWAŁ RUCH A KIEDY NIE (STAN AKTYWNY/NIEAKTYWNY) - DO ZROBIENIA PO PUNKCIE 1 <br>
3 -- AUTOREFRESH - NIE ODŚWIEŻA WARTOŚCI "LATEST VALUES" JEDYNIE WYKRESY LINIOWE <br>
