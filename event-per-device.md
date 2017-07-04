# WACOM bamboo pen tablet

## Wacom Bamboo Craft Pen

### Supporting info

bus     0x3
vendor  0x56a
product 0xd2
version 0x100

### events

- EV_SYN 0
- EV_KEY 1
  - BTN_TOOL_PEN    32O
  - BTN_TOOL_RUBBER 321
  - BTN_TOUCH       330
  - BTN_STYLUS      331
  - BTN_STYLUS2     332
- EV_ABS 3
  - ABS_X           0 (0 14720 fuzz 4)
  - ABS_Y           1 (0 9200 fuzz 4)
  - ABS_PRESSURE    24 (0 1023)
  - ABS_DISTANCE    25 (0 31 fuzz 1)


## Wacom Bamboo Craft Finger

### Supporting info

bus     0x3
vendor  0x56a
product 0xd2
version 0x100

### events

- EV_SYN 0
- EV_KEY 1
  - BTN_TOOL_FINGER     325
  - BTN_TOUCH           330
  - BTN_TOUCH_DOUBLETAP 333
- EV_ABS 3
  - ABS_X               0 (0 15360 reso 128)
  - ABS_Y               1 (0 10240 reso 128)
  - ABS_MT_SLOT         47
  - ABS_MT_POSITION_X   53 (0 15360 reso 128)
  - ABS_MT_POSITION_Y   54 (0 10240 reso 128)
  - ABS_MT_TRACKING_ID  57 (0 65535)


## Wacom Bamboo Craft Pad

### Supporting info

bus     0x3
vendor  0x56a
product 0xd2
version 0x100

### events

- EV_SYN 0
- EV_KEY 1
  - BTN_LEFT            272
  - BTN_RIGHT           273
  - BTN_FORWARD         277
  - BTN_BACK            278
  - BTN_STYLUS          331
- EV_ABS 3
  - ABS_X               0 (0 15360 reso 128)
  - ABS_Y               1 (0 10240 reso 128)

## ELAN0732 multi touch screen

### Supporting info

bus     0x18
vendor  0x4f3
product 0x249e
version 0x100

### Events


- EV_SYN 0
- EV_KEY 1
  - BTN_TOUCH           330
- EV_ABS 3
  - ABS_X               0 (0 2832 reso 10)
  - ABS_Y               1 (0 1584 reso 10)
  - ABS_MT_SLOT         47 (0 9)
  - ABS_MT_TOUCH_MAJOR  48 (0 255) 
  - ABS_MT_TOUCH_MINOR  49 (0 255) 
  - ABS_MT_ORIENTATION  52 (0 1)
  - ABS_MT_POSITION_X   53 (0 2832 reso 10)
  - ABS_MT_POSITION_Y   54 (0 1584 reso 10)
  - ABS_MT_TOOL_X       60 (0 2832 reso 10)
  - ABS_MT_TOOL_Y       61 (0 1584 reso 10)
  - ABS_MT_TRACKING_ID  57 (0 65535)
