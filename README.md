[![Build Status](https://travis-ci.org/silver13/BoldClash-BWHOOP-B-03.svg?branch=master)](https://travis-ci.org/silver13/BoldClash-BWHOOP-B-03)

## NotFastEnuf Notes - Bwhoop B03 Silverware modified to work on BWHOOP, E011, or H8mini_blue_board.
Last major update 9.11.18

Testing a new layout for config.h  - feel free to let me know what you think.  Your feedback is appreciated. 

There are two main steps to prep this file for flash.  The first will be in config.h and the second will be in pid.c file.

STEP 1:  Open config.h with keil and make edits to set your selections in 6 categories.

         _Hardware Selection_ - select your target: alienwhoop zer0, bwhoop, e011, or H8mini_blue_board based hardware
         
         _Receiver Settings_ - set rates, expo, radio protocol, transmitter type and assign features to auxiliary channel switches
                              
         _Voltage Settings_ - low voltage cutoff and other voltage related settings - UPDATE: LVC can now be switched on via stick gesture.  See notes for Berzerker release on the releases page.
         
         _Filter Settings_ -set gyro filter and D term filter frequencies and orders - UPDATE: reccomendation is to use alienwhoop switchable filtering.  See notes for Berzerker release on releases page.
         
         _Motor Output Settings_ - set pwm rate, motor curves, inverted yaw for props out, and features related to motor output - UPDATE: props in/props out is now switchable via stick gesture with alienwhoop settings.  See notes for Berzerker release for instructions.
                                 
         _Additional Features_ - remaining special features 
         
STEP 2:  Open pid.c with keil and either edit pids to your preferred values or select a set of pids that I have prepared.   I plan to keep all my tunes in pid.c and will have them labeled and noted with the associated filter settings for each type of build.  All you have to do to use one of my tunes is uncomment the pid group you want to use and make sure the others are commented out.  I will keep whatever pids I'm using updated here if I change them and the default set will always be for a whoop with fpv gear installed.  Setpoint weight values for P are also just below pids - if you want a sharper stick feel on one of my tunes then change these values closer to 1.0.  Stick Accelerator and transition values are here too.  There are two profiles you can populate which are switchable via auxillary channel.

## brianquad Notes - Additions for Analog Aux channels

This option (controlled in config.h) adds support for Analog Aux channels to control certain pre-programmed features. These are intended to be used with a transmitter with knobs/sliders to easily alter parameters while flying. These are controlled by #define lines in config.h. Enable these features by uncommenting the "#define USE_ANALOG_AUX" line. Commenting that line disables all analog aux channels at the compiler level, meaning they do not make the built firmware bigger or slower than it was before.

Initially, these features include:
1. Analog Rate Multiplier (ANALOG_RATE_MULT)
   - Use a tranmitter knob to control your rates to help find your sweet spot without flashing in between
   - Set your MAX_RATE and MAX_RATE_YAW to the highest rate you might want
   - Use the assigned knob to adjust beween 0 and 100% of that rate in a linear scale
     - Putting the knob at its middle point will give you half of your MAX_RATE
2. Analog Max Angle for Level mode (ANALOG_MAX_ANGLE)
   - When in Angle/Level mode, the maximum angle the quad is allowed to tilt (controlling your max speed, etc.) is set by the LEVEL_MAX_ANGLE define
   - When enabling ANALOG_MAX_ANGLE, the LEVEL_MAX_ANGLE define is ignored
   - The knob controls the maximum angle from 0 to 90 degrees in a linear scale
     - Putting the knob at its middle point will give you a maximum angle of 45 degrees
3. PID adjustments (ANALOG_RP_P, etc.)
   - Assigning a knob to one of these defines lets you alter that PID setting from 0.5X to 1.5X of the current setting in pid.c
   - Each of the P, I, or D for Roll, Pitch, and Yaw can be selected in config.h, or Roll and Pitch P, I, or D can be selected together on one knob
   - The PID adjustments can be saved, just like the classic Silverware gesture PID adjustments. To save a new value, use the Down Down Down (DDD) gesture to write the current PID values to flash (including your new one(s)) and re-center your adjusted values. This means to keep your new value after saving, you must re-center your knob/slider.

These initial features are mostly meant to start a conversation on how Analog Aux channels could be used. For example, I'm sure there are better ways to do live PID adjustment with a couple of analog knobs!

###How do you access/assign analog channels? What channels can be used?

For Sbus and DSM, you can assign any of the channels to use as analog aux channels.

For Bayang, you can use a modified version of the Bayang protocol I've made to the Multiprotocol Tx and Deviation Tx firmware that adds two 8-bit analog channels to the protocol.

The Multiprotocol module uses channels 14 and 15 for these analog channels. Set the "Option/Telemetry" value for the Bayang protocol on the Taranis to 2 or 3 (2 to get only the analog channels, 3 to get both Telemetry and the analog channels).

Deviation uses channels 13 and 14. Enable the Aux Analog option for the Bayang protocol.

For both the Multiprotocol module and Deviation, Silverware will not bind with a transmitter that does not have matching options (both Telemetry and Analog Aux channels).

These modifications can be found on the analog aux branch in my forks on GitHub (for now, you _must_ select the branch rather than master):
	https://github.com/brianquad/DIY-Multiprotocol-TX-Module/tree/bayang-analog-aux
	https://github.com/brianquad/deviation/tree/bayang-analog-aux

####How to use Trim Switches for Silverware Analog Aux channels in Deviation
VIRTUAL POT (Example, by Ian444):

1. Say you want to assign LV (left vertical) trim switch to drive the radio channel 11 as if it were a pot, each click driving the pot in one direction or the other, using Virt3 as the intermediate link. (It could be any radio channel and use any free virtual channel.)

2. Go into the TRIMS menu and set the LV trim to Virt3, so replace "whatever-is-there" with Virt3 i.e. it should look like: Virt3/step size/TRIMLV+. You can highlight "Virt3" and hit enter to get into the submenu if you need to. Set step size, trim+, trim- etc. Step size 10 gives 10 clicks up and 10 clicks down. Save it.

3. Go into the MIXER menu and find Virt3, set the mixer type as "simple", Src is Virt3, curve is 1-to-1, scale is 0 and offset is 0. Save it. The output of Virt3 is -100 to +100 with 0 being centre. You can check this in the Transmitter Menu/Channel Monitor Virt3 bar graph display.

4. Go into the mixer menu and find the Ch11 mixer and set this: mixer type is complex, Mixers is 1, Page is 1, Switch is none, Mux is replace, Src is Virt3, Curve is 1-to-1, scale is 100, offest is 0, and set NO TRIM instead of TRIM. You can also set limits in the Ch11 first menu if required.

5. Check the radio output in the Transmitter Menu/Channel Monitor, you should see the CH11 output following the trim switch.


## Current Experimental Features and DEVIATIONS FROM STOCK SILVERWARE 

 - Target Selection:  define your board type and hardware settings are automatically selected for E011 (OLD STYLE), Bwhoop, bwhoop pro, E011c, beta fpv lite, and ALIENWHOOP ZER0.  
 - Radio Type Selection:  Renamed aux channels as chan_5 through chan_10 and proper mapping is now controlled by defining your transmitter type.  Simply select devo, multi (for taranis or other multimodule), or stock (for toy tx) and assign the features you want to chan_#.  Your aux channel mapping will be adjusted in software to match your radio channel numbering.
 - Racemode:  flight mode with leveling on roll, acro on pitch, and yaw axis rotates about gravity vector.  Can be activated on an aux channel when in level mode.
 - Racemode Horizon: same as above with horizon on roll.
 - Horizon: leveling when upright, will flip or roll.
 - Kalman Gyro Filter:  adjustable gyro filter that's very similar to a 1st order filter but to me feels a little faster and a little weaker.  You decide...
 - Kalman Motor Filter:  adjustable motor output filter.  Same evaluation as the gyro version.
 - Idle up and Arming on seperate aux channels:  idle speed is also adjustable.  Paired with mix increase throttle feature it behaves like airmode
 - Arming safety (when arming feature is turned on)  - Props will not spin when arming unless your throttle is below THROTTLE_SAFETY variable value.  Attempting to arm with throttle above this limit will rapid flash the led to indicate a safety override condition.
 - MIX_INCREASE_THROTTLE_3 will now also automatically not activate during pre-takeoff staging after arming untill throttle has crossed the THROTTLE_SAFETY value to improve on ground behavior prior to takeoff.
 - Sticks Deadband:  adjustable deadband for transmitter inputs to compensate for gimbals that don't perfectly center
 - Motor Filter Frequencies:  motor filters are adjustable by a frequency instead of a decimal value.
 - AUTOBIND Has been added.  Set a fixed ID in your TX.  Stick gesture comand up-up-up to turn on autobind. Quad will flash once.  Stick gesture Down-Down-Down will save your fixed ID.  Unplug battery and plug in to verify.  No more power cycling TX to bind.
 - Voltage Telemetry Correction Factor has been added to make it easy to fine tune your telemetry voltage to read exactly accurate.  To use this feature - measure the voltage of a freshly charged pack with a trusted multimeter.  Make note of this value.  Then connect the battery and make note of the reported voltage by telemetry.  Now go back to config and update the reported telemetry voltage and actual battery voltage values.  Compile and reflash.  Your reported telemetry voltage will be automatically rescaled withing the adc calculation and will now be displayed perfectly.
 - Buzzer Code has been changed to combine automatic buzzer features and aux channel buzzer features into one define.  Enabeling this feature with with the aux channel set to CHAN_OFF will only activate all automatic buzzer features (like beeping on low battery or failsafe).  Changing the CHAN_OFF to CHAN_# (you pick your aux #) will allow both automatic buzzer functions and the ability to turn on the buzzer with your selected aux channel.
 - JOELUCID's YAW FIX has been added to the code on a define in config.  Feel free to turn it on and off and test the "feel" of this fix for yourself.
 - SBUS receiver code has been updated to include missing channels
 - STICK_TRAVEL_CHECK feature has been added to give the ability to make sure your sticks are reaching 100% throws in software.  This feature when activated will override the function of the stick gesture aux channel.  RIGHT-RIGHT-DOWN will enter a mode where the throttle is inactive and the led will rapid blink when you move the sticks to 100% throws.  If you do not see a rapid led blink at stick extents - scale up your throws in your transmitter untill you do.  LEFT-LEFT-DOWN will exit this mode.  Suggestion to DEVO 7e users - you may want to define this check once, then reflash after checking with the feature off so that you can use the stick gesture channel as a supliment for other features since you only have 2 switches.
 - EXPO VALUES have now been split into a seperate variable for each individual axis AND a seperate expo set is available for acro mode and leveled modes.  This gives the the pilot the ability to run high expo in acro with fast rotational rates for freestyle but also switch into level mode with a completely different set of expo variables where more linear controls may be desired for racing.
 - Alienwhoop Zer0 target has been added and work continues to optomize its feature set.  This target was origionaly intended for SBUS receiver but now supports SPI based XN297L receiver modules.  One can be found inside most toy transmitters and removed to become an affordable but capable micro receiver with telemetry.  Selecting any of the Bayang protocols will automatically populate code for the SPI receiver option - alternatively selecting SBUS will deactivate SPI and enable the SBUS appropriate code.
 - Additional notes have been added to the releases page for Alienwhoop ZER0 firmware including new switchable features via stick gestures.  Please read these notes for further instructions.

 ## Bikemike's Blheli 4way Interface Support(from Betaflight) 15.03.18 (Yets)

This commit enables flashing and configuring Blheli using the Silverware FC. **May not work with all ESCs**

 - FC must have MOSFETS and motor pulldown resistors removed
 - In hardware.h file comment in either define USE_ESC_DRIVER or define USE_DSHOT_DRIVER_BETA coupled with define USE_SERIAL_4WAY_BLHELI_INTERFACE
 - Quad must be onground and not armed
 - Connect TX/RX of a usb TTL adapter/Arduino to DAT/CLK and GND to GND in Blheli suite, select the 4way-IF (D) interface
 - Connect and configure/flash ESCs as usual
 - After disconnecting, normal FC operation should resume
 
 Credit to Bikemike https://www.rcgroups.com/forums/showpost.php?p=38505698&postcount=11950

_Easiest way to find me for feedback & discussion is here https://community.micro-motor-warehouse.com/t/notfastenuf-e011-bwhoop-silverware-fork/5501?u=notfastenuf_

_end NFE notes_

## SilverWare - BoldClash BWHOOP B-03 version

_Also works with B03 Pro_

Currently does not account for centered throttle! ( no altitude hold ) It uses normal throttle, low = motors off. That means it should be used with Devo / multimodule or another tx.

Programming connector is a Microjst 1.25 pitch connector. Don't wire positive to st-link as you may overcharge the battery if connected or damage the st-link.

Programming instructions ( uses St-link Utility program ):
https://www.rcgroups.com/forums/showthread.php?2876797-Boldclash-bwhoop-B-03-opensource-firmware

Compiling instructions ( uses Keil uVision IDE):
https://www.rcgroups.com/forums/showthread.php?2877480-Compilation-instructions-for-silverware#post37391059

### Level / acro mode change
By default "gestures" are used to change modes, move the stick *left-left-down* for acro mode , and *right-right-down* for level mode.

### Pid gestures and save
Pid gestures allow the pilot to change the acro mode pids by a percentage, and such tune the quadcopter without a computer. The new pids can be saved so that they will be restored after the quad is power cycled.The new pids will remain active if saved, until the pid values in file pid.c are changed. If the values are not changed, flashing the quad will not erase the pids unless the erase command is manually issued when programming.

*See also*
http://sirdomsen.diskstation.me/dokuwiki/doku.php?id=pidgesture

### Accel calibration / pid save
The gesture for accel calibration is down - down - down. If pids have been changed using the respective gestures since the last powerup or save, the pids will be saved instead.

### Telemetry
DeviationTx and multimodule+taranis can support telemetry, this requires no changes from the defaults on the quad. For devo, when selecting the Bayang protocol, hit Enter to see options, and enable telemetry there. Telemetry currently contains received number of data and telemetry packets, and 2 voltages, battery raw voltage and compensated voltage ( against voltage drop )

For multimodule, you need to add telemetry ( as an option ) to the bayang protocol in the protocol table ( configuration file ). Note the telemetry protocol won't work with stock quads.

*See also*
http://sirdomsen.diskstation.me/dokuwiki/doku.php?id=telemetry

### Android App telemetry
The Android app "SilverVISE" by SilverAG (not me) is able to receive telemetry from the quad using BLE packets. To use, the app protocol should be set in the quadcopter. The app will also show the pids.

*More information*
http://sirdomsen.diskstation.me/dokuwiki/doku.php?id=silvervise

### Linux/gcc version
The gcc version compiles close to 16k, and may need turning off features in order to make it fit. It's also possible to flash up to 32K with changes. Read __install.md__ for additional information. 

The boldclash settings may need changes to work with gcc well. Turn off the software lpf filters except the last 2, the loop time is longer, at 1400, which affects the frequency of other soft lpf filters. You could set loop time to 1500 but it may not be needed.

### Wiki
http://sirdomsen.diskstation.me/dokuwiki/doku.php?id=start

### 03.19
* Blheli passthrough support added for ESCs
* Buzzer can be enabled on a channel/switch with BUZZER_ENABLES_CHAN_## (credit: Markus Gritsch)
* Added RX_BAYANG_PROTOCOL_TELEMETRY_AUTOBIND define to ensure all protocol builds would compile due to the nature of the autobind feature

### 01.18
* 2 new D term filters, 1st and 2nd order with custom frequency
* improved led flash timing
* the throttle smooth feature is gone 
* nrf24 support added, bayang protocol + telemetry
* softi2c support for 1 pullup only ( e011 )

### 29.08.17
* moved flash save to 31k
* added 2 looptime independent soft lpf
* added lowerthrottlemix3 from h8
* added motor filter 2 replacing original,much better performance
* pid save has own led flash now
* cleanup of unused features: headless and some other


### xx.06.17
* pid gestures - pids can be changed by gestures at the field
* pid save - new pids are saved to flash by the d-d-d gesture

### 02.05.17
* level pid is tuned more aggressive
* added filter between level pid and  acro pid
* fixed issue where "Overclock" option broke level mode (i2c) - overclock can be used on the bwhoop now
* removed level mode I term - this was not usually used
* minor cleanup and efficiency
* GCC autovdrop now functional
* LVC throttle lowering disabled by default just in case it malfunctions

### initial changes

* autovdrop improved, and better compensation
* new measured motor curve at 24K pwm
* added a new way of lowering throttle below a certain voltage
* lvc now flashes below an "uncompensated" voltage, too, just in case
