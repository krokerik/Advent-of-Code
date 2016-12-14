import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.regex.*;

/**
 * @author Erik Andersson on 2016-12-14.
 */
public class Dec14 {
	private static Hashtable<String, String> cache;

    public static void main(String[] args) {
		cache = new Hashtable<String,String>();
        if(args.length>0)
            for(String test:args) {
                System.out.println("\rpart1: \u001B[32m"+getIndex(test,64)+"\u001B[0m");
                System.out.println("\rpart2: \u001B[32m"+getStretchedIndex(test,64,2016)+"\u001B[0m");
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/14.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"../input/14.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    System.out.println("\rpart1: \u001B[32m"+getIndex(row,64)+"\u001B[0m");
                    System.out.println("\rpart2: \u001B[32m"+getStretchedIndex(row,64,2017)+"\u001B[0m");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    private static int getIndex(String base, Integer index) {
		int i = 0, res = 0;
		String hash;
		Pattern threeInARow = Pattern.compile("(.)\\1\\1");
		Pattern fiveInARow  = Pattern.compile("(.)\\1\\1\\1\\1");
		TreeMap<Integer, String> unconfirmed = new TreeMap<Integer,String>();
		TreeSet<Integer> indices = new TreeSet<Integer>();
		do {
			String id = base + i;
			hash = getHash(id,1);
			Matcher three = threeInARow.matcher(hash);
			Matcher five  = fiveInARow.matcher(hash);
			if(five.find()){
				String temp = five.group().substring(2);
				if(unconfirmed.containsValue(temp)){
					Iterator<Map.Entry<Integer,String>> itr = unconfirmed.entrySet().iterator();
					while(itr.hasNext()){
						Map.Entry<Integer,String> entry = itr.next();
						if(temp.equals(entry.getValue())){
							indices.add(entry.getKey());
							itr.remove();
							System.out.print("\r"+indices.size()+"/"+index);
							System.out.flush();
						}
					}
				}
			}
			if(three.find() && indices.size()<index){
				unconfirmed.put(i,three.group());
			}
			i++;
			for(int j=0; j<i-1000; j++){
				unconfirmed.remove(j);
			}
		} while(indices.size()<index || unconfirmed.size()>0);
		int j=0;
		for(Integer key:indices){
			if(j==index-1){
				res = key;
				break;
			}
			j++;
		}
        return res;
    }

    private static int getStretchedIndex(String base, Integer index, Integer times) {
		int i = 0, res = 0;
		String hash;
		Pattern threeInARow = Pattern.compile("(.)\\1\\1");
		Pattern fiveInARow  = Pattern.compile("(.)\\1\\1\\1\\1");
		TreeMap<Integer, String> unconfirmed = new TreeMap<Integer,String>();
		TreeSet<Integer> indices = new TreeSet<Integer>();
		do {
			String id = base + i;
			hash = getHash(id,times);
			Matcher three = threeInARow.matcher(hash);
			Matcher five  = fiveInARow.matcher(hash);
			while(five.find()){
				String temp = five.group().substring(2);
				if(unconfirmed.containsValue(temp)){
					Iterator<Map.Entry<Integer,String>> itr = unconfirmed.entrySet().iterator();
					while(itr.hasNext()){
						Map.Entry<Integer,String> entry = itr.next();
						if(temp.equals(entry.getValue())){
							indices.add(entry.getKey());
							System.out.print("\r"+indices.size()+"/"+index);
							System.out.flush();
							itr.remove();
						}
					}
				}
			}
			if(three.find()&&indices.size()<index){
				unconfirmed.put(i,three.group());
			}
			Iterator<Map.Entry<Integer,String>> itr = unconfirmed.entrySet().iterator();
			while(itr.hasNext()){
				Map.Entry<Integer,String> entry = itr.next();
				if(entry.getKey()<i-1000){
					itr.remove();
				}
			}
			i++;
		} while(indices.size()<index || unconfirmed.size()>0);
		int j=0;
		for(Integer key:indices){
			if(j==index-1){
				res = key;
				break;
			}
			j++;
		}
        return res;
	}

	private static String getHash(String str, int times) {
		String hex = "";
		MessageDigest alg = null;
		try {
			alg = MessageDigest.getInstance("MD5");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		if(alg!=null) {
			for(int i=0; i<times; i++){
				hex = cache.get(str);
				if(hex==null){
					hex = "";
					byte[] digested = alg.digest(str.getBytes());
					for (byte b : digested) {
						String tempHex = Integer.toHexString(0xFF & b);
						if (tempHex.length() == 1)
							hex += "0";
						hex += tempHex;
					}
					if(i==0)
						cache.put(str,hex);
				}
				str = hex;
			}
		}
		return hex;
	}
}
