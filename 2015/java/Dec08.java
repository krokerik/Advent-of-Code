import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author Erik Andersson on 2015-12-12.
 */
public class Dec08 {
    public static void main(String[] args) {
        int numChars1 = 0;
        int numChars2 = 0;
        if(args.length>0)
            for(String test:args) {
                numChars1+=part1(test);
                numChars2+=part2(test);
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/08.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/08.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    numChars1+=part1(row);
                    numChars2+=part2(row);

                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        System.out.println(numChars1);
        System.out.println(numChars2);
    }
    private static int part1(String row) {
        String out = row.substring(1,row.length()-1);
        out = out.replaceAll("\\\\x[0-9a-f]{2}",".");
        out = out.replaceAll("\\\\.",".");
        return row.length()-out.length();
    }
    private static int part2(String row) {
        String out = "\"";
        for(char c: row.toCharArray()){
            if(c == '\\')
                out+="\\\\";
            else if(c == '\"')
                out+="\\\"";
            else
                out+=c;
        }
        out += "\"";
        return out.length()-row.length();
    }
}
