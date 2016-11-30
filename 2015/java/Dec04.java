import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * @author Erik Andersson on 2015-12-11.
 */
public class Dec04 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println(part1(test));
                System.out.println(part2(test));
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/04.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/04.txt\" to where you run it." +
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
        return numIterationsToRepeatingZeroes(row,5);
    }
    private static int part2(String row) {
        return numIterationsToRepeatingZeroes(row,6);
    }
    private static int numIterationsToRepeatingZeroes(String row,int numZeroes){
        MessageDigest alg = null;
        try {
            alg = MessageDigest.getInstance("MD5");
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        String zeroes = "";
        for(int i=0; i<numZeroes; i++){
            zeroes+="0";
        }
        String hex = "";
        int num = 1;
        if(alg!=null)
            while(!hex.startsWith(zeroes)){
                hex = "";
                String tempRow = row+num++;
                byte[] digested = alg.digest(tempRow.getBytes());
                for (byte b : digested) {
                    String tempHex = Integer.toHexString(0xFF & b);
                    if (tempHex.length() == 1)
                        hex += "0";
                    hex += tempHex;

                }
            }

        return num-1;
    }
}
