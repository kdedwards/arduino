# EEPROM Reader/Writer Sketch for Arduino Nano

## Description: This sketch is to program an 28C16A 16K EEPROM using 2 54HC595 8bit shift registers and an Arduino Nano.

## Component List
* 1 x Arduino Nano
* 2 x 54HC595 (referenced as 54HC595-1 and 54HC595-2)
* 1 x 28C16A

## Pinout Connections

### Nano

|Nano Pin|Component|Component Pin Number|Component Pin Description|
|:------:|---------|:------------------:|-------------------------|
|A0      |54HC595-1|14                  |Data                     |
|A1      |54HC595-1|12                  |Latch                    |
|A1      |54HC595-2|12                  |Latch                    |
|A2      |54HC595-1|11                  |Clock                    |
|A2      |54HC595-2|11                  |Clock                    |
|A3      |28C16A   |20                  |Output Enable            |
|A4      |28C16A   |21                  |Write Enable             |
|D2      |28C16A   |9                   |I/O 0                    |
|D3      |28C16A   |10                  |I/O 1                    |
|D4      |28C16A   |11                  |I/O 2                    |
|D5      |28C16A   |13                  |I/O 3                    |
|D6      |28C16A   |14                  |I/O 4                    |
|D7      |28C16A   |15                  |I/O 5                    |
|D8      |28C16A   |16                  |I/O 6                    |
|D9      |28C16A   |17                  |I/O 7                    |
|D13     |Button   |N/A                 |N/A                      |

### 54HC595-1
|54HC595-1 Pin|Component|Component Pin Number|Component Pin Description|
|:------------|---------|:-------------------|-------------------------|
|1            |28C16A   |7                   |A1                       |
|2            |28C16A   |6                   |A2                       |
|3            |28C16A   |5                   |A3                       |
|4            |28C16A   |4                   |A4                       |
|5            |28C16A   |3                   |A5                       |
|6            |28C16A   |2                   |A6                       |
|7            |28C16A   |1                   |A7                       |
|8            |GND      |N/A                 |N/A                      |
|9            |54HC595-2|14                  |Data                     |
|10           |+5v      |N/A                 |N/A                      |
|11           |Nano     |A2                  |N/A                      |
|11           |54HC595-2|11                  |Clock                    |
|12           |Nano     |A1                  |N/A                      |
|12           |54HC595-2|11                  |Latch                    |
|13           |GND      |N/A                 |N/A                      |
|14           |Nano     |A0                  |N/A                      |
|15           |28C16A   |8                   |A0                       |
|16           |+5V      |N/A                 |N/A                      |

### 54HC595-2
|54HC595-2 Pin|Component|Component Pin Number|Component Pin Description|
|:------------|---------|:-------------------|-------------------------|
|1            |28C16A   |22                  |A9                       |
|2            |28C16A   |19                  |A10                      |
|3            |N/A      |N/A                 |N/A                      |
|4            |N/A      |N/A                 |N/A                      |
|5            |N/A      |N/A                 |N/A                      |
|6            |N/A      |N/A                 |N/A                      |
|7            |N/A      |N/A                 |N/A                      |
|8            |GND      |N/A                 |N/A                      |
|9            |N/A      |N/A                 |N/A                      |
|10           |+5v      |N/A                 |N/A                      |
|11           |Nano     |A2                  |N/A                      |
|11           |54HC595-1|11                  |Clock                    |
|12           |Nano     |A1                  |N/A                      |
|12           |54HC595-1|11                  |Latch                    |
|13           |GND      |N/A                 |N/A                      |
|14           |54HC595-1|9                   |Shift Out/Overflow       |
|15           |28C16A   |23                  |A8                       |
|16           |+5V      |N/A                 |N/A                      |

### 28C16A
|28C16A Pin|Component|Component Pin Number|Component Pin Description|
|:---------|---------|:-------------------|-------------------------|
|1         |54HC595-1|7                   |Qh                       |
|2         |54HC595-1|6                   |Qg                       |
|3         |54HC595-1|5                   |Qf                       |
|4         |54HC595-1|4                   |Qe                       |
|5         |54HC595-1|3                   |Qd                       |
|6         |54HC595-1|2                   |Qc                       |
|7         |54HC595-1|1                   |Qb                       |
|8         |54HC595-1|15                  |Qa                       |
|9         |Nano     |D2                  |N/A                      |
|10        |Nano     |D3                  |N/A                      |
|11        |Nano     |D4                  |N/A                      |
|12        |GND      |N/A                 |N/A                      |
|13        |Nano     |D5                  |N/A                      |
|14        |Nano     |D6                  |N/A                      |
|15        |Nano     |D7                  |N/A                      |
|16        |Nano     |D8                  |N/A                      |
|17        |Nano     |D9                  |N/A                      |
|18        |GND      |N/A                 |N/A                      |
|19        |54HC595-2|2                   |Qc                       |
|20        |Nano     |A3                  |N/A                      |
|21        |Nano     |A4                  |N/A                      |
|22        |54HC595-2|1                   |Qb                       |
|23        |54HC595-2|15                  |Qa                       |
|24        |+5V      |N/A                 |N/A                      |

