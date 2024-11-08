package UserLogin;

import java.util.HashMap;

public class AccountManager {

    private HashMap<String, String> accs;

    private final static String USER_NAME_1 = "Patrick";
    private final static String USER_NAME_2 = "Molly";
    private final static String PASSWORD_1 = "1234";
    private final static String PASSWORD_2 = "FloPup";
    public AccountManager(){
        accs = new HashMap<>();
        accs.put(USER_NAME_1, PASSWORD_1);
        accs.put(USER_NAME_2, PASSWORD_2);
    }

    public boolean accountExists(String user_name){
        return accs.containsKey(user_name);
    }

    public boolean matchPassword(String user_name, String password){
        if(accountExists(user_name))
            return accs.get(user_name).equals(password);
        return false;
    }

    public void createAccount(String user_name, String password){
        if(!accountExists(user_name))
            accs.put(user_name, password);
    }
}