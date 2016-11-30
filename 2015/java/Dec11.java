import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author Erik Andersson on 2015-12-12.
 */
public class Dec11 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println(part1(test));
                System.out.println(part2(test));
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/11.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/11.txt\" to where you run it." +
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
    private static String part1(String row) {
        do
            row = increment(row);
        while(!validate(row));
        return row;
    }

    private static boolean validate(String pw) {
        boolean inARow = false,noConfusing = false,containPair = false;
        for(int i=0;i<pw.length();i++){
            char temp = pw.charAt(i);
            if(i+2<pw.length() && pw.charAt(i+1)==temp+1 && pw.charAt(i+2)==temp+2) {
                inARow = true;
            }
        }
        if(!pw.matches(".*(i|o|l).*"))
            noConfusing=true;
        if(pw.matches(".*([a-z])\\1.*([a-z])\\2.*"))
            containPair=true;
        return inARow && noConfusing && containPair;
    }

    private static String increment(String pw) {
        int pos=pw.length()-1,pre=pos+1;
        char[] pwArr = pw.toCharArray();
        while(pos>=0 && pos<pwArr.length && pre!=pos && pwArr[pos]<='z'){
            pre = pos;
            if(pwArr[pos]=='z')
                pwArr[pos--] = 'a';
            else
                pwArr[pos]++;
        }
        return String.valueOf(pwArr);
    }

    private static String part2(String row) {
        return part1(part1(row));
    }
}
