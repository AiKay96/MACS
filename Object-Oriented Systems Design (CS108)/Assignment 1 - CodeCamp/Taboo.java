
/*
 HW1 Taboo problem class.
 Taboo encapsulates some rules about what objects
 may not follow other objects.
 (See handout).
*/

import java.util.*;

public class Taboo<T> {
	HashMap<T, Set<T> > mp;
	/**
	 * Constructs a new Taboo using the given rules (see handout.)
	 * @param rules rules for new Taboo
	 */
	public Taboo(List<T> rules) {
		mp = new HashMap<>();
		for(int  i = 0; i < rules.size() - 1; i++){
			T curr = rules.get(i);
			if(curr == null)
				continue;
			T next = rules.get(i+1);
			if(mp.containsKey(curr)){
				Set<T> currSet = mp.get(curr);
				if(next != null)
					currSet.add(next);
				mp.put(curr, currSet);
			}else{
				Set<T> currSet = new HashSet<>();
				if(next != null)
					currSet.add(next);
				mp.put(curr, currSet);
			}
		}
		Set<T> currSet = new HashSet<>();
		mp.put(rules.get(rules.size() - 1), currSet);
	}
	
	/**
	 * Returns the set of elements which should not follow
	 * the given element.
	 * @param elem
	 * @return elements which should not follow the given element
	 */
	public Set<T> noFollow(T elem) {
		if(mp.containsKey(elem))
			return mp.get(elem);
		return Collections.emptySet();
	}
	
	/**
	 * Removes elements from the given list that
	 * violate the rules (see handout).
	 * @param list collection to reduce
	 */
	public void reduce(List<T> list) {
		for(int i = 0; i < list.size() - 1; i++){
			T curr = list.get(i);
			Set<T> currSet = noFollow(curr);
			while(i + 1 < list.size() && currSet.contains(list.get(i+1)))
				list.remove(i+1);
		}
	}
}
