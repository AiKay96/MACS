// TabooTest.java
// Taboo class tests -- nothing provided.

import java.util.*;

import junit.framework.TestCase;

public class TabooTest extends TestCase {
    private List<String> stringToList(String s) {
        List<String> list = new ArrayList<String>();
        for (int i=0; i<s.length(); i++) {
            list.add(String.valueOf(s.charAt(i)));
            // note: String.valueOf() converts lots of things to string form
        }
        return list;
    }

    public void testTaboo1() {
        //basics
        List<String> a = stringToList("abbcbz");
        Taboo t = new Taboo<>(a);
        Set<String> st1 = new HashSet<>();
        st1.add("b");
        st1.add("c");
        st1.add("z");
        //relevant follow
        assertTrue( st1.equals(t.noFollow("b")));
        Set<String> st2 = new HashSet<>();
        //empty follow
        assertTrue( st2.equals(t.noFollow("z")));
        //other element
        assertTrue(Collections.emptySet().equals(t.noFollow("k")));
        List<String> b = stringToList("abbcbkpz");
        //basic reduce
        t.reduce(b);
        List<String> c = stringToList("ackpz");
        assertTrue( b.equals(c));
        //reduce again same result
        t.reduce(b);
        assertTrue( b.equals(c));
        List<String> d = stringToList("bbzbbbccb");
        //all char reduce
        t.reduce(d);
        List<String> e = stringToList("b");
        assertTrue( d.equals(e));
    }
    public void testTaboo2() {
        //null tests
        List<Integer> a = Arrays.asList(1, 2, null, 1, 3);
        Taboo t = new Taboo<>(a);
        assertTrue( t.noFollow(2).equals(Collections.emptySet()));
        //change nothing
        List<Integer> b = Arrays.asList(2, 2, 2, 1);
        t.reduce(b);
        List<Integer> c = Arrays.asList(2, 2, 2, 1);
        assertTrue(c.equals(b));
    }
}
