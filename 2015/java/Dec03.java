import java.awt.Point;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

/**
 * @author Erik Andersson on 2015-12-11.
 */
public class Dec03 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println(part1(test));
                System.out.println(part2(test));
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/03.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/03.txt\" to where you run it." +
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
        return makeTrip(row.toCharArray()).size();
    }
    private static int part2(String row) {
        String santaOrders = "";
        String roboOrders = "";
        for(int i=0;i<row.length();i++){
            if(i%2==0)
                santaOrders += row.charAt(i);
            else
                roboOrders += row.charAt(i);
        }
        HashMap<Point,Integer> houses = makeTrip(santaOrders.toCharArray());
        houses.putAll(makeTrip(roboOrders.toCharArray()));
        return houses.size();
    }
    private static HashMap<Point,Integer> makeTrip(char[] moves){
        HashMap<Point,Integer> houses = new HashMap<>();
        int x=0,y=0;
        houses.put(new Point(x,y),1);

        for(char c:moves) {
            switch (c) {
                case '^':
                    y++;
                    break;
                case 'v':
                    y--;
                    break;
                case '>':
                    x++;
                    break;
                case '<':
                    x--;
                    break;
            }
            int presents = 0;
            if(houses.get(new Point(x,y))!=null)
                presents = houses.get(new Point(x,y));
            houses.put(new Point(x,y),presents+1);
        }
        return houses;
    }
}
