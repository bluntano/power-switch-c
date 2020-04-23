# power-switch-c
 🖥️ A remote power switch for my PC 🖥️
 
 Generally speaking, I wouldn't advise you to use that web server code outside local network, as it has its own disadvantages like, no POST methods and not very secure.

## What makes it so special?
The remote web server is written in C, which I've never done before: writing a web server in C language.

I learned making a web server in C from [Jacob Sorber](https://people.cs.clemson.edu/~jsorber/)'s video ["Program your own web server in C. (sockets)"](https://www.youtube.com/watch?v=esXw4bdaZkc)

## Does it work?
Yes, it actually does! There are some disadvantages but, I got the main part to work.

### Disadvantages
- I haven't got POST method to work. It can process GET methods.
- The code may be filled with unoptimized code that I'm kind of afraid to touch (you know, don't fix it if it ain't broke)

## Hardware?
No, it won't work on Windows. In fact, it won't work on regular computers.

I used Raspberry Pi Zero W, its GPIO pinout, and a 5V relay. The reason why it only works on Raspberry Pi device is that, it has `lwiringPi` library that the code requires. That library is for GPIO communication.

## How does one compile it, or install it?

Simple:

```bash
make
sudo ./power-switch
```

## Was it worth it?
I think so. I haven't touched C language much but, I got to experience it a bit more. So that was cool to make.

#
Bye-bye, fellas!
