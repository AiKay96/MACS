// Cracker.java
/*
 Generates SHA hashes of short strings in parallel.
*/

import java.security.*;
import java.util.Arrays;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.CountDownLatch;

public class Cracker {
	// Array of chars used to produce strings
	public static final char[] CHARS = "abcdefghijklmnopqrstuvwxyz0123456789.,-!".toCharArray();
	public static final int CHAR_NUM = 40;
	private static CountDownLatch latch;
	String ans;
	/*
	 Given a byte[] array, produces a hex String,
	 such as "234a6f". with 2 chars for each byte in the array.
	 (provided code)
	*/
	public static String hexToString(byte[] bytes) {
		StringBuffer buff = new StringBuffer();
		for (int i=0; i<bytes.length; i++) {
			int val = bytes[i];
			val = val & 0xff;  // remove higher bits, sign
			if (val<16) buff.append('0'); // leading 0
			buff.append(Integer.toString(val, 16));
		}
		return buff.toString();
	}
	
	/*
	 Given a string of hex byte values such as "24a26f", creates
	 a byte[] array of those values, one byte value -128..127
	 for each 2 chars.
	 (provided code)
	*/
	public static byte[] hexToArray(String hex) {
		byte[] result = new byte[hex.length()/2];
		for (int i=0; i<hex.length(); i+=2) {
			result[i/2] = (byte) Integer.parseInt(hex.substring(i, i+2), 16);
		}
		return result;
	}

    public byte[] generateHash(String password){
        try {
            MessageDigest md = MessageDigest.getInstance("SHA");
            md.update(password.getBytes());
            byte[] hashByte = md.digest();
            return hashByte;
        } catch (NoSuchAlgorithmException e){
            e.printStackTrace();
        }
        return null;
    }

	public String generatePass(String hash, int len, int num) {
		ans = "";
		try {
			latch = new CountDownLatch(num);
			int range = CHAR_NUM / num;
			int r = CHAR_NUM % num;
			int from = 0;
			for(int i = 0; i < num; i++){
				int to = from + range;
				if(r > 0){
					to++;
					r--;
				}
				Worker worker = new Worker(hash, len, from, to);
				worker.start();
				from = to;
			}
			latch.await();
		} catch (InterruptedException ignored){
		}
		return ans;
	}

	public static void main(String[] args) {
		if (args.length < 1) {
			System.exit(1);
		}
		Cracker cracker = new Cracker();
		if (args.length == 1){
			//args: targ
			// a! 34800e15707fae815d7c90d49de44aca97e2d759
			// xyz 66b27417d37e024c46526c2f6d358a754fc552f3
			String targ = args[0];
			System.out.println(hexToString(cracker.generateHash(targ)));
		}
		// args: targ len [num]
		String targ = args[0];
		int len = Integer.parseInt(args[1]);
		int num = 1;
		if (args.length>2) {
			num = Integer.parseInt(args[2]);
		}
		System.out.println(cracker.generatePass(targ, len, num));

	}

	private class Worker extends Thread{
		byte[] hash;
		int len, from, to;
		public Worker(String hash, int len, int from, int to){
			this.hash = hexToArray(hash);
			this.len = len;
			this.from = from;
			this.to = to;
		}

		private void recursion(String curr){
			if(curr.length() == len){
				if(Arrays.equals(generateHash(curr), hash))
					ans = curr;
				return;
			}
			for(int i = 0; i < CHAR_NUM; i++)
				recursion(curr + CHARS[i]);
		}

		public void run() {
			for(int i = from; i < to; i++) {
				String curr = "";
				curr += CHARS[i];
				if(ans != "")
					break;
				recursion(curr);
			}
			latch.countDown();
		}
	}
}
