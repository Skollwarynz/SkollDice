# Truly random dice generator

This project is a dice generator for RPG games that actually implements full randomic generation of the number used as results of the dices. 

The idea is to use the entropy inside the computer of phone of the user to produce fully randomical numbers. The code is open source to let each programmer and Master to control and eventually issue any sorts of problem. 

The idea was to fix the problem of both physical and digital dices. This can help all player to fully enjoy the randomization of dices. 

For any suggestion or expansion you can open an issue request and if useful I will add the feature. 



## Architecture

The program uses two methods to produces normally distrubuted fully random numbers: 

- Simple linear method 

- Complex linear method

The two methods are explained in the section 5.1 and 5.2 of the [NIST Special Publication 800-90A](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90Ar1.pdf) so for the full explanation you can read the document directly. 

The idea is to produce a single numbers (a 1 dice throw) using the Simple linear method because recommended for it. When the program produces multiple dice trhow the generator will use automatically the complex linear method to produce better results. 



Each byte is read by /dev/urandom beacause it produces fully cryptograpically secure randomized number is produced. As we generate each byte of the number we secure the full randomization throught the use of the linear method. This simple setup of app hides profound and difficult research about the true randomization on application used for computer science or little programs. 
