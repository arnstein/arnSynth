# arnSynth

If you wish to make a synthesizer from scratch, you must first create the universe.  
...but since we already have the universe, I'll just focus on the synthesizer part.  
Having the flu lately and sitting inside being bored, I wanted to see if it is easy to create a basic software sound synthesizer.
The formula for a sine wave is A * sin(2pifT), where A is the amplitude, f is the frequency of the note, and T is the period of one wave. 
Does this mean that by just using the math library in C we can generate sound?  
Well yes, but actually no. Even though we can easily generate the values for the sine wave with the math library, we also need to communicate with the sound card to actually generate sound.
There are many ways to do this, but since I wanted this to be easy, I decided to use SDL2. Click [here](https://youtu.be/MeMPCSqQ-34) to see a presentation from one of the core developers of SDL2, Ryan Gordon, about game development with SDL2.
