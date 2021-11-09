#
#  Game of Life class
#
#  Author(s): Jake Irons
#
class GameOfLife

    # Creates getter methods for instance variables @rows and @cols
    attr_reader  :rows, :cols

    # Constructor that initializes instance variables with default values
    def initialize()
        @grid = []
        @rows = 0
        @cols = 0
    end

    # Reads data from the file, instantiates the grid, and loads the
    # grid with data from file. Sets @grid, @rows, and
    # @cols instance variables for later use.
    def loadGrid(file)
        data = IO.read(file)
        tokens = data.strip.split(' ')

        @rows = tokens.shift.to_i
        @cols = tokens.shift.to_i
        @grid = Array.new(@rows)
        for i in (0...@rows)
            @grid[i] = Array.new(@cols)
            @grid[i].fill(0)
        end
        
        for i in 0...@rows
        	for j in 0...@cols
        		@grid[i][j] = tokens.shift.to_i
        	end
        end

    end

    # Saves the current grid values to the file specified
    def saveGrid(file)
        data = @rows.to_s + ' ' + @cols.to_s + ' '

        for i in 0...@rows
        	for j in 0...@cols
        		data += @grid[i][j].to_s + ' '
        	end
        end

        data += "\n"
        IO.write(file, data)
    end

    # Mutates the grid to next generation
    def mutate()
        # make a copy of grid and fill it with zeros
        temp = Array.new(@rows)
        for i in (0...@rows)
            temp[i] = Array.new(@cols)
            temp[i].fill(0)
        end

        for i in 0...@rows
        	for j in 0...@cols
        		temp[i][j] = @grid[i][j]
        	end
        end
        
        for i in 0...@rows
        	for j in 0...@cols
        		if getNeighbors(i, j) < 2 and @grid[i][j] == 1
        			temp[i][j] = 0
        		elsif (getNeighbors(i,j) == 3 or getNeighbors(i,j) == 2) and @grid[i][j] == 1
        			temp[i][j] = 1
        		elsif getNeighbors(i, j) > 3 and @grid[i][j] == 1
        			temp[i][j] = 0
        		end
        		if getNeighbors(i, j) == 3 and @grid[i][j] == 0
        			temp[i][j] = 1
        		end
        	end
        end

        # DO NOE DELETE: set @grid to temp grid
        @grid = temp
    end

    # Returns the number of neighbors for cell at @grid[i][j]
    def getNeighbors(i, j)
        neighbors = 0

        for surr_row in -1...2
        	for surr_col in -1...2
        		if surr_row != 0 or surr_col != 0
        			new_row = i + surr_row
        			new_col = j + surr_col
        			if (new_row >=0 and new_row < @rows) and (new_col >= 0 and new_col < @cols) and @grid[new_row][new_col] == 1
        				neighbors += 1
        			end
        		end
        	end
        end

        # DO NOT DELETE THE LINE BELOW
        neighbors
    end

    # Returns a string representation of GameOfLife object
    def to_s
        str = "\n"
        for i in 0...@rows
            for j in 0...@cols
                if @grid[i][j] == 0
                    str += ' . '
                else
                    str += ' X '
                end
            end
            str += "\n"
        end
        str
    end

end
