// Bank.java

/*
 Creates a bunch of accounts and uses threads
 to post transactions to the accounts concurrently.
*/

import java.io.*;
import java.util.*;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.LinkedBlockingQueue;

public class Bank {
	public static final int ACCOUNTS = 20;	 // number of accounts
    public static final int STARTING_BALANCE = 1000;
    private BlockingQueue<Transaction> requests;
    private List<Transaction> data;
    private static CountDownLatch latch;
    ArrayList<Account> accounts;
	/*
	 Reads transaction data (from/to/amt) from a file for processing.
	 (provided code)
	 */
	public void readFile(String file) {
			try {
			BufferedReader reader = new BufferedReader(new FileReader(file));
			
			// Use stream tokenizer to get successive words from file
			StreamTokenizer tokenizer = new StreamTokenizer(reader);
			
			while (true) {
				int read = tokenizer.nextToken();
				if (read == StreamTokenizer.TT_EOF) break;  // detect EOF
				int from = (int)tokenizer.nval;
				
				tokenizer.nextToken();
				int to = (int)tokenizer.nval;
				
				tokenizer.nextToken();
				int amount = (int)tokenizer.nval;

                requests.put(new Transaction(from, to, amount));
			}
		}
		catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	/*
	 Processes one file of transaction data
	 -fork off workers
	 -read file into the buffer
	 -wait for the workers to finish
	*/
	public void processFile(String file, int numWorkers) throws InterruptedException {
        initConcurrencyVariables(numWorkers);
        startWorkers(numWorkers);
        readFile(file);
        joinWorkers(numWorkers);
	}
    private void initConcurrencyVariables(int numWorkers){
        latch = new CountDownLatch(numWorkers);
        requests = new LinkedBlockingQueue<>();
        data = Collections.synchronizedList(new ArrayList<Transaction>());
    }
    private void startWorkers(int numWorkers){
        for(int i = 0; i < numWorkers; i++){
            Worker worker = new Worker(requests);
            worker.start();
        }
    }
    private void joinWorkers(int numWorkers) throws InterruptedException {
        for(int i = 0; i < numWorkers; i++)
            requests.put(new Transaction(-1, 0, 0));
        latch.await();
    }

	void createAccounts(){
        accounts = new ArrayList<>();
        for(int i = 0; i < ACCOUNTS; i++)
            accounts.add(new Account(this, i, STARTING_BALANCE));
    }

    private void printAccounts(){
        for(int i = 0; i < ACCOUNTS; i++)
            System.out.println(accounts.get(i));
    }

    ArrayList<String> storeAccounts(){
        ArrayList<String> arr = new ArrayList<>();
        for(int i = 0; i < ACCOUNTS; i++)
            arr.add(accounts.get(i).toString());
        return arr;
    }
	
	/*
	 Looks at commandline args and calls Bank processing.
	*/
	public static void main(String[] args) throws InterruptedException {
		// deal with command-lines args
		if (args.length == 0) {
			System.out.println("Args: transaction-file [num-workers [limit]]");
			System.exit(1);
		}
		
		String file = args[0];
		
		int numWorkers = 1;
		if (args.length >= 2) {
			numWorkers = Integer.parseInt(args[1]);
		}
        Bank bank = new Bank();
        bank.createAccounts();
        bank.processFile(file, numWorkers);
        bank.printAccounts();
	}
    private class Worker extends Thread{
        private BlockingQueue<Transaction> request;
        public Worker(BlockingQueue<Transaction> requests){
            request = requests;
        }

        public void start(){
            new Thread(new Runnable() {
                @Override
                public void run() {
                    Transaction transaction = new Transaction(-1, 0, 0);
                    while(true) {
                        try {
                            transaction = request.take();
                        } catch (InterruptedException ignored) {}
                        if(transaction.from == -1)
                            break;
                        int amount = transaction.amount;
                        Account accountFrom = accounts.get(transaction.from);
                        accountFrom.changeBalance((-1) * amount);
                        Account accountTo = accounts.get(transaction.to);
                        accountTo.changeBalance(amount);
                    }
                    latch.countDown();

                }
            }).start();
        }
    }
}

