# bluetooth-light-automation-with-arduino
#items used

SLAVE
.arduino nano
.HC05 bluetooth module
.A touch switch
.LDR
.a PIR motion sensor

FINALsERIAL
.arduino nano
.HC05 bluetooth module
.Two relays (for two bulbs)



This project has two arduino nano modules which communicate with the use of bluetooth modules.
One arduino (slave) instructs the other one (FINALsERIAL) to switch on the light based on some conditions.
The conditions include light intensity which is read by and ldr and also a motion sensor
