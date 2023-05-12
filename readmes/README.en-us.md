<h1 align="center">Chessey</h1>
<p align="center">Command line chess with C</p>

![Chessey](https://github.com/nadjiel/chessey/assets/97067805/a4b6ac74-50ef-47f7-998f-4e881adc4315)

## ♟️ About
Chessy was a project made in an informal GameJam between my brother [@DaveJosef](https://github.com/DaveJosef) and I.

The competition had a limit of approximately 1 month and the games had to attend to the conditions of being black and white and not having any sounds.

This was the first game I made. At the time I was coursing the first period of the System Analysis and Development university, where I was learning the C language.

The game is made to be played by two players in the same computer, the player 1 controlling the white pieces (represented by the number 1), and the player 2, the black pieces (represented by the number 2).

## 🎮 How to play
At the start of the game it is asked that the player's nicknames are informed, first player 1's, then player 2's. After that, the match starts.

To interact with the game, it is used an address system - arrangements of a letter and a number (for example **a2**, where the first black Pawn from left to right starts, or **e8**, where starts the white King), so to commit the pieces' moves, the players will be asked the start and finish addresses of the pieces they want to move.

To represent the pieces, the game uses two characters: a letter and a number. The letter indicates what is that piece and the number shows which player is its owner: the white or black player.

Following are the meanings of the letters that represent the pieces:

- **p**: Pawn;
- **t**: Rook;
- **c**: Knight;
- **b**: Bishop;
- **D**: Queen;
- **R**: King.

That way, as an example, we can say that the piece **D1** is the white Queen and the piece **c2** is one of the black Knights.

Furthermore, to represent empty squares in the board, two underlines are used.

### Special events
Next are described some special events that may occur in the game and how you can deal with them:

- En-passant capture: to accomplish an en passant capture, you just have to move the captor to the square where the Pawn that would be captured skipped by moving two consecutive squares.

- Castling: in order to castle, the King must be moved to squares in the direction of the desired Rook. This way the Rook will automatically commit the rest of the move.

- Promotion: When a Pawn arrives its opposite side of the board, it will be able to be promoted. The game will ask its player to what piece it wants to promote. At this moment the player in question must answer with **t** (Rook), **c** (Knight), **b** (Bishop) or **D** (Queen), that are the pieces available for the promotion.

## 👇 Installing
If you want to try the game, you can download the 64bit version for the Windows OS via the executable in the project releases here on Github (the [release v2.0.0](https://github.com/nadjiel/chessey/releases/tag/v2.0.0) is the full version), or you can compile the source code yourself if you are not using Windows.

## ✍️ Author
This project was developed with ❤️ by [@Nadjiel](https://github.com/nadjiel)

## [Leia em português](https://github.com/nadjiel/chessey/blob/main/README.md)