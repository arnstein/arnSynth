# arnSynth

If you wish to make a synthesizer from scratch, you must first create the universe.  
...but since we already have the universe, I'll just focus on the synthesizer part.  


### Step 1: Generating the sine wave
Having the flu lately and sitting inside being bored, I wanted to see if it is easy to create a basic software sound synthesizer.
The formula for a sine wave is A * sin(2pifT), where A is the amplitude, f is the frequency of the note, and T is the period of one wave. 
In my program I have implemented this by having a variable called sine_step_size which is assigned as  2 * 3.14159 * note * octave / sample_rate.
This value is re-calculated every time a new note or octave is chosen by the user. In the sin() function I then pass sine_value which is a double that starts at 0 and is incremented by sine_step_size.
Does this mean that by just using the math library in C I have generated sound?  
Well yes, but actually no. Even though we can easily generate the values for the sine wave with the math library, we also need to communicate with the sound card to actually generate sound.

### Step 2: Getting sound out of your speakers

There are many ways to do this, but since I wanted this to be easy, I decided to use SDL2 (Simple DirectMedia Layer). [Here](https://youtu.be/MeMPCSqQ-34) you can see a presentation about game development with SDL2 from one of the core developers of SDL2. SDL does all the hard and scary stuff for you, so you can easily create audio and video!
By initializing an audio interface and defining a callback function that is called when the audio device needs more data. This function sends the sine wave values to the audio device.

### Step 3: Handle input

SDL2 also has an easy way to handle keyboard input. In the main loop we look for keyboard events. By mapping different frequencies to different keys on the keyboard, we give the user the feeling of playing a synthesizer. Cool!

### Step 4: ??? Profit? No, display the keyboard.

SDL2 allows you to easily create a window and render text. I render something that looks like a keyboard, showing the keyboard bindings.

### Step 5: Rock and/or roll!

You are now in control of the synthesizer! 
