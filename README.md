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

There are many ways to do this, but since I wanted this to be easy, I decided to use SDL2. [Here](https://youtu.be/MeMPCSqQ-34) you can see a presentation about game development with SDL2 from one of the core developers of SDL2. 
