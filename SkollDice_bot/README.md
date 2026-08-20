# SkollDice bot for Discord

The SkollDice script was used for the creation of its official bot for Discord. The code is open source to let people experiment and fork the original idea. If you ever create a newer version of this bot, feel free to contact me in any sort of way possible; I will be glad to see the code created by me for other projects.

---

## 📑 Table of Contents

1. [Command of the Bot](#command-of-the-bot)
2. [How to Host Yourself](#how-to-host-yourself)
3. [How to Invite on Your Server](#how-to-invite-on-your-server)

---

## Command of the Bot

The bot has only one command and the syntax is pretty simple:

`/roll 1D4 1d6` or `/roll 1D4,1D6 7`

or `/r`

The bot isn't case-sensitive and doesn't check for a specific order for the input dice. The idea is to make the command as uncomplicated and fast to use as possible.

## How to Host Yourself

If you want to modify and customize the bot, the only solution is to host it yourself. Here are some important points to remember in order to do that:

- Set up a `.env` file with the following structure:
  ```env
  DISCORD_TOKEN=Your_token

- Use a VM like Oracle's free one to efficiently have a 24/7 bot.

- Pay attention to error handling on message sends because they're asynchronous to the response code.

## How to Invite on Your Server

If you don't want to host it yourself, no problem! I personally took a free virtual machine from Oracle to host the bot 24/7 as long as RAM is available. You can add the bot using the link presented on the main page or more simply...

Then go to Discord and click on the button that says "Add bot to the server", or if you prefer, you can search for it on Discord bot directories.
