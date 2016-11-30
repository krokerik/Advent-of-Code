import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-13.
 */
public class Dec13 {
    private static class Person{
        public final String name;
        public HashMap<String,Integer> opinions;
        public Person(String name){
            opinions = new HashMap<>();
            this.name = name;
        }
        public void setOpinion(String p,int opinion){
            opinions.put(p,opinion);
        }
        public int getOpinion(String name){
            return opinions.get(name);
        }
    }
    private static HashMap<String,Person> people = new HashMap<>();
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                part1(test);
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/13.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/13.txt\" to where you run it." +
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
        System.out.println(getBest(people));
        part2("Erik");
        System.out.println(getBest(people));

    }

    private static int getBest(HashMap<String, Person> people) {
        ArrayList<Person> peopleList = new ArrayList<>(people.values());
        ArrayList<ArrayList<Person>> permutations = permutation(0,peopleList);
        int best = Integer.MIN_VALUE;
        ArrayList<Person> bestP = null;
        for(ArrayList<Person> p:permutations){
            int score = evaluate(p);
            if(score>best){
                best = score;
                bestP = p;
            }
        }
        print(bestP);
        return best;
    }
    private static ArrayList<ArrayList<Person>> permutation(int pos, ArrayList<Person> start){
        ArrayList<ArrayList<Person>> permutations = new ArrayList<>();
        if(start.size()-pos==1) {
            permutations.add(start);
        } else {
            for (int i = pos; i < start.size(); i++) {
                start = swap(start,pos,i);
                permutations.addAll(permutation(pos+1, start));
                start = swap(start,pos,i);

            }
        }
        return permutations;
    }
    private static void print(ArrayList<Person> p){
        for(Person person:p)
            System.out.print(person.name + " ");
        System.out.println();
    }
    private static ArrayList<Person> swap(ArrayList<Person> arr, int pos1, int pos2){
        ArrayList<Person> tempArr = new ArrayList<>();
        tempArr.addAll(arr);
        if(pos1!=pos2) {
            Person temp = tempArr.get(pos1);
            tempArr.set(pos1, tempArr.get(pos2));
            tempArr.set(pos2, temp);
        }
        return tempArr;
    }
    private static int evaluate(ArrayList<Person> people){
        int tot=0;
        int len=people.size();
        for(int i=0; i<len; i++){
            int lIndex=i-1,rIndex=i+1;
            lIndex = lIndex<0?len-1:lIndex;
            rIndex = rIndex>=len?0:rIndex;
            String lName = people.get(lIndex).name;
            String rName = people.get(rIndex).name;
            tot += people.get(i).getOpinion(lName);
            tot += people.get(i).getOpinion(rName);
        }
        return tot;
    }

    private static int part1(String row) {
        Pattern p = Pattern.compile("([A-Z])\\w+|[0-9]+|(lose|gain)");
        Matcher m = p.matcher(row);
        String aName = "";
        String mood = "";
        int amount = 0;
        String bName = "";
        if(m.find())
            aName = m.group();
        if(m.find())
            mood = m.group();
        if(m.find())
            amount = Integer.valueOf(m.group());
        if(m.find())
            bName = m.group();

        Person a;
        people.getOrDefault(aName,new Person(aName));
        if(!people.containsKey(aName)) {
            a = new Person(aName);
            people.put(aName, a);
        } else a = people.get(aName);

        switch (mood){
            case "gain":
                a.setOpinion(bName,amount);
                break;
            case "lose":
                a.setOpinion(bName,amount*-1);
        }

        return amount;
    }
    private static int part2(String row) {
        Person me = new Person(row);
        ArrayList<Person> p = new ArrayList<>(people.values());
        for(Person person:p){
            person.setOpinion(row,0);
            me.setOpinion(person.name,0);
        }
        people.put(row,me);
        return 0;
    }
}
