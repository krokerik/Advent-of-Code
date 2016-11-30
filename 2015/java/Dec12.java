import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Stack;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-12.
 */
public class Dec12 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println(part1(test));
                System.out.println(part2(test));
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/12.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/12.txt\" to where you run it." +
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
        int nums = 0;
        Pattern p = Pattern.compile("-?[0-9]+");
        Matcher m = p.matcher(row);
        while (m.find())
            nums += Integer.parseInt(m.group());

        return nums;
    }
    private static int part2(String row) {
        Stack<Integer> indexes = new Stack<>();
        char[] fuckJson = row.toCharArray();
        String temp;
        for(int i=0; i<fuckJson.length; i++){
            if(fuckJson[i]=='{' || fuckJson[i]=='[')
                indexes.push(i);
            else if(fuckJson[i]=='}') {
                StringBuilder sb = new StringBuilder();
                for(int j=indexes.peek();j<i+1;j++){
                    sb.append(fuckJson[j]);
                }
                temp = sb.toString();
                Pattern p = Pattern.compile(":\"red\"");
                Matcher m = p.matcher(temp);
                if(m.find()){
                    for(int j=indexes.peek();j<i+1;j++){
                        fuckJson[j] = '_';
                    }
                }
                indexes.pop();
            }
            else if(row.charAt(i)==']'){
                indexes.pop();
            }
        }

        return part1(String.valueOf(fuckJson));
    }
}
