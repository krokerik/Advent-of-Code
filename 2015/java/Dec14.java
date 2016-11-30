import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-14
 */
public class Dec14 {
    private static class Reindeer{
        private final String name;
        private final int speed;
        private final int runTime;
        private final int rest;
        private int distance;
        private int restStart;
        private int runStart;
        private int score;
        private boolean flying = true;
        public Reindeer(String name, int speed, int runTime, int rest){
            this.name = name;
            this.speed = speed;
            this.runTime = runTime;
            this.rest = rest;
            this.distance = 0;
            this.restStart = 0;
            this.runStart = 0;
            this.score = 0;
        }
        public int tick(){
            if(flying) {
                distance += speed;
                runStart++;
                if(runStart>=runTime) {
                    flying = false;
                    runStart=0;
                }
            }else{
                restStart++;
                if(restStart>=rest) {
                    flying = true;
                    restStart=0;
                }
            }
            return getDistance();
        }
        public int getScore() {
            return score;
        }
        public void incScore() {
            this.score++;
        }
        public int getDistance(){
            return distance;
        }
    }
    private static ArrayList<Reindeer> reindeers = new ArrayList<>();
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                part1(test);
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/14.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/14.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    part1(row);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        for (int i = 0; i < 2503; i++) {
            int best = Integer.MIN_VALUE;
            for (Reindeer reindeer : reindeers) {
                reindeer.tick();
                if(reindeer.getDistance()>best)
                    best = reindeer.getDistance();
            }
            for(Reindeer r:reindeers)
                if(r.getDistance()==best)
                    r.incScore();
        }
        for (Reindeer reindeer:reindeers)
            System.out.println(reindeer.name+" "+reindeer.getDistance()+" "+reindeer.getScore());
    }
    private static void part1(String row){
        String reg1 = "\\d+";
        String reg2 = "([A-Z])\\w+";
        Pattern p = Pattern.compile(reg1);
        Matcher m = p.matcher(row);
        int speed = 0;
        int time = 0;
        int rest = 0;
        String name = "";
        if(m.find())
            speed = Integer.parseInt(m.group());
        if(m.find())
            time = Integer.parseInt(m.group());
        if(m.find())
            rest = Integer.parseInt(m.group());

        p = Pattern.compile(reg2);
        m = p.matcher(row);
        if(m.find())
            name = m.group();

        reindeers.add(new Reindeer(name,speed,time,rest));
    }
}
