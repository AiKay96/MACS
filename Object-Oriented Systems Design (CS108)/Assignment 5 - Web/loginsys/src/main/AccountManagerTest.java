import UserLogin.AccountManager;
import junit.framework.TestCase;

public class AccountManagerTest extends TestCase {
    private AccountManager accountManager;
    private final static String USER_NAME_1 = "Patrick";
    private final static String USER_NAME_2 = "Molly";
    private final static String PASSWORD_1 = "1234";
    private final static String PASSWORD_2 = "FloPup";

    protected void setUp(){
        accountManager = new AccountManager();
    }
    public void testStart(){
        assertEquals(true, accountManager.accountExists(USER_NAME_1));
        assertEquals(true, accountManager.accountExists(USER_NAME_2));
        assertEquals(false, accountManager.accountExists("ANNA"));
        assertEquals(true, accountManager.matchPassword(USER_NAME_1, PASSWORD_1));
        assertEquals(true, accountManager.matchPassword(USER_NAME_2, PASSWORD_2));
        assertEquals(false, accountManager.matchPassword("ANNA", "ANNA"));
    }

    public void testCreate(){
        accountManager.createAccount("ANNA", "bana");
        assertEquals(true, accountManager.matchPassword("ANNA", "bana"));
        accountManager.createAccount("ANNA", "BANA");
        assertEquals(false, accountManager.matchPassword("ANNA", "BANA"));
        accountManager.createAccount("USER", "PASS");
        assertEquals(true, accountManager.matchPassword("USER", "PASS"));
    }
}