import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-11.
 */
public class Dec06 {
    private static int[][] lights1 = new int[1000][1000];
    private static int[][] lights2 = new int[1000][1000];
    public static void main(String[] args) {

        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader("../input/06.txt"));
            while (br.ready()) {
                String row = br.readLine();
                part1(row);
                part2(row);
            }
        } catch (FileNotFoundException e) {
            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
            try {
                String row = in.readLine();
                while (row != null) {
                    part1(row);
                    part2(row);
                    row = in.readLine();
                }
            } catch (IOException e1) {
                e1.printStackTrace();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }


        System.out.println(numLit());
        System.out.println(totBright());
    }

    private static int part1(String row) {
        int x1,y1,x2,y2;
        Pattern p = Pattern.compile("[0-9]+,[0-9]+");
        Matcher m = p.matcher(row);
        if(!m.find())
            return 0;
        String temp = m.group();
        x1 = Integer.parseInt(temp.split(",")[0]);
        y1 = Integer.parseInt(temp.split(",")[1]);
        if(!m.find())
            return 0;
        temp = m.group();
        x2 = Integer.parseInt(temp.split(",")[0]);
        y2 = Integer.parseInt(temp.split(",")[1]);
        m = Pattern.compile("(turn on|toggle|turn off)").matcher(row);
        if(!m.find())
            return 0;
        temp = m.group();
        switch (temp) {
            case "turn on":
                turnOn(x1, y1, x2, y2);
                break;
            case "turn off":
                turnOff(x1, y1, x2, y2);
                break;
            case "toggle":
                toggle(x1, y1, x2, y2);
                break;
        }
        return numLit();
    }

    private static void toggle(int x1, int y1, int x2, int y2) {
        for(int x=x1; x<=x2; x++)
            for (int y=y1; y<=y2; y++)
                lights1[x][y] = lights1[x][y]==1?0:1;
    }

    private static void turnOff(int x1, int y1, int x2, int y2) {
        for(int x=x1; x<=x2; x++)
            for (int y=y1; y<=y2; y++)
                lights1[x][y] = 0;

    }

    private static void turnOn(int x1, int y1, int x2, int y2) {
        for(int x=x1; x<=x2; x++)
            for (int y=y1; y<=y2; y++)
                lights1[x][y] = 1;

    }

    private static int part2(String row) {
        int x1,y1,x2,y2;
        Pattern p = Pattern.compile("[0-9]+,[0-9]+");
        Matcher m = p.matcher(row);
        if(!m.find())
            return 0;
        String temp = m.group();
        x1 = Integer.parseInt(temp.split(",")[0]);
        y1 = Integer.parseInt(temp.split(",")[1]);
        if(!m.find())
            return 0;
        temp = m.group();
        x2 = Integer.parseInt(temp.split(",")[0]);
        y2 = Integer.parseInt(temp.split(",")[1]);
        m = Pattern.compile("(turn on|toggle|turn off)").matcher(row);
        if(!m.find())
            return 0;
        temp = m.group();
        switch (temp) {
            case "turn on":
                turnOn2(x1, y1, x2, y2);
                break;
            case "turn off":
                turnOff2(x1, y1, x2, y2);
                break;
            case "toggle":
                toggle2(x1, y1, x2, y2);
                break;
        }
        return totBright();
    }

    private static void turnOn2(int x1, int y1, int x2, int y2) {
        for(int x=x1; x<=x2; x++)
            for (int y=y1; y<=y2; y++)
                lights2[x][y] += 1;

    }
    private static void turnOff2(int x1, int y1, int x2, int y2) {
        for(int x=x1; x<=x2; x++)
            for (int y=y1; y<=y2; y++)
                lights2[x][y] = lights2[x][y]>0?lights2[x][y]-1:0;

    }
    private static void toggle2(int x1, int y1, int x2, int y2) {
        for(int x=x1; x<=x2; x++)
            for (int y=y1; y<=y2; y++)
                lights2[x][y] += 2;
    }

    private static int numLit(){
        int num=0;
        for(int[] row: lights1)
            for(int light:row)
                if(light==1)
                    num++;
        return num;
    }
    private static int totBright() {
        int num=0;
        for(int[] row: lights2)
            for(int light:row)
                num+=light;
        return num;
    }
}
