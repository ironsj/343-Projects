#
# Othello Game Class
# Author(s): Jake Irons
#

class Othello

    # Constants
    WHITE = 'W'
    BLACK = 'B'
    EMPTY = '-'
    TIE = 'T'

    # Creates getter methods for instance variables @size, @turn, @disc,
    # @p1Disc, and @p2Disc
    attr_reader  :size, :turn, :disc, :p1Disc, :p2Disc

    # Constructs and initializes the board of given size
    def initialize(size, startPlayer, discColor)
        # validate arguments
        if size < 4 || size > 8 || size % 2 != 0
            raise ArgumentError.new('Invalid value for board size.')
        end
        if startPlayer < 1 || startPlayer > 2
            raise ArgumentError.new('Invalid value for player number.')
        end
        if discColor != WHITE && discColor != BLACK
            raise ArgumentError.new('Invalid value for disc.');
        end

        # set instance variables
        @board = []
        @size = size
        @turn = startPlayer
        @disc = discColor

        # set two more instance variables @p1Disc and @p2Disc
        if @turn == 1
            @p1Disc = @disc
            @p2Disc = @disc == WHITE ? BLACK : WHITE
        else
            @p2Disc = @disc
            @p1Disc = @disc == WHITE ? BLACK : WHITE;
        end

        # create the grid (as array of arrays)
        @board = Array.new(@size)
        for i in (0...@board.length)
            @board[i] = Array.new(@size)
            @board[i].fill(0)
        end

        # initialize the grid
        initializeBoard()
    end

    # Initializes the board with start configuration of discs
    def initializeBoard()
	for i in (0...@size)
		for j in (0...@size)
			@board[i][j] = '-'
		end
	end
	
	@board[@size/2 -1][@size/2 - 1] = 'B'
	@board[@size/2][@size/2] = 'B'
	@board[@size/2 - 1][@size/2] = 'W'
	@board[@size/2][@size/2 - 1] = 'W'	

    end

    # Returns true if placing the disc of current player at row,col is valid;
    # else returns false
    def isValidMove(row, col)
        return isValidMoveForDisc(row, col, @disc)
    end

    # Returns true if placing the specified disc at row,col is valid;
    # else returns false
    def isValidMoveForDisc(row, col, disc)
	other_disc = ''
	if disc == 'B'
		other_disc = 'W'
	else
		other_disc = 'B'
	end
	
	if @board[row][col] == '-'
		for surrRow in -1..1 do
			for surrCol in -1..1 do
				if surrRow != 0 or surrCol != 0
					new_row = row + surrRow
					new_col = col + surrCol
					if (new_row >= 0 and new_row < @size) and (new_col >= 0 and new_col < @size) and @board[new_row][new_col] == other_disc
						while (new_row >= 0 and new_row < @size) and (new_col >= 0 and new_col < @size) and @board[new_row][new_col] == other_disc do
							new_row = new_row + surrRow
							new_col = new_col + surrCol
							if (new_row >= 0 and new_row < @size) and (new_col >= 0 and new_col < @size) and @board[new_row][new_col] == disc
								return true
							end
						end
					end
				end
			end
		end
	end
	
    	return false
    end

    # Places the disc of current player at row,col and flips the
    # opponent discs as needed
    def placeDiscAt(row, col)
        if (!isValidMove(row, col))
            return
        end

        # place the current player's disc at row,col
        @board[row][col] = @disc
	other_disc = ''
	if disc == 'B'
		other_disc = 'W'
	else
		other_disc = 'B'
	end
	
	for surrRow in -1..1 do
		for surrCol in -1..1 do
			if surrRow != 0 or surrCol != 0
				new_row = row + surrRow
				new_col = col + surrCol
				if (new_row >= 0 and new_row < @size) and (new_col >= 0 and new_col < @size) and @board[new_row][new_col] == other_disc
					square_count = 1
					while (new_row >= 0 and new_row < @size) and (new_col >= 0 and new_col < @size) and @board[new_row][new_col] == other_disc do
						square_count += 1
						new_row = new_row + surrRow
						new_col = new_col + surrCol
						if (new_row >= 0 and new_row < @size) and (new_col >= 0 and new_col < @size) and @board[new_row][new_col] == disc
							end_count = square_count - 1
							until end_count < 1 do
								@board[new_row - (surrRow * end_count)][new_col - (surrCol * end_count)] = @disc
								end_count -=  1
							end
							break
						end
					end
				end
			end
		end
	end
        

        # DO NOT DELETE - prepares for next turn if game is not over
        if (!isGameOver())
            prepareNextTurn();
        end
    end

    # Sets @turn and @disc instance variables for next player
    def prepareNextTurn()
        if @turn == 1
            @turn = 2
        else
            @turn = 1
        end
        if @disc == WHITE
            @disc = BLACK
        else
            @disc = WHITE
        end
    end

    # Returns true if a valid move for current player is available;
    # else returns false
    def isValidMoveAvailable()
        isValidMoveAvailableForDisc(@disc)
    end

    # Returns true if a valid move for the specified disc is available;
    # else returns false
    def isValidMoveAvailableForDisc(disc)

        for i in 0...@size do
        	for j in 0...@size do
        		if isValidMoveForDisc(i, j, disc)
        			return true
        		end
        	end
        end

        # DO NOT DELETE - if control reaches this statement, then a valid move is not available
        return false;
    end

    # Returns true if the board is fully occupied with discs; else returns false
    def isBoardFull()

        for i in 0...@size do
        	for j in 0...@size do
        		if @board[i][j] == '-'
        			return false
        		end
        	end
        end

        return true
    end

    # Returns true if either the board is full or a valid move is not available
    # for either disc
    def isGameOver()
        return isBoardFull() ||
                    (!isValidMoveAvailableForDisc(WHITE) &&
                                !isValidMoveAvailableForDisc(BLACK))
    end

    # If there is a winner, it returns Othello::WHITE or Othello::BLACK.
    # In case of a tie, it returns Othello::TIE
    def checkWinner()

        black_count = 0
        white_count = 0
        if !isGameOver
        	return
        else
        	for i in 0...@size do
        		for j in 0...@size do
        			if @board[i][j] == 'B'
        				black_count += 1
        			elsif @board[i][j] == 'W'
        				white_count += 1
        			end
        		end
        	end
        end
        
        if white_count > black_count
        	return Othello::WHITE
        elsif black_count > white_count
        	return Othello::BLACK
        end
        
        return Othello::TIE
    end

    # Returns a string representation of the board
    def to_s()
        str = "\n  "
        for i in (0...@size)
            str << (i+1).to_s + ' '
        end
        str << "\n";
        for i in (0...@size)
            str << (i+1).to_s + ' ';
            str << @board[i].join(' ') + "\n";
        end
        return str;
    end

end
