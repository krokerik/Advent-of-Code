import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Erik Andersson on 2015-12-12.
 */
public class Dec07 {
    static HashMap<String,Short> wires = new HashMap<>();
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                part1(test);
                part2(test);
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/07.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"input/07.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    part1(row);
                    part2(row);

                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        for(String wire:wires.keySet()) {
            if(wires.get(wire)<0)
                System.out.println(wire + ": " + wires.get(wire)+Short.MAX_VALUE);
        }
    }
    private static int part1(String row) {
        if(row.matches("[a-z0-9]+ -> [a-z]+")) {
            String wire = row.split(" -> ")[0];

            Short value = 0;
            if(wires.containsKey(wire))
                value = wires.get(wire);
            else if(wire.matches("[0-9]+"))
                value = Short.parseShort(wire);

            String output = row.split(" -> ")[1];
            wires.put(output,value);
        } else if(row.matches("[a-z0-9]+ (OR|AND|RSHIFT|LSHIFT) [a-z0-9]+ -> [a-z]+")) {
            String wire1 = row.split(" (OR|AND|RSHIFT|LSHIFT) ")[0];
            String wire2 = row.split(" (OR|AND|RSHIFT|LSHIFT) ")[1].split(" -> ")[0];
            String output = row.split(" -> ")[1];
            String type = row.split(" ?[a-z0-9]+ ?")[1];
            Short lval = 0;
            Short rval = 0;
            if(wires.containsKey(wire1))
                lval = wires.get(wire1);
            else if(wire1.matches("[0-9]+"))
                lval = Short.parseShort(wire1);

            if(wires.containsKey(wire2))
                rval = wires.get(wire2);
            else if(wire2.matches("[0-9]+"))
                rval = Short.parseShort(wire2);
            if(type.equals("AND"))
                wires.put(output, (short) (lval & rval));
            else if(type.equals("OR"))
                wires.put(output, (short) (lval | rval));
            if(type.equals("LSHIFT"))
                wires.put(output,(short)(lval<<rval));
            else if(type.equals("RSHIFT"))
                wires.put(output,(short)(lval>>>rval));
        } else if(row.matches("NOT [a-z]+ -> [a-z]+")) {
            String wire = row.split(" ")[1];
            String output = row.split("-> ")[1];
            Short val = 0;
            if(wires.containsKey(wire))
                val = wires.get(wire);
            wires.put(output, (short) ~val);
        } else {
            System.out.println(row);
        }
        return 0;
    }
    private static int part2(String row) {
        return 0;
    }
}
