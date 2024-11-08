package BasicStore;

import com.mysql.cj.Session;

import java.util.HashMap;
import java.util.Set;

public class ShoppingCart {
    private HashMap<String, Integer> cart;
    public ShoppingCart() {
        cart = new HashMap<>();
    }

    public void addProduct(String productID) {
        if (cart.containsKey(productID)) {
            changeNum(productID, getNum(productID) + 1);
            return;
        }
        cart.put(productID, 1);
    }

    public int getNum(String productID) {
        return cart.get(productID);
    }

    public void changeNum(String productID, int num) {
        cart.remove(productID);
        if(num > 0)
            cart.put(productID, num);
    }

    public HashMap<String, Integer> getAllProducts() {
        return cart;
    }
}
