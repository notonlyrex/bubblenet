# BubbleNet

The LubJam 2025 game, the part of GGJ2025, where the main theme was "bubble".
This time the game was made for the [M5 StickC
Plus2](https://docs.m5stack.com/en/core/M5StickC%20PLUS2), an ESP32-powered IoT
device, equipped with a 1.13" TFT screen and a button.

The game is requiring the Wi-Fi module, screen and a button.

The core play is related to hacking the Wi-Fi network with a set of three
micro-games: shooting into the target, making the bubble stay in size and
solving the cipher aka sorting numbers.

Game is in Japanese, for fun.

## Techs

Game is built using PlatformIO and M5Unified, M5GFX and M5StickCPlus2 library,
in C++ language, from scratch. This is also why there are mostly circles and
other simple graphics, not the actual bubbles.

## Theme and Diversifiers

The theme for GGJ2025 was "bubble", so everything is presented in the form of a
circle (bubble) -- starting from Wi-Fi network signal rate, then we are shooting
bubble into the target, make the bubble larger and finally sort the numbers by
swapping two adjacent ones... which is known as "bubble sort".

Diversifiers included:

* Sharing is caring (Sponsored by GitHub) -- share the source code for your
  submission in a public GitHub repository and list the URL on your submission
  page,
* Outside the box -- the game is played using a non-standard controller or
  other methods to interact with the game -- this game is played using a
  non-standard device as well as including Wi-Fi signal strength as one of the
  methods of interaction,
* Contextual -- the game uses no more than two buttons, but the buttons perform
  a wide range of different functions that change based on the
  player/character's current scenario in the game -- BubbleNet is using only one
  button which is used for different things in different microgames,
* Anthology -- Instead of making one game, make at least three micro-games that
  are thematically linked to create a small collection -- technically all the
  actual play in the BubbleNet are three simple micro-games.

## Plot

BubbleNet is strictly related to the Rex games lore -- the device the game is
played on is in a form of a watch -- similar to the watch the Norma, Rex's
companion, is uploading herself in Rex4EverLaughter.

While never explicitely said in the game, we as the player are helping another
AI, *Sensation*, to prevent Earth's wireless networks from being hacked during
the first minutes of the alien invasion which kickstarted the Rex series.

## Video

[![Watch the video](https://img.youtube.com/vi/zSpkuEf4skE/maxresdefault.jpg)](https://youtu.be/zSpkuEf4skE)

## License

Licensed under CC-BY-SA 4.0.
