import kotlinGameOfLife.GameOfLife
import kotlin.system.exitProcess

fun main(args: Array<String>){
    if(args.size != 1){
        println("Wrong number of arguments to program. This program requires a filename as argument.")
        println("Usage: ./driver filename")
        println("Example: ./driver beacon.gol")
        exitProcess(1);
    }
    println(args[0])

    val life = GameOfLife()

    life.loadGrid(args[0])

    println("Beginning with grid size " + life.rows + "," + life.cols)
    println(life.toString())

    while(true){
        print("Press q to quit, i to iterate, w to save to file, or any other key to move to next generation: ")
        var input = readLine()!!
        input = input.trim().toLowerCase()

        when(input){
            "q" -> {
                println("Exiting program")
                exitProcess(1)
            }
            "n" -> {
                life.mutate()
                println(life.toString())
            }
            "i" -> {
                print("How many iterations? ")
                val number = Integer.valueOf(readLine())
                for(i in 0 until number)
                    life.mutate()
                    println(life.toString())
            }
            "w" -> {
                print("Enter a filename: ")
                val filename = readLine()!!
                life.saveGrid(filename.trim())
                println("Grid saved to file $filename\n")
            }
            else -> {
                life.mutate()
                println(life.toString())
            }
        }

    }


}