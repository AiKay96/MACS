import java.util.HashSet;
import java.util.Set;

// CS108 HW1 -- String static methods

public class StringCode {

	/**
	 * Given a string, returns the length of the largest run.
	 * A a run is a series of adajcent chars that are the same.
	 * @param str
	 * @return max run length
	 */
	public static int maxRun(String str) {
		if(str.equals(""))
			return 0;
		int ans = 1;
		int counter = 1;
		char prevChar = str.charAt(0);
		for(int i = 1; i < str.length(); i++){
			char curr = str.charAt(i);
			if(curr == prevChar){
				counter++;
				ans = Math.max(ans, counter);
			}else{
				counter = 1;
			}
			prevChar = curr;
		}
		return ans;
	}

	
	/**
	 * Given a string, for each digit in the original string,
	 * replaces the digit with that many occurrences of the character
	 * following. So the string "a3tx2z" yields "attttxzzz".
	 * @param str
	 * @return blown up string
	 */
	public static String blowup(String str) {
		String answer = "";
		for(int i = 0; i < str.length(); i++){
			char curr = str.charAt(i);
			if(Character.isDigit(curr)){
				if(i == str.length() - 1)
					continue;
				int numChar = curr - '0';
				char toRepeat = str.charAt(i+1);
				for(int j = 0; j < numChar; j++)
					answer += toRepeat;
			}else{
				answer += curr;
			}
		}
		return answer;
	}
	
	/**
	 * Given 2 strings, consider all the substrings within them
	 * of length len. Returns true if there are any such substrings
	 * which appear in both strings.
	 * Compute this in linear time using a HashSet. Len will be 1 or more.
	 */
	public static boolean stringIntersect(String a, String b, int len) {
		if(a.length() < len || b.length() < len)
			return false;
		HashSet<String> st = new HashSet<>();
		for(int i = 0; i <= a.length() - len; i++){
			st.add(a.substring(i, i + len - 1));
		}
		for(int i = 0; i <= b.length() - len; i++){
			if(st.contains(b.substring(i, i + len - 1)))
				return true;
		}
		return false;
	}
}
