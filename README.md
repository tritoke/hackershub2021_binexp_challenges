# hackershub2021_binexp_challenges

I developed these challenges for the CTF part of Hacker's Hub 2021.
An event put on by The University of Manchester's Crackchester Cybersecurity Society.
They are intended to be a beginner level introduction to binary exploitation, with very little assumed knowledge.

### Running the challenges

You can run them locally by just running the `chal` binary in every challenge directory.

You can run them "remotely" using docker:
1. Build the docker container with `docker build -t challenge_<challenge name> .`.
2. Run the image with `docker run --rm -p 1337:1337 challenge_<challenge name>`

They can then be interacted with over port 1337.

### Known issues
The local and remote solutions are not always the same for each challenge.
I sadly only managed to find a work around for this after the CTF was over.

But it does help to be aware of the issue for other CTFs.
Essentially, sometimes the stack will not balance on an exploit due to 16-byte alignment requirements for some instructions.
This can be fixed by adding a `ret gadget` to the exploit chain before calling the function that is breaking.
A `ret gadget` is just a pointer to a `ret` instruction.
