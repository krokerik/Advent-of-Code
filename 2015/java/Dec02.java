import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author Erik Andersson on 2015-12-11.
 */
public class Dec02 {
    public static void main(String[] args) {
        int totalPaper = 0;
        int totalRibbon = 0;
        if(args.length>0)
            for(String test:args) {
                totalPaper += part1(test);
                totalRibbon += part2(test);
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/02.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/02.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br.ready()) {
                    String row = br.readLine();
                    totalPaper += part1(row);
                    totalRibbon += part2(row);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        System.out.println(totalPaper);
        System.out.println(totalRibbon);
    }
    private static int part1(String row) {
        int l = Integer.parseInt(row.split("x")[0]);
        int w = Integer.parseInt(row.split("x")[1]);
        int h = Integer.parseInt(row.split("x")[2]);
        return part1(l,w,h);
    }
    private static int part1(int l,int w, int h){
        int smallest = Integer.MAX_VALUE;
        int total = 0;

        int temp = 2*l*w;
        total += temp;
        smallest = temp<smallest?temp:smallest;

        temp = 2*w*h;
        total += temp;
        smallest = temp<smallest?temp:smallest;

        temp = 2*h*l;
        total += temp;
        smallest = temp<smallest?temp:smallest;

        total += smallest/2;

        return total;
    }
    private static int part2(String row) {
        int l = Integer.parseInt(row.split("x")[0]);
        int w = Integer.parseInt(row.split("x")[1]);
        int h = Integer.parseInt(row.split("x")[2]);
        return part2(l,w,h);
    }
    private static int part2(int l,int w, int h){
        int smallest = Integer.MAX_VALUE;

        int temp = perimeter(l,w);
        smallest = temp<smallest?temp:smallest;

        temp = perimeter(w,h);
        smallest = temp<smallest?temp:smallest;

        temp = perimeter(h,l);
        smallest = temp<smallest?temp:smallest;

        return smallest+volume(l,w,h);
    }
    private static int perimeter(int x,int y){
        return 2*x+2*y;
    }
    private static int volume(int l, int w, int h){
        return l*w*h;
    }
}
