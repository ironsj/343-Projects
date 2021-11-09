package kotlinGameOfLife
import java.io.File
import java.util.*


class GameOfLife {
    var rows = 0
    var cols = 0
    var grid = arrayOf<Array<Int>>()

    fun loadGrid(file: String){
        val scanner = Scanner(File(file))
        rows = scanner.nextInt()
        cols = scanner.nextInt()


        for(i in 0 until rows) {
            var array = arrayOf<Int>()
            for (j in 0 until cols) {
                array += 0
            }
            grid += array
        }


        while(scanner.hasNextInt()){
            for(i in 0 until rows)
                for(j in 0 until cols)
                    grid[i][j] = scanner.nextInt()
        }
    }

    fun saveGrid(file: String){
        var data = "$rows $cols "
        for(i in 0 until rows){
            for(j in 0 until cols){
                data += grid[i][j].toString() + " "
            }
        }
        data += "\n"
        File(file).writeText(data)
    }

    fun mutate(){
        var temp = arrayOf<Array<Int>>()
        for(i in 0 until rows) {
            var array = arrayOf<Int>()
            for (j in 0 until cols) {
                array += 0
            }
            temp += array
        }

        for(i in 0 until rows) {
            for (j in 0 until cols) {
                temp[i][j] = grid[i][j]
            }
        }

        for(i in 0 until rows){
            for(j in 0 until cols){
                if(getNeighbors(i, j) < 2 && grid[i][j] == 1){
                    temp[i][j] = 0;
                }
                else if((getNeighbors(i, j) == 3 || getNeighbors(i, j) == 2) && grid[i][j] == 1){
                    temp[i][j] = 1;
                }
                else if(getNeighbors(i, j) > 3 && grid[i][j] == 1){
                    temp[i][j] = 0;
                }
                if((this.getNeighbors(i, j) == 3) && grid[i][j] == 0){
                    temp[i][j] = 1;
                }
            }
        }

        grid = temp
    }

    fun getNeighbors(i: Int, j: Int): Int {
        var neighbors = 0
        var newRow: Int
        var newCol: Int

        for(surrRow in -1 until 2){
            for(surrCol in -1 until 2){
                if(surrRow != 0 || surrCol != 0){
                    newRow = i + surrRow
                    newCol = j + surrCol
                    if(newRow in 0 until rows && newCol in 0 until cols && grid[newRow][newCol] == 1){
                        neighbors++
                    }
                }
            }
        }
        return neighbors
    }

    override fun toString(): String {
        var str: String = ""
        for(i in 0 until rows) {
            for (j in 0 until cols) {
                if (grid[i][j] == 0)
                    str += " . "
                else
                    str += " X "
            }
            str += "\n"
        }
        return str
    }


}