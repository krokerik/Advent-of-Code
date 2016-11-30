import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-15.
 */
public class Dec15 {
    private static class Ingredient{
        private final int capacity;
        private final int durability;
        private final int flavor;
        private final int texture;
        private final int calories;

        public Ingredient(int capacity, int durability, int flavor, int texture, int calories){
            this.capacity = capacity;
            this.durability = durability;
            this.flavor = flavor;
            this.texture = texture;
            this.calories = calories;
        }
        
        public int getCapacity() {
            return capacity;
        }

        public int getDurability() {
            return durability;
        }

        public int getFlavor() {
            return flavor;
        }

        public int getTexture() {
            return texture;
        }

        public int getCalories() {
            return calories;
        }
    }
    
    private static ArrayList<Ingredient> ingredients;
    public static void main(String[] args) {
        ingredients = new ArrayList<>();
        if(args.length>0)
            for(String test:args) {
                parse(test);
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/15.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/15.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    parse(row);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        System.out.println(part1());
        System.out.println(part2());
        
    }

    private static String part1() {
        int[] amount = {0,0,0,0};
        int best = 0;
        int[] bestAmount = amount.clone();
        for (int a = 0; a < 100; a++) {
            amount[0] = a;
            for (int b = 0; b < 100 - a; b++) {
                amount[1] = b;
                for (int c = 0; c < 100 - a - b; c++) {
                    amount[2] = c;
                    int d = 100 - a - b - c;
                    amount[3] = d;
                    int temp  = evaluate(amount);
                    if(temp>best) {
                        best = temp;
                        bestAmount = amount.clone();
                    }
                }
            }
        }
        String s = "";
        for (int i:bestAmount)
            s += i+" ";
        return s+"\t"+best;
    }

    private static String part2() {
        int[] amount = {0,0,0,0};
        int best = 0;
        int[] bestAmount = amount.clone();
        for (int a = 0; a < 100; a++) {
            amount[0] = a;
            for (int b = 0; b < 100 - a; b++) {
                amount[1] = b;
                for (int c = 0; c < 100 - a - b; c++) {
                    amount[2] = c;
                    int d = 100 - a - b - c;
                    amount[3] = d;
                    int temp  = evaluate(amount);
                    if(calCount(amount)==500 & temp>best) {
                        best = temp;
                        bestAmount = amount.clone();
                    }
                }
            }
        }
        String s = "";
        for (int i:bestAmount)
            s += i+" ";
        return s+"\t"+best;
    }

    private static int calCount(int[] amounts) {
        int calories=0;
        for (int i = 0; i < 4; i++) {
            calories += ingredients.get(i).getCalories()*amounts[i];
        }
        return calories;
    }

    private static void parse(String row) {
        Pattern p = Pattern.compile("-?\\d");
        Matcher m = p.matcher(row);
        int capacity=0, durability=0, flavor=0, texture=0, calories=0;
        if (m.find())
            capacity = Integer.parseInt(m.group());
        if (m.find())
            durability = Integer.parseInt(m.group());
        if (m.find())
            flavor = Integer.parseInt(m.group());
        if (m.find())
            texture = Integer.parseInt(m.group());
        if (m.find())
            calories = Integer.parseInt(m.group());
        ingredients.add(new Ingredient(capacity,durability,flavor,texture,calories));
    }
    private static int evaluate(int[] amounts){
        int totCapacity=0, totDurability=0, totFlavor=0, totTexture=0;
        for (int i = 0; i < 4; i++) {
            totCapacity += ingredients.get(i).getCapacity()*amounts[i];
            totDurability += ingredients.get(i).getDurability()*amounts[i];
            totFlavor += ingredients.get(i).getFlavor()*amounts[i];
            totTexture += ingredients.get(i).getTexture()*amounts[i];
        }

        return Math.max(totCapacity,0)*Math.max(totDurability,0)*
                Math.max(totFlavor,0)*Math.max(totTexture,0);
    }
}