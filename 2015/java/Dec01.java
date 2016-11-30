import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author Erik Andersson on 2015-12-11.
 */
public class Dec01 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println(part1(test));
                System.out.println(part2(test));
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/01.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/01.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br.ready()) {
                    String row = br.readLine();
                    System.out.println(part1(row));
                    System.out.println(part2(row));
                    System.out.println();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    public static int part1(String input){
        int floor = 0;
        for(char c:input.toCharArray()){
            if(c==')')
                floor--;
            else if(c=='(')
                floor++;
        }
        return floor;
    }
    public static int part2(String input){
        int index = 0;
        for(index=0;index<input.length();index++){
            if(part1(input.substring(0,index))==-1)
                break;
        }
        return index;
    }
}
