import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * @author Erik Andersson on 2016-12-05.
 */
public class Dec05 {
    public static void main(String[] args) {
        if(args.length>0)
            for(String test:args) {
                System.out.println(getPassword(test));
                //System.out.println(part2(test));
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
                    System.out.println(getPassword(row));
                    //System.out.println(part2(row));
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
				System.out.println(password);
			}
		} while(password.length() < 8);
        return password;
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
