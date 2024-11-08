import junit.framework.TestCase;

import java.util.ArrayList;

public class BankTest extends TestCase {
    String[] ANS_2 = new String[]{
            "acct:0 bal:1000 trans:10360",
            "acct:1 bal:1000 trans:8880",
            "acct:2 bal:1000 trans:10440",
            "acct:3 bal:1000 trans:9840",
            "acct:4 bal:1000 trans:10520",
            "acct:5 bal:1000 trans:10520",
            "acct:6 bal:1000 trans:9480",
            "acct:7 bal:1000 trans:9440",
            "acct:8 bal:1000 trans:8720",
            "acct:9 bal:1000 trans:9000",
            "acct:10 bal:1000 trans:9960",
            "acct:11 bal:1000 trans:10520",
            "acct:12 bal:1000 trans:9760",
            "acct:13 bal:1000 trans:9640",
            "acct:14 bal:1000 trans:10320",
            "acct:15 bal:1000 trans:9840",
            "acct:16 bal:1000 trans:10400",
            "acct:17 bal:1000 trans:10560",
            "acct:18 bal:1000 trans:11720",
            "acct:19 bal:1000 trans:10080"
    };
    String[] ANS_1 = new String[]{
            "acct:0 bal:1000 trans:518",
            "acct:1 bal:1000 trans:444",
            "acct:2 bal:1000 trans:522",
            "acct:3 bal:1000 trans:492",
            "acct:4 bal:1000 trans:526",
            "acct:5 bal:1000 trans:526",
            "acct:6 bal:1000 trans:474",
            "acct:7 bal:1000 trans:472",
            "acct:8 bal:1000 trans:436",
            "acct:9 bal:1000 trans:450",
            "acct:10 bal:1000 trans:498",
            "acct:11 bal:1000 trans:526",
            "acct:12 bal:1000 trans:488",
            "acct:13 bal:1000 trans:482",
            "acct:14 bal:1000 trans:516",
            "acct:15 bal:1000 trans:492",
            "acct:16 bal:1000 trans:520",
            "acct:17 bal:1000 trans:528",
            "acct:18 bal:1000 trans:586",
            "acct:19 bal:1000 trans:504"};
    Bank bank1;
    Bank bank2;
    protected void setUp() throws Exception{
        super.setUp();
    }
    public void testThread1() throws InterruptedException {
        bank1 = new Bank();
        bank1.createAccounts();
        bank1.processFile("5k.txt", 1);
        bank2 = new Bank();
        bank2.createAccounts();;
        bank2.processFile("100k.txt", 1);
        ArrayList<String> arr1 = bank1.storeAccounts();
        ArrayList<String> arr2 = bank2.storeAccounts();
        for(int i = 0; i < Bank.ACCOUNTS; i++){
            String exp1 = arr1.get(i);
            String act1 = ANS_1[i];
            String exp2 = arr2.get(i);
            String act2 = ANS_2[i];
            assertEquals(exp1, act1);
            assertEquals(exp2, act2);
        }
    }
    public void testThread4() throws InterruptedException {
        bank1 = new Bank();
        bank1.createAccounts();
        bank1.processFile("5k.txt", 4);
        bank2 = new Bank();
        bank2.createAccounts();;
        bank2.processFile("100k.txt", 4);
        ArrayList<String> arr1 = bank1.storeAccounts();
        ArrayList<String> arr2 = bank2.storeAccounts();
        for(int i = 0; i < Bank.ACCOUNTS; i++){
            String exp1 = arr1.get(i);
            String act1 = ANS_1[i];
            String exp2 = arr2.get(i);
            String act2 = ANS_2[i];
            assertEquals(exp1, act1);
            assertEquals(exp2, act2);
        }
    }
    public void testThread8() throws InterruptedException {
        bank1 = new Bank();
        bank1.createAccounts();
        bank1.processFile("5k.txt", 8);
        bank2 = new Bank();
        bank2.createAccounts();;
        bank2.processFile("100k.txt", 8);
        ArrayList<String> arr1 = bank1.storeAccounts();
        ArrayList<String> arr2 = bank2.storeAccounts();
        for(int i = 0; i < Bank.ACCOUNTS; i++){
            String exp1 = arr1.get(i);
            String act1 = ANS_1[i];
            String exp2 = arr2.get(i);
            String act2 = ANS_2[i];
            assertEquals(exp1, act1);
            assertEquals(exp2, act2);
        }
    }

    public void testThread10() throws InterruptedException {
        bank1 = new Bank();
        bank1.createAccounts();
        bank1.processFile("5k.txt", 10);
        bank2 = new Bank();
        bank2.createAccounts();;
        bank2.processFile("100k.txt", 10);
        ArrayList<String> arr1 = bank1.storeAccounts();
        ArrayList<String> arr2 = bank2.storeAccounts();
        for(int i = 0; i < Bank.ACCOUNTS; i++){
            String exp1 = arr1.get(i);
            String act1 = ANS_1[i];
            String exp2 = arr2.get(i);
            String act2 = ANS_2[i];
            assertEquals(exp1, act1);
            assertEquals(exp2, act2);
        }
    }
}
