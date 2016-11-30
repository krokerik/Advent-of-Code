import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-11.
 */
public class Dec05 {
    public static void main(String[] args) {
        int numNice1 = 0;
        int numNice2 = 0;
        if(args.length>0)
            for(String test:args) {
                if(part1(test)==1)
                    numNice1++;
                if(part2(test)==1)
                    numNice2++;
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/05.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/05.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    if(part1(row)==1)
                        numNice1++;
                    if(part2(row)==1)
                        numNice2++;

                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        System.out.println(numNice1);
        System.out.println(numNice2);
    }
    private static int part1(String row) {

        return isNice1(row)?1:0;
    }
    private static int part2(String row) {
        return isNice2(row)?1:0;
    }
    private static boolean isNice1(String word){
        Pattern p = Pattern.compile("[aeiou].*[aeiou].*[aeiou]");
        Matcher m = p.matcher(word);
        if(!m.find())
            return false;

        p = Pattern.compile("(.)\\1");
        m = p.matcher(word);
        if(!m.find())
            return false;

        p = Pattern.compile("(ab)|(cd)|(pq)|(xy)");
        m = p.matcher(word);
        return !m.find();

    }
    private static boolean isNice2(String word){
        Pattern p = Pattern.compile("(..).*\\1");
        Matcher m = p.matcher(word);
        if(!m.find())
            return false;

        p = Pattern.compile("(.).\\1");
        m = p.matcher(word);
        return m.find();

    }
}
