import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-12.
 */
public class Dec10 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println(part1(test));
                System.out.println(part2(test));
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/10.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/10.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    System.out.println(part1(row));
                    System.out.println(part2(row));
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    private static int part1(String row) {
        String out = row;
        long start = System.currentTimeMillis();
        for(int i=0;i<40;i++){
            out = lookAndSay(out);
            System.out.println(i+1+" "+(System.currentTimeMillis()-start)/1000.0+"s");
        }
        return out.length();
    }
    private static int part2(String row) {
        String out = row;
        long start = System.currentTimeMillis();
        for(int i=0;i<50;i++){
            out = lookAndSay(out);
            System.out.println(i+1+" "+(System.currentTimeMillis()-start)/1000.0+"s");
        }
        return out.length();
    }
    private static String lookAndSay(String input){
        Pattern p = Pattern.compile("([0-9])(\\1*)?");
        Matcher m = p.matcher(input);
        StringBuilder sb = new StringBuilder();
        while (m.find()){
            sb.append(String.valueOf(m.group().length())).append(m.group().charAt(0));
        }
        return sb.toString();
    }
}
