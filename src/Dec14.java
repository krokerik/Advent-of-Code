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
        private int time;
        public Reindeer(String name, int speed, int runTime, int rest){
            this.name = name;
            this.speed = speed;
            this.runTime = runTime;
            this.rest = rest;
            this.distance = 0;
            this.restStart = rest*-1;
            this.time = 0;
        }
        public int tick(){
            time++;
            if(time-restStart>rest)
                distance+=speed;
            if(time-restStart-restStart>runTime)
                restStart = time;

            return getDistance();
        }
        public int getDistance(){
            return distance;
        }
    }
    String reg1 = "\\d+";
    String reg2 = "([A-Z])\\w+";
}
