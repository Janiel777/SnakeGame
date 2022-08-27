# OpenFrameworks Audiovisualizer Specs
In this project, you and your partner are expected to essentially complete the code you are given. The features you must add to this project are listed below, and divided by phases. Typically speaking, the features described in Phase 1 are easier than those in Phase 2, and those in Phase 2 are easier than those in Phase 3. 

## Phase 1: A WarmUp
- Change the Background Color in each mode.
- Change the Color of the Rectangle in mode 1 to be random.
    - Hint, use ofRandom().
- Pressing the "a" key "pauses" the visualizer and 'a' "unpauses" the visualizer.
    - In other words, when the draw method is called, the rectangle shapes will not change unless the visualizer is unpaused.

## Phase 2: Special Keys
- Using certain keys will change songs
   - Songs are available in the folder bin/data. If you are to add a song, it must be added in this folder, as it is where OpenFrameworks reads resources.
    - An example of this would perhaps be making it so that when the "d" key is pressed, "geesebeat.wav" is played. 
    - This must be done for four songs. 
- Using the "=" key will raise the volume and the "-" key will lower it. 
    - In order to achieve this, 1 should be considered the max value, and 0 the minimum, as the setVolume() method accepts double numbers such as 0.2.
- There must be 64 bars in the "Rectangle Height Visualizer". 
    - These bars must be nect to each other, left-to-right and must correspond to values in the "amplitudes" vector.
    - All 64 bars must fit, no matter the width of the screen. (To see an example, see the specs document).
- Implement the "Rectangle Width Visualizer"
    - This mode is very similar to the aforementioned "Rectangle Height Visualizer," only it is rotated either way 90 degrees. (To see an example, see the specs document).

## Phase 3: Full Features
- Pressing the "r" key will record all keys pressed afterwards until it is pressed again.
    - You must have an indicator that appears when this feature is active. 
- Pressing the "t" key will loop through the recorded keys and perform any associated actions at fixed intervals.
    - While this is happening, the program must not listen to any keys being pressed unless the process is cancelled by pressing "t" again.

# Key Advice
The best way to tackle this project is to become comfortable with the code base so that you feel confident enough to add to it. If you feel stuck or are having any issues ith the project, be it understanding it or partner issues, make sure to contact a TA as soon as possible. We encourage you to have fun with this and truly make it your own!