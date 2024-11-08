import junit.framework.TestCase;

public class CrackerTest extends TestCase {
    Cracker cracker;
    protected void setUp() throws Exception{
        super.setUp();
        Bank bank = new Bank();
    }
    public void testGenerateHash(){
        assertEquals(cracker.hexToString(cracker.generateHash("molly")), "4181eecbd7a755d19fdf73887c54837cbecf63fd");
        assertEquals(cracker.hexToString(cracker.generateHash("a!")), "34800e15707fae815d7c90d49de44aca97e2d759");
        assertEquals(cracker.hexToString(cracker.generateHash("xyz")), "66b27417d37e024c46526c2f6d358a754fc552f3");
    }

    public void testGeneratePass(){
        assertEquals(cracker.generatePass("86f7e437faa5a7fce15d1ddcb9eaeaea377667b8", 1, 4), "a");
        assertEquals(cracker.generatePass("adeb6f2a18fe33af368d91b09587b68e3abcb9a7", 2, 10), "fm");

        assertEquals(cracker.generatePass("34800e15707fae815d7c90d49de44aca97e2d759", 2, 4), "a!");
        assertEquals(cracker.generatePass("66b27417d37e024c46526c2f6d358a754fc552f3", 3, 10), "xyz");

        assertEquals(cracker.generatePass("4181eecbd7a755d19fdf73887c54837cbecf63fd", 5, 8), "molly");
    }
}
