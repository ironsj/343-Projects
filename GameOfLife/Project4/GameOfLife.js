'use strict';

/**
 *  Game of Life
 *  Author(s): Jake Irons
 */

/*
 * The "fs" module provides an API for interacting with the file system
 */
const fs = require('fs');

// Class that represents Game of Life
class GameOfLife {

    // Constructor that sets up instance variables with default values
    constructor() {
        this.grid = [];
        this.rows = 0;
        this.cols = 0;
    }

    // Reads data from the file, instantiates the grid, and loads the
    // grid with data from file. Sets this.grid, this.rows, and
    // this.cols instance variables for later use.
    loadGrid(file) {
        let data = fs.readFileSync(file, 'utf8');
        let tokens = data.split(' ');

        this.rows = parseInt(tokens.shift());
        this.cols = parseInt(tokens.shift());
        this.grid = new Array(this.rows);
        for (let i = 0; i < this.rows; i++) {
            this.grid[i] = new Array(this.cols);
            this.grid[i].fill(0);
        }

        for (let i = 0; i < this.rows; i++) {
        	for(let j = 0; j < this.cols; j++){
        		this.grid[i][j] = parseInt(tokens.shift());
		}
        }

    }

    // Saves the current grid values to the file specified.
    saveGrid(file) {
        let data = this.rows + ' ' + this.cols + ' ';

        // TO DO: append the values in this.grid to data
        for (let i = 0; i < this.rows; i++) {
        	for(let j = 0; j < this.cols; j++){
        		data += this.grid[i][j] + ' ';
		}
        }

        data += '\n';
        fs.writeFileSync(file, data);
    }

    // Mutates the grid to next generation
    mutate() {
        // make a copy of grid and fill it with zeros
        let temp = new Array(this.rows);
        for (let i = 0; i < this.rows; i++) {
            temp[i] = new Array(this.cols);
            temp[i].fill(0);
        }

        // TO DO: using values in this.grid, set temp grid to next generation
	for (let i = 0; i < this.rows; i++) {
        	for(let j = 0; j < this.cols; j++){
        		temp[i][j] = this.grid[i][j];
		}
        }
        
        for(let i = 0; i < this.rows; i++){
		for(let j = 0; j < this.cols; j++){
			if((this.getNeighbors(i, j) < 2) && (this.grid[i][j] == '1')){
				temp[i][j] = 0;
			}
			else if(((this.getNeighbors(i, j) == 3) || (this.getNeighbors(i, j) == 2)) && (this.grid[i][j] === 1)){
				temp[i][j] = 1;
			}
			else if((this.getNeighbors(i, j) > 3) && (this.grid[i][j] === 1)){
				temp[i][j] = 0;
			}
			if((this.getNeighbors(i, j) == 3) && (this.grid[i][j] === 0)){
				temp[i][j] = 1;
			}
		}
	}

        // set this.grid to temp grid
        this.grid = temp;
    }

    // Returns the number of neighbors for cell at this.grid[i][j]
    getNeighbors(i, j) {
        let neighbors = 0;

        // TO DO: determine number of neighbors of cell at this.grid[i][j]
        var newRow;
	var newCol;
	for(let surrRow = -1; surrRow < 2; surrRow++){
		for(let surrCol = -1; surrCol < 2; surrCol++){
			if(surrRow != 0 || surrCol != 0){
				newRow = i + surrRow;
				newCol = j + surrCol;
				if((newRow >=0 && newRow < this.rows) && (newCol >= 0 && newCol < this.cols)){
					if(this.grid[newRow][newCol] === 1){
						neighbors++;
					}
				} 
			}
		}
	}
        
        return neighbors;
    }

    // Returns a string representation of the grid (for display purposes)
    toString() {
        let str = '\n';
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.cols; j++) {
                if (this.grid[i][j] === 0) {
                    str += ' . ';
                } else {
                    str += ' X ';
                }
            }
            str += "\n";
        }
        return str;
    }
}

module.exports = GameOfLife;
