import java.util.*;

public class Appearances {
	
	/**
	 * Returns the number of elements that appear the same number
	 * of times in both collections. Static method. (see handout).
	 * @return number of same-appearance elements
	 */
	public static <T> int sameCount(Collection<T> a, Collection<T> b) {
		int counter = 0;
		HashMap<T, Integer> mp = new HashMap<>();
		for(T curr: a){
			int num = 1;
			if(mp.containsKey(curr))
				num = mp.get(curr) + 1;
			mp.put(curr, num);
		}
		for(T curr: b) {
			if(mp.containsKey(curr)) {
				int num = mp.get(curr) - 1;
				mp.put(curr, num);
			}
		}
		for(T curr: mp.keySet())
			if(mp.get(curr) == 0)
				counter++;
		return counter;
	}
	
}
