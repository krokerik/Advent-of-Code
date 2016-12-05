import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;


/**
 * @author Erik Andersson on 2016-12-05.
 */
public class Dec05 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println("\r\u001B[32m"+getPassword(test)+"\u001B[0m");
                System.out.println("\r\u001B[32m"+getPositionPassword(test)+"\u001B[0m");
            }
        else {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader("../input/05.txt"));
            } catch (FileNotFoundException e) {
                System.err.println("Put your input in a file placed in the" +
                        " relative path \"../input/05.txt\" to where you run it." +
                        " Or supply your input as program argument.");
                e.printStackTrace();
            }
            try {
                while (br != null && br.ready()) {
                    String row = br.readLine();
                    System.out.println("\r\u001B[32m"+getPassword(row)+"\u001B[0m");
                    System.out.println("\r\u001B[32m"+getPositionPassword(row)+"\u001B[0m");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    private static String getPassword(String base) {
		int index = 0;
		String hash, password="";
		do {
			String id = base + index;
			hash = getHash(id);
			index++;
			if(hash.startsWith("00000")) {
				password += hash.charAt(5);
			}

			String tmp = new String(password);
			int len = tmp.length();
			tmp = "\u001B[32m" + tmp + "\u001B[31m";
			for(int i = len; i<8; i++) {
				tmp += hash.charAt(6+i);
			}
			System.out.print("\r"+tmp+"\u001B[0m");
			System.out.flush();
		} while(password.length() < 8);
        return password;
    }
	
    private static String getPositionPassword(String base) {
		int index = 0, numSet = 0;
		String hash;
		char[] password = { ' ',
		                    ' ',
		                    ' ',
		                    ' ',
		                    ' ',
		                    ' ',
		                    ' ',
		                    ' ' };

		do {
			String id = base + index;
			hash = getHash(id);
			index++;
			if(hash.startsWith("00000")) {
				int pos = Character.getNumericValue(hash.charAt(5));
				if(pos < 8 && password[pos] == ' ') {
					password[pos] = hash.charAt(6);
					numSet++;
				}
			}

			String tmp = new String("\r\u001B[32m");
			for(int i=0; i<8; i++) {
				if(password[i] == ' ') {
					tmp += "\u001B[31m"+hash.charAt(6+i)+"\u001B[32m";
				} else {
					tmp += password[i];
				}
			}
			System.out.print(tmp + "\u001B[0m");
			System.out.flush();
		} while(numSet<8);
        return new String(password);
	}
	
	private static String getHash(String str) {
		MessageDigest alg = null;
        String hex = "";
        try {
            alg = MessageDigest.getInstance("MD5");
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        if(alg!=null) {
			byte[] digested = alg.digest(str.getBytes());
			for (byte b : digested) {
				String tempHex = Integer.toHexString(0xFF & b);
				if (tempHex.length() == 1)
					hex += "0";
				hex += tempHex;
			}
		}
		return hex;
		
	}
}
