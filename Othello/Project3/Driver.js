'use strict';


/**
 * Requires "readline-sync" package for synchronous I/O
 * Package installation: npm install readline-sync
 * 		(run this command inside the project folder; requires node.js)
 * Documentation: https://www.npmjs.com/package/readline-sync
 */
const readlineSync = require('readline-sync');

const Othello = require('./Othello');

// Main driver for the program
function main() {
	// info: process.argv array stores command-line arguments
	if (process.argv.length !== 5) {
		console.log("Incorrect number of arguments to the program");
		console.log("Usage: node Main.js boardsize startplayernbr disccolor");
		console.log("Example: node Main.js 6 1 B");
		process.exit(1);
	}

	// extract board size, start player, and disc color from command-line arguments
	let size = parseInt(process.argv[2]);
	let player = parseInt(process.argv[3]);
	let disc = process.argv[4].toUpperCase();

	if (size < 4 || size > 8 || size % 2 !== 0 || player < 1 || player > 2 || (disc !== Othello.WHITE && disc !== Othello.BLACK)) {
		console.log("Invalid arguments to the program");
		process.exit(1);
	}

	let game = new Othello(size, player, disc);

	console.log("<<<<< Welcome to the game of Othello >>>>>");
	console.log("Player 1: " + game.p1Disc + "   Player 2: " + game.p2Disc);
	console.log("Player " + player + " starts the game...");

	let row, col, line, tokens;

	while (!game.isGameOver()) {
		console.log(game.toString());

		if (!game.isValidMoveAvailable()) {
			console.log("No valid moves available for player " + game.turn + "(" + game.disc + "). You lose your turn.");
			game.prepareNextTurn();
		} else {
			while (true) {
				line = readlineSync.question("Turn> Player " + game.turn + "(" + game.disc + ") - Enter location to place your disc (row col): ");
				tokens = line.split(' ');
				row = parseInt(tokens[0]);
				col = parseInt(tokens[1]);
				if (row < 1 || row > game.size || col < 1 || col > game.size) {
					console.log("Sorry, invalid input. Try again.");
					continue;
				}
				row--;	// adjust it for zero-indexed board
				col--;  // adjust it for zero-indexed board
				if (!game.isValidMove(row,col)) {
					console.log("Sorry, that is not a valid move. Try again.");
					continue;
				}
				break;
			}
			game.placeDiscAt(row,col);
		}
	}

	// print the final board and display winner or tie information
	console.log(game.toString());
	let winner = game.checkWinner();
	if (winner === game.p1Disc) {
		console.log("Game is over. The winner is Player 1(" + winner + ").");
	} else if (winner === game.p2Disc) {
		console.log("Game is over. The winner is Player 2(" + winner + ").");
	} else {
		console.log("Game is over. No winner.");
	}
}

// Invoke the driver
main()
