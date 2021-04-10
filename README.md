# Electronic-voting-system
 RFID based electronic voting system.
Initially project name is displayed on the LCD for some time. After that, controller is
waiting for the RFID card from the voter or user. Once voter or user is placed the RFID card in
front of the RFID reader then reader is reading the card number and giving that card number to the
controller through serial communication. After reading the card number, controller is checking the
card number with predefined card numbers which are already there in the application program. If
the card is matched with any one of the card number then one time password is generated and that
password should be displayed on the LCD for some time. Then voter or user has to enter the
password from the keypad. If the entered password is correct then one menu will display on the
LCD with party symbols. By using keypad voter has to select the one party. If the password is
wrong the one led is ON just for giving information about wrong password is entered. Menu
contains the following options.
********* MENU *********
1. PARTY1 - SYMBOL
2. PARTY2 - SYMBOL
3. PARTY3 - SYMBOL
4. PARTY4 - SYMBOL
Based on the voter interest he/she has to select one option from the menu. If the voter is
selecting the wrong option again same menu will display until voter is selecting the correct option
from the menu. After voting is completed that status is added to the previous result of that particular
party. For this we are using the EEPROM to save the voting result for all parties. For each party we
are going to use one memory location to save the result status. Here for each voter we are issuing
one RFID card. Finally to see the voting result voter officer’s card is required to place.
----in program , in array first 3 cards are of voter and 4th of officer.----